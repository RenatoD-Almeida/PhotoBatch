#include "argumentParser.hpp"

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
}

int main(int argc, char* argv[]){

    ArgumentParser ArgParser;

    RegisterApiFlags(ArgParser);
    RegisterApiOptions(ArgParser);

    ArgParser.Parser(argc, argv);

    std::cout << std::boolalpha << "rename  : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Rename) << std::endl;
    std::cout << std::boolalpha << "convert : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Convert) << std::endl;
    std::cout << std::boolalpha << "resize  : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Resize) << std::endl;
    std::cout << std::boolalpha << "scale   : " << std::setw(10) << ArgParser.GetFlag(Args::Flags::Scale) << std::endl;
    std::cout << "folder  : "  << std::setw(10) << ArgParser.GetOptionAs<const std::string&>("folder") << std::endl;
    std::cout << "amount  : "  << std::setw(10) << ArgParser.GetOptionAs<float>("amount") << std::endl;
    

    return 0;
}


void RegisterApiFlags(class ArgumentParser& ap){
    ap.RegisterFlag("rename");
    ap.RegisterFlag("convert");
    ap.RegisterFlag("resize");
    ap.RegisterFlag("scale");
}

void RegisterApiOptions(class ArgumentParser& ap){
    ap.RegisterOption("folder");
    ap.RegisterOption("amount");
}