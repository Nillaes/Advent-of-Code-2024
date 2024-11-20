#include <stdio.h>
#include <iostream>
#include <fstream>

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
        printf("\nerror has occurred");
    }

    return inputStream;
}

std::string day = "1";

int main(){
    std::ifstream inputStream = GetInputStream(day);
    if(!inputStream.is_open()){
        printf("\n COULD NOT GET FILE!\n");
        return 1;
    }
    inputStream.seekg (0, inputStream.end);
    int filesize = inputStream.tellg();
    inputStream.seekg (0, inputStream.beg);

    char* buffer = new char [filesize];
    inputStream.read(buffer, filesize);
    inputStream.close();

    int floor = 0;
    int firstBasementPos = 0;
    for(int i = 0; i < filesize; i++){
        if(buffer[i] == '('){
            floor++;
        }
        if(buffer[i] == ')'){
            floor--;
        }
        if(floor < 0 && firstBasementPos == 0){
            std::cout << "\n" << i << "\n";
            firstBasementPos = i;
        }
    }
    std::cout << "\n" << floor << "\n";
}