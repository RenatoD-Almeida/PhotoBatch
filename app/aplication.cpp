#include "argumentParser.hpp"
#include <filesystem>

void RegisterApiFlags(class ArgumentParser& ap);
void RegisterApiOptions(class ArgumentParser& ap);


//descobrir como usar namespaces e por que do constexpr
namespace Args
{
    namespace Flags
    {
        static constexpr const char* Rename = "rename";
        static constexpr const char* Convert = "convert";
        static constexpr const char* Resize = "resize";
        static constexpr const char* Scale = "scale"; 
    }
    namespace Options
    {
        static constexpr const char* Folder = "folder";
        static constexpr const char* Filter = "filter";   
    }
}

void ValidateArgs(const ArgumentParser& argParser) 
{
    const bool bRename = argParser.GetFlag(Args::Flags::Rename);
    const bool bConvert = argParser.GetFlag(Args::Flags::Convert);
    const bool bResize = argParser.GetFlag(Args::Flags::Resize);
    const bool bScale = argParser.GetFlag(Args::Flags::Scale);

    if(!(bRename ^ bConvert ^ bResize ^ bScale))
    {
        throw std::invalid_argument("Ha mais de uma flag/opcao ativa!!\n");
    }

    const std::string folder = argParser.GetOptionAs<const std::string&>(Args::Options::Folder);
    if(folder.empty())
    {
        throw std::invalid_argument("O diretorio da pasta nao pode estar vazia!\n");
    }
    
    if(!std::filesystem::exists(folder))
    {
        throw std::invalid_argument("A pasta informada nao existe!\n");
    }
}

int main(int argc, char* argv[]){

    ArgumentParser ArgParser;

    RegisterApiFlags(ArgParser);
    RegisterApiOptions(ArgParser);

    ArgParser.Parser(argc, argv);

    try
    {
        ValidateArgs(ArgParser);
    }catch(const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
    }

    #ifdef dev
        std::cout << std::boolalpha << "rename  : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Rename) << std::endl;
        std::cout << std::boolalpha << "convert : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Convert) << std::endl;
        std::cout << std::boolalpha << "resize  : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Resize) << std::endl;
        std::cout << std::boolalpha << "scale   : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Scale) << std::endl;
        std::cout << "folder  : "  << std::setw(10) << ArgParser.GetOptionAs<const std::string&>(Args::Options::Folder) << std::endl;
        std::cout << "filter  : "  << std::setw(10) << ArgParser.GetOptionAs<const std::string&>(Args::Options::Filter) << std::endl;
        std::string folder = ArgParser.GetOptionAs<const std::string&>(Args::Options::Folder);
    #endif


    return 0;
}


void RegisterApiFlags(class ArgumentParser& ap)
{
    ap.RegisterFlag("rename");
    ap.RegisterFlag("convert");
    ap.RegisterFlag("resize");
    ap.RegisterFlag("scale");
}

void RegisterApiOptions(class ArgumentParser& ap)
{
    ap.RegisterOption(Args::Options::Folder);
    ap.RegisterOption(Args::Options::Filter);
}