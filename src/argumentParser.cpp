#include "argumentParser.hpp"

void ArgumentParser::RegisterFlag(const std::string& Flag)
{
    if(!(Flag.empty()))
    {
        m_Flags[Flag] = false;
    }
}

bool ArgumentParser::GetFlag(const std::string& Flag) const
{
    if(!Flag.empty())
    {
        auto it = m_Flags.find(Flag);
        if(it != std::end(m_Flags))
        {
            return it->second;
        }
    }
    return false;
}

void ArgumentParser::Parser(int argc, char* argv[])
{
    if(argc > 1){
        for(int i = 1 ; i < argc ; ++i)
        {
            std::string arg = utility::ToLowerString(argv[i]);
            if(arg.length() >= 3)
            {
                if(arg[0] == '-' && arg[1] == '-')
                {
                    arg = arg.substr(2);
                    if(arg.find_first_of('=') != std::string::npos)
                    {
                        //Option:
                        const size_t SignPos = arg.find('=');
                        if(SignPos != std::string::npos)
                        {
                            std::string OptionKey = arg.substr(0, SignPos);
                            std::string OptionValue = arg.substr(SignPos + 1);
                            
                            auto OptionIt = m_Options.find(OptionKey);
                            if(OptionIt != std::end(m_Options))
                            {
                                OptionIt->second = OptionValue;
                            }
                        }
                    }else{
                        //Flag
                        auto FlagIt = m_Flags.find(arg);
                        if(FlagIt != std::end(m_Flags))
                        {
                            FlagIt->second = true;
                        } 
                    }
                }
            }
        }
    }
}

void ArgumentParser::RegisterOption(const std::string& option)
{
    if(!option.empty())
    {
        m_Options[option] = "";
    }
}

const std::string& ArgumentParser::GetOption(const std::string& option) const
{
    if(!option.empty())
    {
        auto it = m_Options.find(option);
        if(it != std::end(m_Options))
        {
            return it->second;           
        }
    }
    static std::string EmptyOption = "";
    return EmptyOption;
}