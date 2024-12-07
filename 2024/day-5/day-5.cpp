#include "../../utils/input.h"
#include "../../utils/utils.h"
#include <regex>
typedef std::string str;

str day = "5";

int main(int argc, char const *argv[]){
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

    return 0;
}