#ifndef _MODE_H
#define _MODE_H
#include <string>

    class Mode
    {       
        protected:
            std::string m_Folder;
            std::string m_Filter;

            virtual void runImpl() = 0;
        public:
            Mode(const std::string& Folder, const std::string& Filter);
            
            const std::string& getFilter() const;
            const std::string& getFolder() const;

            virtual const std::string& getModeName() const = 0;

            void Run();
    };

#endif