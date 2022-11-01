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
            RenameMode(const std::string&, const std::string&, const std::string, const int);  
            const std::string& getModeName() const override;
    };

/* ============================ Class ConvertMode ============================ */

    class ConvertMode final : public Mode
    {
        std::string m_From;
        std::string m_To;

        protected:
            void runImpl() override;
        
        public:

            ConvertMode(const std::string&, const std::string&, const std::string&, const std::string&);
            const std::string& getModeName() const override;

            
    };

/* ============================ Class Resize ============================ */

    class ResizeMode : public Mode
    {
        int m_Width;
        int m_Height;
    
    public:
        ResizeMode(const std::string&, const std::string&, int, int);
        const std::string& getModeName() const override;
        void ResizeImage(const std::filesystem::path&, int, int) const;

    protected:
        void runImpl() override;

    };

/* ============================ Class Scale ============================ */
    class ScaleMode final: public ResizeMode
    {
        float m_Amount;
    public:
        ScaleMode(const std::string&, const std::string&, float);
        const std::string& getModeName() const override;
    protected:
        void runImpl() override;
    };

    std::unique_ptr<Mode> CreateMode(const ArgumentParser& argParser);

#endif