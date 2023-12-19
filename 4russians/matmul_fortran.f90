module mult_fortran

    implicit none
    contains

    subroutine fill_RowSums(p, k, B, RowSums)
        integer (4):: B(:, :), RowSums(:, :)
        integer :: p, k, i, j, l
        do j = 2, ishft(1, k)
            l = log(j-1.0)/log(2.0)
            do i = 1, size(B, 2)
                RowSums(j,i) = xor(RowSums(j-ishft(1, l), i), B(p+l+1, i))
            end do
        end do
    end subroutine

    subroutine dec_num(iter, row, k, A, d)
        integer:: iter, row, k, d, j, p, bt, tmp
        integer(4)::A(:, :)
        bt = 32
        d = 0
        do j = 0, k-1
            p = iter + j
            tmp = shiftr(AND(A(row, p/bt+1), ishft(1, bt - 1 - MOD(p,bt))), bt - 1 - MOD(p, bt))
            d = d + ishft(1, j) * tmp 
        end do    
    end subroutine

    subroutine mat_mul(A, B, C)
        integer(4), dimension(:, :) :: A, B, C
        integer :: N, M, k, iter, col, row, d
        integer(4), allocatable:: RowSums(:, :)

        N = size(A, 1)
        M = size (A, 2)

        if (N > 1024) then
            k = 19 - log(N/3.0)/log(2.0)
        else
            k = log(N*1.0)/log(2.0)
        end if
        allocate ( RowSums(ishft(1, k), M) )
        do iter = 1, N/k
            call fill_RowSums((iter-1)*k, k, B, RowSums)
            do row = 1,N
                call dec_num((iter-1)*k, row, k, A, d)
                do col = 1,M
                    C(row, col) = xor(C(row, col), RowSums(d+1, col))
                end do
            end do           
        end do
        if (MOD(N, k)>0) then
            call fill_RowSums((N/k)*k, MOD(N, k), B, RowSums)
            do row = 1, N
                call dec_num(k*(N/k), row, MOD(N, k), A, d)
                do col = 1, M
                    C(row, col) = xor(C(row, col), RowSums(d+1, col))
                end do
            end do
        end if
    end subroutine

    subroutine wrapper_func(N, M, mA, mB, mC) bind (C, name = "matmul_f90")
        use :: iso_c_binding

        type(C_PTR), value :: mA, mB, mC
        integer(C_INT), value :: N, M
        integer(4), pointer :: at(:, :), bt(:, :), ct(:, :)
        integer(4), allocatable :: a(:, :), b(:, :), c(: ,:)
integer::i, j
        call C_F_POINTER(mA, at, [M, N])
        call C_F_POINTER(mB, bt, [M, N])
        call C_F_POINTER(mC, ct, [M, N])

        allocate (b(N, M))
        allocate (a(N, M))
        allocate (c(N, M))
        a = transpose(at)
        b = transpose(bt)
        do i=1, N
            do j=1, M
                c(i, j)=0
            end do
        end do
        call mat_mul(a, b, c)
        ct = transpose(c)
        deallocate (a)
        deallocate (b)
        deallocate (c)
    end subroutine 

end module mult_fortran
