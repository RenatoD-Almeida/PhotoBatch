#ifndef _MODE_H
#define _MODE_H

#include <memory>
#include <filesystem>
#include <algorithm>
#include "argumentParser.hpp"

    class Mode
    {       
        private:
            std::string m_Folder;
            std::string m_Filter;
        protected:
            virtual void runImpl() = 0;
        
        public:
            Mode(const std::string& Folder, const std::string& Filter);
            
            const std::string& getFilter() const;
            const std::string& getFolder() const;

            virtual const std::string& getModeName() const = 0;

            void Run();
    };

    class RenameMode final : public Mode
    {
        public:
            RenameMode(const std::string& Folder, const std::string& Filter, const std::string Prefix, const int StartNumber);  
            const std::string& getModeName() const override;

        protected:
            void runImpl() override;

        private:
            std::string     m_Prefix;
            int             m_StartNumber;
    };

    std::unique_ptr<Mode> createMode(const ArgumentParser& argParser);

#endif