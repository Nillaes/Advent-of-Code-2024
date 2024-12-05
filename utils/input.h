#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

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

/* Splits a string using a separator. Currently only accepts single character separators.
Returns a std::vector containing the split string*/
std::vector<std::string> Split(std::string string, char separator){

    std::string buff = "";
    std::vector<std::string> parts;
    for (int i = 0; i < string.length(); i++){
        if (string[i] != separator){
            buff.append(1, string[i]);
        }else{
            parts.push_back(buff);
            buff.clear();
        }
    }
    parts.push_back(buff);
    
    return parts;
}