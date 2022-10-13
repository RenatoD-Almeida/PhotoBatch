#include "utility.hpp"

namespace utility{

    std::string ToLowerString(std::string str){
        for(char& c : str){
            c = std::tolower(c);
        }
        return str;
    }

}