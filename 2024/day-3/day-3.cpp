#include "../../utils/input.h"
#include "../../utils/utils.h"
#include <regex>
typedef std::string str;

str day = "3";

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

    str input = buffer;
    std::regex r("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    std::smatch m;
    
    int sum = 0;
    while (std::regex_search(input, m, r))
    {
        sum += NumbersToInt(m[1]) * NumbersToInt(m[2]);
        //std::cout << std::endl << m[1] << ", " << m[2];    
        input = m.suffix();
    }
    
    
    input = buffer; // reset for part two
    int p2Sum = 0;
    bool MulActive = true;
    std::regex do_pattern("do\\(\\)");
    std::regex dont_pattern("don't\\(\\)");

    while(input != ""){
        std::smatch MulMatch;
        std::smatch DoMatch;
        std::smatch DontMatch;
        std::regex_search(input, DoMatch, do_pattern);
        std::regex_search(input, DontMatch, dont_pattern);
        std::regex_search(input, MulMatch, r);
        // Option 1: The mul instruction is the first we find
        if(MulMatch.position() < DontMatch.position() && MulMatch.position() < DoMatch.position()){
            if (MulActive){
                p2Sum += NumbersToInt(MulMatch[1]) * NumbersToInt(MulMatch[2]);
            }
            input = MulMatch.suffix();
        }
        // Option 2: We find a Do instruction
        else if (DoMatch.position() < DontMatch.position() && DoMatch.position() < MulMatch.position()){
            MulActive = true;
            input = DoMatch.suffix();
        }
        else if (DontMatch.position() < DoMatch.position() && DontMatch.position() < MulMatch.position())
        {
            MulActive = false;
            input = DontMatch.suffix();
        }else{
            input = "";
        }
    }

    std::cout << std::endl << sum << std::endl;
    std::cout << std::endl << p2Sum << std::endl;

    return 0;
}