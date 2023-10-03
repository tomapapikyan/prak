#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

void generate_input(int size, std::fstream& input){

    std::srand(time(NULL));

    for (int k = 0; k < 2; k++){
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++)
                input<<int(std::rand()%2)<<" ";
            input<<"\n";
        }
        input<<"\n";
    }

    input.close();
}
