#include "../../utils/input.h"
#include "../../utils/utils.h"
typedef std::string str;

str day = "2";



struct Box
{
    int Height;
    int Width;
    int Length;
    int Area;
    int smallestSide;
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

    str lineBuffer[1024];
    int currLine = 0;

    str line = "";
    for (int i = 0; i < filesize; i++)
    {
        if (buffer[i] != '\n')
        {
            line.append(1, buffer[i]);
        }else{
            lineBuffer[currLine] = line;
            currLine++;
            line.clear();
        }
    }
    /*
    At this point Line buffer contains all the lines as individual strings
    The part probably should be added as a separate Utility function in the utils.h header so it can be reused in the other challenges
    */
   Box boxList[1024];
   for (int i = 0; i < 1024; i++){
    if(lineBuffer[i] != ""){ // Ignore empty strings
        str stringNumber = "";
        int8_t side = 0;
        for (int8_t j = 0; j <= lineBuffer[i].length(); j++){
            if (lineBuffer[i][j] != 'x' && j < lineBuffer[i].length())
            {
                stringNumber.append(1,lineBuffer[i][j]);
            }else{
                if (side == 0)
                {
                    boxList[i].Length = NumbersToInt(stringNumber);
                    stringNumber.clear();
                    side++;
                }else if (side == 1)
                {
                    boxList[i].Width = NumbersToInt(stringNumber);
                    stringNumber.clear();
                    side++;
                }else if (side == 2)
                {
                    boxList[i].Height = NumbersToInt(stringNumber);
                    stringNumber.clear();
                    side++;
                }
            }
        }
        }
   }
   // Boxlist is now loaded
    int totalNeeded = 0;
    for (int i = 0; i < 1024; i++)
    {
        int s1 = boxList[i].Width * boxList[i].Length;
        int s2 = boxList[i].Width * boxList[i].Height;
        int s3 = boxList[i].Height * boxList[i].Length;
        boxList[i].Area = 2*s1 + 2*s2 + 2*s3;
        boxList[i].smallestSide = std::min(s1, std::min(s2, s3));
        totalNeeded += boxList[i].Area + boxList[i].smallestSide;
    }

    std::cout << '\n' << totalNeeded << '\n';

    return 0;
}