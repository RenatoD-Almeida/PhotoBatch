#include "argumentParser.hpp"
#include <algorithm>
#include <array>
#include <filesystem>

// ============================ Registram flags e Opções necessárias!
void RegisterApiFlags(class ArgumentParser& ap);
void RegisterApiOptions(class ArgumentParser& ap);

// ============================ Valida os argumentos passados via linha de comando!
void ValidateArgs(const ArgumentParser& argParser);

#ifdef dev
    void print_flags(ArgumentParser& ArgParser);
#endif


int main(int argc, char* argv[]){

    ArgumentParser ArgParser;

    RegisterApiFlags(ArgParser);
    RegisterApiOptions(ArgParser);

    

    try
    {
        ArgParser.Parser(argc, argv);
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

/* ============================ Validação Argumentos ============================ */

void ValidateArgs(const ArgumentParser& argParser) 
{
    const bool bRename = argParser.GetFlag(Args::Flags::Rename);
    const bool bConvert = argParser.GetFlag(Args::Flags::Convert);
    const bool bResize = argParser.GetFlag(Args::Flags::Resize);
    const bool bScale = argParser.GetFlag(Args::Flags::Scale);
    const bool bHelp = argParser.GetFlag(Args::Flags::Help);

    /* ---------------------------- Validação da flag Help ---------------------------- */
    if(bHelp)
    {
        if((bRename ^ bConvert ^ bResize ^ bScale))  /* ---------------------------- Help com flag ativa */        
        {
            if(bRename)
            {
                utility::helpGetMessage(Args::Flags::i_RENAME);
            }else if(bConvert)
            {
                utility::helpGetMessage(Args::Flags::i_CONVERT);
            }else if(bResize)
            {
                utility::helpGetMessage(Args::Flags::i_RESIZE);
            }else
            {
                utility::helpGetMessage(Args::Flags::i_SCALE);
            }
            return;
        }else /* ---------------------------- Help com nenhum flag ativa */
        {
            utility::helpGetMessage(Args::Flags::i_NOARGS);
            return;
        }
    }

    /* ---------------------------- Validação das flags ativas ---------------------------- */
    if(!(bRename || bConvert || bResize || bScale))
    {
        throw std::invalid_argument("Pelo menos uma opcao tem de estar ativa!!\n");
    }
    
    if(!(bRename ^ bConvert ^ bResize ^ bScale))
    {
        throw std::invalid_argument("Ha mais de uma flag/opcao ativa!!\n");
    }

    /*           -> -> Folder e Filter são necessárias em todas as flags <- <-              */
    /* ---------------------------- Validação do folder~ ---------------------------- */
    const std::string folder = argParser.GetOptionAs<std::string>(Args::Options::Folder);
    if(folder.empty())
    {
        throw std::invalid_argument("O diretorio da pasta nao pode estar vazia!\n");
    }
    
    if(!std::filesystem::exists(folder))
    {
        throw std::invalid_argument("A pasta informada nao existe!\n");
    }

    /* ---------------------------- Validação do filter~ ---------------------------- */
    const std::string filter = argParser.GetOptionAs<std::string>(Args::Options::Filter);
    if(!utility::validateString(filter))
    {
        throw std::invalid_argument("Ha argumentos invalidos no filtro: \'\\/*?:\"<>|\'\n");
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
        }catch(const std::invalid_argument&)
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

    /* ---------------------------- Validação da flag Scale ---------------------------- */
    if(bScale)
    {
        float amount = 0.0f;
        try
        {
            amount = argParser.GetOptionAs<float>(Args::Options::Amount);
        }
        catch(const std::exception&)
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
    /* ---------------------------- Validação da flag Rename ---------------------------- */
    if(bRename)
    {
        std::string prefix = argParser.GetOptionAs<std::string>(Args::Options::Prefix);
        if(prefix.empty())
        {
            throw std::invalid_argument("O prefixo nao pode estar vazio no modo Rename!");
        }
        if(!utility::validateString(prefix))
        {
            throw std::invalid_argument("Nao pode haver caracteres especiais no prefix: \'\\/*?:\"<>|\'");
        }

        int startNumber = 0;
        try
        {
            startNumber = argParser.GetOptionAs<int>(Args::Options::StartNumber);
        }
        catch(const std::invalid_argument&)
        {
            throw std::invalid_argument("O Start Number tem de ser um numero no modo Rename");
        }
        if(startNumber < 0)
        {
            throw std::invalid_argument("StartNumber nao pode ser menor que 0 no modo Rename");
        }        
    }
    /* ---------------------------- Validação da flag Convert ---------------------------- */
    if(bConvert)
    {
        const std::string to = argParser.GetOptionAs<std::string>(Args::Options::To);
        const std::string from = argParser.GetOptionAs<std::string>(Args::Options::From);
        const std::array<std::string, 2> extension = {"png", "jpg"};
        if(!(to.empty()) && !(from.empty()))
        {
            const bool bValidFrom = (std::find(std::begin(extension), std::end(extension), from) != std::end(extension));
            const bool bValidTo = (std::find(std::begin(extension), std::end(extension), to) != std::end(extension));
            if(!(bValidFrom) || !(bValidTo))
            {
                throw std::invalid_argument("To e From tem de estar na lista de extension cadastradas : <png|jpg>");    
            }
            if(from == to)
            {
                throw std::invalid_argument("To e From nao podem ser iguais!\n.");    
            }
        }else
        {
            throw std::invalid_argument("To e From nao podem estar vazios no modo Convert");
        }
    }

}

#ifdef dev
void print_flags(ArgumentParser& ArgParser)
{
    std::cout << std::endl;
    std::cout << std::boolalpha << "HELP    : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Help) << std::endl;
    std::cout << std::endl;
    std::cout << "---- Flags" << std::endl;
    std::cout << std::boolalpha << "rename  : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Rename) << std::endl;
    std::cout << std::boolalpha << "convert : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Convert) << std::endl;
    std::cout << std::boolalpha << "resize  : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Resize) << std::endl;
    std::cout << std::boolalpha << "scale   : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Scale) << std::endl;
    std::cout << std::endl << "---- Option Gerais" << std::endl;
    std::cout << "folder  : "  << std::setw(10) << ArgParser.GetOptionAs<std::string>(Args::Options::Folder) << std::endl;
    std::cout << "filter  : "  << std::setw(10) << ArgParser.GetOptionAs<std::string>(Args::Options::Filter) << std::endl;
    std::cout << std::endl << "---- Option Flags" << std::endl;
    std::cout << "width   : "  << std::setw(10) << ArgParser.GetOptionAs<int>(Args::Options::Width) << std::endl;
    std::cout << "Height  : "  << std::setw(10) << ArgParser.GetOptionAs<int>(Args::Options::Height) << std::endl;
    std::cout << "Amount  : "  << std::setw(10) << ArgParser.GetOptionAs<float>(Args::Options::Amount) << std::endl;
    std::cout << "Prefix  : "  << std::setw(10) << ArgParser.GetOptionAs<std::string>(Args::Options::Prefix) << std::endl;
    std::cout << "StartNumber: "  << std::setw(7) << ArgParser.GetOptionAs<int>(Args::Options::StartNumber) << std::endl;
    std::cout << "To      : "  << std::setw(10) << ArgParser.GetOptionAs<std::string>(Args::Options::To) << std::endl;
    std::cout << "From    : "  << std::setw(10) << ArgParser.GetOptionAs<std::string>(Args::Options::From) << std::endl;
    std::cout << std::endl;
}
#endif

/* ============================ Registrando flags ============================ */
void RegisterApiFlags(class ArgumentParser& ap)
{
    ap.RegisterFlag(Args::Flags::Rename);
    ap.RegisterFlag(Args::Flags::Convert);
    ap.RegisterFlag(Args::Flags::Resize);
    ap.RegisterFlag(Args::Flags::Scale);
    
    ap.RegisterFlag(Args::Flags::Help);

}
/* ============================ Registrando Option ============================ */ 
void RegisterApiOptions(class ArgumentParser& ap)
{
    ap.RegisterOption(Args::Options::Folder);
    ap.RegisterOption(Args::Options::Filter);
    ap.RegisterOption(Args::Options::Width);
    ap.RegisterOption(Args::Options::Height);
    ap.RegisterOption(Args::Options::Amount);
    ap.RegisterOption(Args::Options::Prefix);
    ap.RegisterOption(Args::Options::StartNumber);
    ap.RegisterOption(Args::Options::To);
    ap.RegisterOption(Args::Options::From);
}