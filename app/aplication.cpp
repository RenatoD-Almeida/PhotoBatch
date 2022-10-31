#include "mode.hpp"
#include <stb_image.h>

// ============================ Registram flags e Opções necessárias!
void RegisterApiFlags(class ArgumentParser& ap);
void RegisterApiOptions(class ArgumentParser& ap);

#ifdef dev
    void print_flags(ArgumentParser& ArgParser);
#endif


int main(int argc, char* argv[]){

    ArgumentParser ArgParser;

    RegisterApiFlags(ArgParser);
    RegisterApiOptions(ArgParser);

    #ifdef dev
        std::cout << "\n\n------ Relatorio ------\n";
    #endif

    try
    {
        ArgParser.Parser(argc, argv);
        std::unique_ptr PhotoBatchMode = CreateMode(ArgParser);
        PhotoBatchMode->Run();
    }catch(const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
    }

    #ifdef dev
        print_flags(ArgParser);
    #endif


    return 0;
}

#ifdef dev
void print_flags(ArgumentParser& ArgParser)
{
    std::cout << "\n\n------ Relatorio FLAGS n OPTIONS ------\n";
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