#ifndef _ARGUMENT_PARSER_H
#define _ARGUMENT_PARSER_H

#include "utility.hpp"

    class ArgumentParser
    {
        public:
            // Flags
            
            void RegisterFlag(const std::string& Flag);
            bool GetFlag(const std::string& Flag) const; // mover ao private depois!
            void Parser(int argc, char* argv[]);
            
            // Options
            void RegisterOption(const std::string& option);

            template<typename T>
            T GetOptionAs(const std::string& option) const;

        private:
            // Mapeamento das flags e opções
            std::map<std::string, bool> m_Flags;
            std::map<std::string, std::string> m_Options;

            //Option
            const std::string& GetOption(const std::string& option) const;


    };

#endif

template<>
float ArgumentParser::GetOptionAs(const std::string& option) const
{
    const std::string& OptionValue = GetOption(option);
    if(!OptionValue.empty()){
        return std::stof(OptionValue);
    }

    return -1; 
};

template<>
int ArgumentParser::GetOptionAs(const std::string& option) const
{
    const std::string& OptionValue = GetOption(option);
    if(!OptionValue.empty()){
        return std::stoi(OptionValue);
    }

    return -1; 
};

template<>
const std::string& ArgumentParser::GetOptionAs<const std::string&>(const std::string& option) const
{
    return GetOption(option);
};
