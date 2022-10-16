#include "argumentParser.hpp"
#include <filesystem>

// ============================ Registram flags e Opções necessárias!
void RegisterApiFlags(class ArgumentParser& ap);
void RegisterApiOptions(class ArgumentParser& ap);

// ============================ Valida os argumentos passados via linha de comando!
void ValidateArgs(const ArgumentParser& argParser);

#ifdef dev
    void print_flags(ArgumentParser& ArgParser);
#endif

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
        static constexpr const char* Width = "width";
        static constexpr const char* Height = "height";
        static constexpr const char* Amount = "amount";
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
        print_flags(ArgParser);
    #endif


    return 0;
}

/* ============================ Registrando flags ============================ */
void RegisterApiFlags(class ArgumentParser& ap)
{
    ap.RegisterFlag(Args::Flags::Rename);
    ap.RegisterFlag(Args::Flags::Convert);
    ap.RegisterFlag(Args::Flags::Resize);
    ap.RegisterFlag(Args::Flags::Scale);
}
/* ============================ Registrando Option ============================ */ 
void RegisterApiOptions(class ArgumentParser& ap)
{
    ap.RegisterOption(Args::Options::Folder);
    ap.RegisterOption(Args::Options::Filter);
    ap.RegisterOption(Args::Options::Width);
    ap.RegisterOption(Args::Options::Height);
    ap.RegisterOption(Args::Options::Amount);
}

/* ============================ Validação Argumentos ============================ */
void ValidateArgs(const ArgumentParser& argParser) 
{
    const bool bRename = argParser.GetFlag(Args::Flags::Rename);
    const bool bConvert = argParser.GetFlag(Args::Flags::Convert);
    const bool bResize = argParser.GetFlag(Args::Flags::Resize);
    const bool bScale = argParser.GetFlag(Args::Flags::Scale);

    /* ---------------------------- Validação das flags ativas ---------------------------- */

    if(!(bRename ^ bConvert ^ bResize ^ bScale))
    {
        throw std::invalid_argument("Ha mais de uma flag/opcao ativa!!\n");
    }

    /* -> -> Folder e Filter são necessárias em todas as flags <- <- */
    /* ---------------------------- Validação do folder ---------------------------- */

    const std::string folder = argParser.GetOptionAs<const std::string&>(Args::Options::Folder);
    if(folder.empty())
    {
        throw std::invalid_argument("O diretorio da pasta nao pode estar vazia!\n");
    }
    
    if(!std::filesystem::exists(folder))
    {
        throw std::invalid_argument("A pasta informada nao existe!\n");
    }
    /* ---------------------------- Validação do filter ---------------------------- */
    const std::string filter = argParser.GetOptionAs<const std::string&>(Args::Options::Filter);
    if(!utility::validateString(filter))
    {
        throw std::invalid_argument("Ha argumentos invalidos no filtro!\n");
    }

    /* ---------------------------- Validação da flag Resize ---------------------------- */
    if(bResize)
    {
        int Width = 0;
        int Height = 0;
        try
        {
            Width = argParser.GetOptionAs<int>(Args::Options::Width);
            Height = argParser.GetOptionAs<int>(Args::Options::Height);
        }catch(const std::invalid_argument& exception)
        {
            throw std::invalid_argument("Width ou Height tem de ser um numero");
        }
        
        if(Width <= 0 || Height <= 0)
        {
            throw std::invalid_argument("Width ou Height sao iguais ou menores que zero, Nao pode!!\n");    
        }
        if(filter.empty())
        {
            throw std::invalid_argument("O Filtro nao pode estar vazio no modo resize!\n");
        }
    }

    /* ---------------------------- Validação da flag Resize ---------------------------- */
    if(bScale)
    {
        float amount = 0.0f;
        try
        {
            amount = argParser.GetOptionAs<float>(Args::Options::Amount);
        }
        catch(const std::exception& exception)
        {
            std::invalid_argument("A opcao amount precisa ser um numero!\n");
        }
        if(amount <= 0)
        {
            throw std::invalid_argument("A opcao amount precisa ser maior que 0");
        }
        if(filter.empty())
        {
            throw std::invalid_argument("O Filter nao pode estar vazio na flag Scale");
        }
    }
}

#ifdef dev
void print_flags(ArgumentParser& ArgParser)
{
    std::cout << std::endl;
    std::cout << std::boolalpha << "nrename  : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Rename) << std::endl;
    std::cout << std::boolalpha << "convert : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Convert) << std::endl;
    std::cout << std::boolalpha << "resize  : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Resize) << std::endl;
    std::cout << std::boolalpha << "scale   : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Scale) << std::endl;
    std::cout << "folder  : "  << std::setw(10) << ArgParser.GetOptionAs<const std::string&>(Args::Options::Folder) << std::endl;
    std::cout << "filter  : "  << std::setw(10) << ArgParser.GetOptionAs<const std::string&>(Args::Options::Filter) << std::endl;
    std::cout << "width   : "  << std::setw(10) << ArgParser.GetOptionAs<int>(Args::Options::Width) << std::endl;
    std::cout << "Height  : "  << std::setw(10) << ArgParser.GetOptionAs<int>(Args::Options::Height) << std::endl;
    std::cout << "Amount  : "  << std::setw(10) << ArgParser.GetOptionAs<float>(Args::Options::Amount) << std::endl;
    std::cout << std::endl;
}
#endif