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
            T GetOptionAs(const std::string& option) const{ return GetOptionAs(option, T());}
        
        private:
            // Mapeamento das flags e opções
            std::map<std::string, bool> m_Flags;
            std::map<std::string, std::string> m_Options;

            //Option
            const std::string& GetOption(const std::string& option) const;
            
            float GetOptionAs(const std::string& option, float) const;
            int GetOptionAs(const std::string& option, int) const;
            std::string GetOptionAs(const std::string& option, std::string) const;
    };


#endif