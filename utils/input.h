#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>

std::ifstream GetInputStream(std::string day){
    std::ifstream inputStream;
    std::string filepath = "../../input/day--2015.txt";
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

// this get's called with something like "679407" and returns 679407
int NumbersToInt(std::string num){
    int length = num.length();
    int number = 0;
    for (int i = 0; i < length; i++){
        int digit = num[i] - int('0');
        number += digit * pow(10, length - i - 1);
    }

    return number;
}