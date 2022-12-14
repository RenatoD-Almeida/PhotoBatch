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

        enum FlagsEnumError
        {
            //FLAGS gerais:
            i_NoFlags, i_FlagsALot,
            
            //Option Folder
            i_EmptyFolder, i_FolderNotExists,

            //Option Filter
            i_InvalidFilter,

            // FLAG RESIZE
            i_InvalidTypeWidthHeight, i_WidthHeightLessThanZero, i_ResizeNoFilter,

            // FLAG SCALE
            i_InvalidTypeAmount, i_AmountLessEqualZero, i_ScaleNoFilter,

            // FLAG RENAME
            i_EmptyPrefix, i_InvalidPrefix, i_InvalidTypeStartNumber, i_StartNumberLessEqualZero,

            // FLAG CONVERT

            i_FromToInvalidExtension, i_FromAndToEqual, i_EmptyFromTo
        }; 
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

namespace utility
{

std::string ToLowerString(std::string str);
bool validateString(const std::string& string);
void helpGetMessage(Args::Flags::flagsEnum flagsEnum);
void getLogError(Args::Flags::flagsEnum FlagsEnum, Args::Flags::FlagsEnumError FlagsError);

}
#endif