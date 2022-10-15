#include "utility.hpp"

namespace utility{

    std::string ToLowerString(std::string str){
        for(char& c : str){
            c = std::tolower(c);
        }
        return str;
    }

    bool validateString(const std::string& string)
    {
        const std::string invalidCaracteres = "\\/*?:\"<>|";
        for(char c : string)
        {
            for(char _c : invalidCaracteres)
            {
                if(c == _c)
                {
                    return false;
                }
            }
        }
        return true;
    }
}