#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>

std::ifstream GetInputStream(std::string day){
    std::ifstream inputStream;
    std::string filepath = "../../input/day-.txt";
    //std::string filepath = "../../input/day--2015.txt"; //Use for challenges from 2015 
    filepath.insert(16,day);
    printf(filepath.c_str());
    inputStream.open(filepath);
    if(inputStream.is_open()){
        //printf("\nFile has been opened succesfully");
    }
    else{
        printf("\nThere was an error while opening the file.");
        printf("filepath used:  ");
        std::cout << filepath << "\n";
    }

    return inputStream;
}

