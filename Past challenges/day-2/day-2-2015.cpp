#include "../../utils/input.h"
std::string day = "2";

struct Box
{
    int Height;
    int Width;
    int Length;
};

int main(int argc, const char** argv) {
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

    char** lineBuffer = new char* [1024];
    int8_t bufferIndex = 0;

    char* line[64];
    int8_t lineIndex = 0;
    
    for (int i = 0; i < filesize; i++)
    {
        if (buffer[i] != '\n'){
            line[lineIndex] = &buffer[i];
            lineIndex++;
        }else{
            lineBuffer[bufferIndex] = *line;
            lineIndex = 0;
            char* line[64];
            bufferIndex++;
        }
    }
    //free(&bufferIndex);
    //free(&lineBuffer);
    //free(&line);

    std::cout << "\n" << *lineBuffer << "\n";

    //std::cout << "\n" << NumbersToInt("67396") << "\n";

    return 0;
}