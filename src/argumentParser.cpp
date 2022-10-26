#include "argumentParser.hpp"

float ArgumentParser::GetOptionAs(const std::string& option, float) const
{
    const std::string& OptionValue = GetOption(option);
    if(!OptionValue.empty()){
        return std::stof(OptionValue);
    }

    return -1; 
};

int ArgumentParser::GetOptionAs(const std::string& option, int) const
{
    const std::string& OptionValue = GetOption(option);
    if(!OptionValue.empty()){
        return std::stoi(OptionValue);
    }

    return -1; 
};

std::string ArgumentParser::GetOptionAs(const std::string& option, std::string) const
{
    return GetOption(option);
};

/* ============================ Flags Methods ============================ */
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

/* ============================ Options Methods ============================ */
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

/* ============================ Arg Methods ============================ */
void ArgumentParser::Parser(int argc, char* argv[])
{
    if(argc > 1){
        for(int i = 1 ; i < argc ; ++i)
        {
            std::string arg = argv[i];
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
                            std::string OptionKey = utility::ToLowerString(arg.substr(0, SignPos));
                            std::string OptionValue = arg.substr(SignPos + 1);
                            
                            auto OptionIt = m_Options.find(OptionKey);
                            if(OptionIt != std::end(m_Options))
                            {
                                OptionIt->second = OptionValue;
                            }
                        }
                    }else
                    {
                        //Flag
                        arg = utility::ToLowerString(arg);
                        auto FlagIt = m_Flags.find(arg);
                        if(FlagIt != std::end(m_Flags))
                        {
                            FlagIt->second = true;
                        } 
                    }
                }
            }else
            {
                throw std::invalid_argument("Opcao invalida: " + arg);
            }
        }
    }
}

