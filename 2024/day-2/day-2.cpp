#include "../../utils/input.h"
#include "../../utils/utils.h"
typedef std::string str;

str day = "2";

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
    //cleanup
    delete [] buffer;

    std::vector<int> report;
    
    std::vector<std::vector<int>> allReports;
    for (int i = 0; i < 1024; i++)
    {
        if( lineBuffer[i] != ""){
            std::vector<std::string> splitLine = Split(lineBuffer[i], ' ');

            for(auto num: splitLine){
                report.push_back(NumbersToInt(num));
            }
            allReports.push_back(report);
            report.clear();
        }
    }

    int8_t maxDelta = 3;
    int validCount = 0;
    int part2ValidCount = 0;
    for (int i = 0; i < allReports.capacity(); i++){
        bool allIncreasing = true;
        bool allDecreasing = true;
        bool deltaCheckPass = true;

        for (int j = 0; j < allReports[i].capacity(); j++){
            
            if (j+1 < allReports[i].capacity()){
                if (allReports[i][j] == allReports[i].at(j+1)){
                    allDecreasing = false;
                    allIncreasing = false;
                    deltaCheckPass = false;
                }if (allIncreasing == true && allReports[i][j] > allReports[i].at(j+1)){
                    allIncreasing = false;
                }if (allDecreasing == true && allReports[i][j] < allReports[i].at(j+1))
                {
                    allDecreasing = false;
                }if (deltaCheckPass == true && std::abs(allReports[i][j] - allReports[i].at(j+1)) > maxDelta)
                {
                    deltaCheckPass = false;
                }      
            }
        }
        if (deltaCheckPass && (allDecreasing || allIncreasing) && allReports[i].capacity() >= 2)
        {
            validCount++;
        }else{ // At tjis point the report is not valid. Hence we want to check if we can make it valid by removing (ignoring) 1 value
            bool v = false;
            for (int j = 0; j < allReports[i].capacity(); j++) // j is the index of the value we should ignore
            {
                std::vector<int> rep;
                for (int n = 0; n < allReports[i].capacity(); n++){
                    if (n != j){
                        rep.push_back(allReports[i][n]);
                    }
                }
                rep.shrink_to_fit();
                //* TESTED: this creates all permutations of the report by removing one value.
                bool allIncreasing = true;
                bool allDecreasing = true;
                bool deltaCheckPass = true;
                for (int j = 0; j < rep.capacity(); j++){
                    if (j+1 < rep.capacity()){
                        if (rep[j] == rep.at(j+1)){
                            allDecreasing = false;
                            allIncreasing = false;
                            deltaCheckPass = false;
                        }if (allIncreasing == true && rep[j] > rep.at(j+1)){
                            allIncreasing = false;
                        }if (allDecreasing == true && rep[j] < rep.at(j+1)){
                            allDecreasing = false;
                        }if (deltaCheckPass == true && std::abs(rep[j] - rep.at(j+1)) > maxDelta){
                            deltaCheckPass = false;
                        }      
                    }
                }
                if (deltaCheckPass && (allDecreasing || allIncreasing) && allReports[i].capacity() >= 2){
                    v = true;
                }
                rep.clear();
            }
            if(v){
                part2ValidCount++;
            }
            
        }
    }
    
    std::cout << std::endl << validCount << std::endl;
    std::cout << std::endl << part2ValidCount + validCount << std::endl;

    return 0;
}
