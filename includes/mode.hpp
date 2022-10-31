#ifndef _MODE_H
#define _MODE_H

#include <memory>
#include <filesystem>
#include <algorithm>
#include "argumentParser.hpp"


/* ============================ Class Mode ============================ */
    class Mode
    {       

        std::string m_Folder;
        std::string m_Filter;

        protected:
            virtual void runImpl() = 0;                                 //IMPLEMENTAR EM TODAS AS CLASSES
            std::vector<std::filesystem::path> getFiles(const std::filesystem::path& extension = "") const;
        
        public:
            Mode(const std::string& Folder, const std::string& Filter);
            
            const std::string& getFilter() const;
            const std::string& getFolder() const;

            virtual const std::string& getModeName() const = 0;         //IMPLEMENTAR EM TODAS AS CLASSES

            void Run();
    };

/* ============================ Class RenameMode ============================ */

    class RenameMode final : public Mode
    {
        std::string     m_Prefix;
        int             m_StartNumber;

        protected:
            void runImpl() override;
            
        public:
            RenameMode(const std::string& Folder, const std::string& Filter, const std::string Prefix, const int StartNumber);  
            const std::string& getModeName() const override;
    };

/* ============================ Class ConvertMode ============================ */

    class ConvertMode final : public Mode
    {

        protected:
            void runImpl() override;
        
        public:

            ConvertMode(const std::string& Folder, const std::string& Filter, const std::string& fromFormat, const std::string& toFormat);
            const std::string& getModeName() const override;
        
        private:
            std::string m_From;
            std::string m_To;
            
    };

/* ============================ Class Resize ============================ */

    class ResizeMode final : public Mode
    {
        int m_Width;
        int m_Height;
    
    public:
        ResizeMode(const std::string& Folder, const std::string& Filter, int Width, int Height);
        const std::string& getModeName() const override;
    

    protected:
        void runImpl() override;
        
    };
    std::unique_ptr<Mode> CreateMode(const ArgumentParser& argParser);

#endif