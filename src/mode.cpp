#include "mode.hpp"

Mode::Mode(const std::string& Folder, const std::string& Filter) : m_Folder(Folder), m_Filter(Filter)
{

}

const std::string& Mode::getFilter() const
{
    return m_Filter;
}

const std::string& Mode::getFolder() const
{
    return m_Folder;
}

void Mode::Run()
{
    //Medir quanto tempo a operação levou.
    runImpl();
}