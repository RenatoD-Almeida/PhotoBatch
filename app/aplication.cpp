#include "argumentParser.hpp"
#include <filesystem>

// ============================ Registram flags e Opções necessárias!
void RegisterApiFlags(class ArgumentParser& ap);
void RegisterApiOptions(class ArgumentParser& ap);

// ============================ Valida os argumentos passados via linha de comando!
void ValidateArgs(const ArgumentParser& argParser);


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
    ap.RegisterFlag(Args::Flags::Rename);
    ap.RegisterFlag(Args::Flags::Convert);
    ap.RegisterFlag(Args::Flags::Resize);
    ap.RegisterFlag(Args::Flags::Scale);
}

void RegisterApiOptions(class ArgumentParser& ap)
{
    ap.RegisterOption(Args::Options::Folder);
    ap.RegisterOption(Args::Options::Filter);
}

void ValidateArgs(const ArgumentParser& argParser) 
{
    const bool bRename = argParser.GetFlag(Args::Flags::Rename);
    const bool bConvert = argParser.GetFlag(Args::Flags::Convert);
    const bool bResize = argParser.GetFlag(Args::Flags::Resize);
    const bool bScale = argParser.GetFlag(Args::Flags::Scale);                      // Option: Folder e Filter necessárias 
                                                                                    // para todas as flags
    /* ============================ Validação das flags ============================*/

    if(!(bRename ^ bConvert ^ bResize ^ bScale))
    {
        throw std::invalid_argument("Ha mais de uma flag/opcao ativa!!\n");
    }

    /* ============================ Validação do folder ============================ */

    const std::string folder = argParser.GetOptionAs<const std::string&>(Args::Options::Folder);
    if(folder.empty())
    {
        throw std::invalid_argument("O diretorio da pasta nao pode estar vazia!\n");
    }
    
    if(!std::filesystem::exists(folder))
    {
        throw std::invalid_argument("A pasta informada nao existe!\n");
    }
    /* ============================ Validação do filter ============================ */
    const std::string filter = argParser.GetOptionAs<const std::string&>(Args::Options::Filter);
    if(!utility::validateString(filter))
    {
        throw std::invalid_argument("Ha argumentos invalidos no filtro!\n");
    }

}