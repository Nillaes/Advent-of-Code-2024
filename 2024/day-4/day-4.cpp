#include "../../utils/input.h"
#include "../../utils/utils.h"
typedef std::string str;

str day = "4";

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

    std::vector<str> lineBuffer;
    str line = "";
    for (int i = 0; i < filesize; i++)
    {
        if (buffer[i] != '\n')
        {
            line.append(1, buffer[i]);
        }else{
            lineBuffer.push_back(line);
            line.clear();
        }
    }
    //cleanup
    delete [] buffer;
    lineBuffer.shrink_to_fit();

    int XMAScounter = 0;
    for (int i = 0; i < lineBuffer.capacity(); i++){ // for each line
        for (int j = 0; j < lineBuffer[i].length(); j++){ // go character by character
            if (lineBuffer[i][j] != 'X') continue; // Since we are looking for "XMAS" sequences if we are not looking at an "X" it does not matter
            //* Checking horizontally
            // checks the next four characters
            if(lineBuffer[i].length() - (j+1) >= 3){ // check right
                if (lineBuffer[i][j+1] == 'M' && lineBuffer[i][j+2] == 'A' && lineBuffer[i][j+3] == 'S'){
                    XMAScounter++;
                }
            }
            //checks the previous four characters
            if (j >= 3){ // check left
                if (lineBuffer[i][j-1] == 'M' && lineBuffer[i][j-2] == 'A' && lineBuffer[i][j-3] == 'S'){
                    XMAScounter++;
                }
            }
            //* Checking vertically
            if(i >= 3){ // check above
                if (lineBuffer[i-1][j] == 'M' && lineBuffer[i-2][j] == 'A' && lineBuffer[i-3][j] == 'S'){
                    XMAScounter++;
                }
            }
            if(lineBuffer.capacity() - (i+1) >= 3){ // check below
                if (lineBuffer[i+1][j] == 'M' && lineBuffer[i+2][j] == 'A' && lineBuffer[i+3][j] == 'S'){
                    XMAScounter++;
                }
            }
            //* Checking diagonals
            if (i >= 3 && j >= 3){ // Top left
                if (lineBuffer[i-1][j-1] == 'M' && lineBuffer[i-2][j-2] == 'A' && lineBuffer[i-3][j-3] == 'S'){
                    XMAScounter++;
                }
            }
            if (i >= 3 && lineBuffer[i].length() - (j+1) >= 3){ // Top right
                if (lineBuffer[i-1][j+1] == 'M' && lineBuffer[i-2][j+2] == 'A' && lineBuffer[i-3][j+3] == 'S'){
                    XMAScounter++;
                }
            }
            if (lineBuffer.capacity() - (i+1) >= 3 && j >= 3){ // Bottom left
                if (lineBuffer[i+1][j-1] == 'M' && lineBuffer[i+2][j-2] == 'A' && lineBuffer[i+3][j-3] == 'S'){
                    XMAScounter++;
                }
            }
            if (lineBuffer.capacity() - (i+1) >= 3 && lineBuffer[i].length() - (j+1) >= 3){ // Bottom right
                if (lineBuffer[i+1][j+1] == 'M' && lineBuffer[i+2][j+2] == 'A' && lineBuffer[i+3][j+3] == 'S'){
                    XMAScounter++;
                }
            }
            
        }
        
    }
    int X_MAScounter = 0;
    for (int i = 0; i < lineBuffer.capacity() - 2; i++){ // -2 because we are checking a 3x3 box
        for (int j = 0; j < lineBuffer[i].length() - 2; j++){ // same reason as above
            if (lineBuffer[i][j] != 'M' && lineBuffer[i][j] != 'S') continue; // the boxes we check start with M or S
            if (lineBuffer[i][j] == 'M'){ //deal with boxes that start with M
                /* Box that we are looking for:
                    M.S
                    .A.
                    M.S
                */
                if (lineBuffer[i][j+2] == 'S' && lineBuffer[i+1][j+1] == 'A' && lineBuffer[i+2][j] == 'M' && lineBuffer[i+2][j+2] == 'S'){
                    X_MAScounter++;
                }
                /* Box that we are looking for:
                    M.M
                    .A.
                    S.S
                */
                if (lineBuffer[i][j+2] == 'M' && lineBuffer[i+1][j+1] == 'A' && lineBuffer[i+2][j] == 'S' && lineBuffer[i+2][j+2] == 'S'){
                    X_MAScounter++;
                }
            }else{ // Deal with boxes that start with S
                /* Box that we are looking for:
                    S.M
                    .A.
                    S.M
                */
                if (lineBuffer[i][j+2] == 'M' && lineBuffer[i+1][j+1] == 'A' && lineBuffer[i+2][j] == 'S' && lineBuffer[i+2][j+2] == 'M'){
                    X_MAScounter++;
                }
                /* Box that we are looking for:
                    S.S
                    .A.
                    M.M
                */
                if (lineBuffer[i][j+2] == 'S' && lineBuffer[i+1][j+1] == 'A' && lineBuffer[i+2][j] == 'M' && lineBuffer[i+2][j+2] == 'M'){
                    X_MAScounter++;
                }
            }         
        }
    }
    
    std::cout << std::endl << "XMAS FOUND: " << XMAScounter << std::endl;
    std::cout << "X-MAS FOUND: " << X_MAScounter << std::endl;
    return 0;
}