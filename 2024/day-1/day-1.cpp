#include "../../utils/input.h"
#include "../../utils/utils.h"
typedef std::string str;

str day = "1";

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

    int list1[1024];
    int list2[1024];

    for (int i = 0; i < 1024; i++)
    {
        if (lineBuffer[i] != "")
        {
            int8_t pos = 0;
            str num1 = "";
            str num2 = "";
            while (lineBuffer[i][pos] != ' ')
            {
                num1.append(1, lineBuffer[i][pos]);
                pos++;
            }
            while (pos < lineBuffer[i].length())
            {
                num2.append(1, lineBuffer[i][pos]);
                pos++;
            }
            list1[i] = NumbersToInt(num1);
            list2[i] = NumbersToInt(num2);
        }
    }
    // Sorting the lists
    radix_sort(list1);
    radix_sort(list2);
    int listDiff = 0;
    for (int i = 0; i < 1024; i++)
    {
        listDiff += std::max(list1[i], list2[i]) - std::min(list1[i], list2[i]);
    }

    int similarityScore = 0;
    for (int i = 0; i < 1024; i++)
    {
        for (int j = 0; j < 1024; j++)
        {
            if (list1[i] == list2[j])
            {
                similarityScore += list1[i];
            }
        }
    }
    

    std::cout <<"\n RESULT PART ONE: " << listDiff << "\n";
    std::cout <<"\n RESULT PART TWO: " << similarityScore << "\n";
    return 0;
}