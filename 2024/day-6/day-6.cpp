#include "../../utils/input.h"
#include "../../utils/utils.h"
typedef std::string str;

str day = "6";
void UpdateDirection(int* dirUpdate, char dir){
    switch (dir)
    {
        case 'v':
            dirUpdate[0] = 1;
            dirUpdate[1] = 0;
            break;
        case '<':
            dirUpdate[0] = 0;
            dirUpdate[1] = -1;
            break;
        case '>':
            dirUpdate[0] = 0;
            dirUpdate[1] = 1;
            break;
        case '^':
            dirUpdate[0] = -1;
            dirUpdate[1] = 0;
            break;
        case '#':
            if (dirUpdate[0] == 1 && dirUpdate[1] == 0)
            {
                dirUpdate[0] = 0;
                dirUpdate[1] = -1;
            }
            else if (dirUpdate[0] == 0 && dirUpdate[1] == -1)
            {
                dirUpdate[0] = -1;
                dirUpdate[1] = 0;
            }
            else if (dirUpdate[0] == 0 && dirUpdate[1] == 1)
            {
                dirUpdate[0] = 1;
                dirUpdate[1] = 0;
            }
            else if (dirUpdate[0] == -1 && dirUpdate[1] == 0)
            {
                dirUpdate[0] = 0;
                dirUpdate[1] = 1;
            }
            break;
            
        default:
            break;
    }
}

int main(int argc, char const *argv[])
{
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

    //* Find starting position
    int Y = 0;
    int X = 0;
    char dir = '!';

    for (int line = 0; line < lineBuffer.capacity(); line++)
    {
        for (int chr = 0; chr < lineBuffer[line].length(); chr++)
        {
            if (lineBuffer[line][chr] == 'v' || lineBuffer[line][chr] == '<' || lineBuffer[line][chr] == '>' || lineBuffer[line][chr] == '^')
            {
                X = chr;
                Y = line;
                dir = lineBuffer[line][chr];
                std::cout << std::endl << "Starting Position Found! " << std::endl;
                break;
            }
        }
    }

    int dirUpdate[2];
    UpdateDirection(dirUpdate, dir);

    //* Time to move across the map
    while (Y + dirUpdate[0]>=0 && X + dirUpdate[1] >= 0 && X + dirUpdate[1] < lineBuffer[0].length() && Y + dirUpdate[0]< lineBuffer.capacity()){ // While we are in the map
        if (lineBuffer[Y + dirUpdate[0]][X + dirUpdate[1]] != '#') // 
        {
            Y += dirUpdate[0];
            X += dirUpdate[1]; 
            lineBuffer[Y][X] = 'X';
        }
        else{
            UpdateDirection(dirUpdate, '#');
        }
        
    }
    
    int visitedTiles = 0;
    for (int line = 0; line < lineBuffer.capacity(); line++)
    {
        for (int chr = 0; chr < lineBuffer[line].length(); chr++)
        {
            if (lineBuffer[line][chr] == 'X')
            {
                visitedTiles++;
            }
        }
    }
    
    std::cout << visitedTiles << " tiles have been visited by the guard." << std::endl;

    return 0;
}