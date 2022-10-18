#ifndef _UTILITY_H
#define _UTILITY_H

#include <iostream>
#include <iomanip>
#include <map>

namespace Args
{
    namespace Flags
    {
        static constexpr const char* Rename = "rename";
        static constexpr const char* Convert = "convert";
        static constexpr const char* Resize = "resize";
        static constexpr const char* Scale = "scale";
        static constexpr const char* Help = "help";
        static constexpr const char* NoArgs = "";
        enum flagsEnum{i_RENAME, i_CONVERT, i_RESIZE, i_SCALE, i_NOARGS};
    }
    namespace Options
    {
        static constexpr const char* Folder = "folder";
        static constexpr const char* Filter = "filter";   
        static constexpr const char* Width = "width";
        static constexpr const char* Height = "height";
        static constexpr const char* Amount = "amount";
        static constexpr const char* Prefix = "prefix";
        static constexpr const char* StartNumber = "startnumber";
        static constexpr const char* To = "to";
        static constexpr const char* From = "from";
    }
}

namespace utility{

std::string ToLowerString(std::string str);
bool validateString(const std::string& string);
void helpGetMessage(Args::Flags::flagsEnum flagsEnum);

}
#endif