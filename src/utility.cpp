#include "utility.hpp"

namespace utility
{

    std::string ToLowerString(std::string str){
        for(char& c : str){
            c = std::tolower(c);
        }
        return str;
    }

    bool validateString(const std::string& string)
    {
        const std::string invalidCaracteres = "\\/*?:\"<>|";
        for(char c : string)
        {
            for(char _c : invalidCaracteres)
            {
                if(c == _c)
                {
                    return false;
                }
            }
        }
        return true;
    }

    void helpGetMessage(const std::string a, const bool flag=false)
    {
        if(flag)
        {
            std::cout << "\n\nHELP : " << "---- " << a << " ----" << std::endl;

            if(a == "rename")
            {
                std::cout << "\nFLAG : trata-se de uma funcionalidade para automatizar a renomeacao de arquivos" << std::endl;
                std::cout << "\n\tOpcoes necessarias:\n" << std::endl;
                std::cout << "\t\t - Prefix        <string>  - Refere-se ao prefixo dos arquivos que deseja renomear." << std::endl;
                std::cout << "\t\t - StartNumber   <int>     - Refere-se a contagem do arquivo que sera iniciado o renomeamento" << std::endl;
                std::cout << "\n\tOpcoes gerais ( igualmente necessaria ):\n" << std::endl;
                std::cout << "\t\t - Folder        <string>  - Refere-se a pasta que esta funcionalidade ira trabalhar." << std::endl;
                std::cout << "\t\t - Filter        <string>  - Refere-se aos arquivos que esta funcionalidade ira trabalhar ." << std::endl;
                std::cout << "\n\tExemplo : \n\n";
                std::cout << std::setw(15) << "\t - Prefix        :     < Imagem >" << std::endl;
                std::cout << std::setw(15) << "\t - StartNumber   :     < 2 >\n\n" << std::endl;
                std::cout << "Serao alterados, apartir do segundo, todos os arquivos que comecem com o prefixo \"Imagem\"\n\n\n";
            }
            if(a == "convert")
            {
                std::cout << "\n\tOpcoes necessarias:\n" << std::endl;
                std::cout << "\t\t - From    <string> - Refere-se a extensao do arquivo que deseja converter." << std::endl;
                std::cout << "\t\t - To      <string> - Refere-se a extensao do arquivo que sera convertido." << std::endl;
                std::cout << "\n\tOpcoes gerais ( igualmente necessaria ):\n" << std::endl;
                std::cout << "\t\t - Folder        <string>  - Refere-se a pasta que esta funcionalidade ira trabalhar." << std::endl;
                std::cout << "\t\t - Filter        <string>  - Refere-se aos arquivos que esta funcionalidade ira trabalhar ." << std::endl;
                std::cout << "\n\tExemplo : \n\n";
                std::cout << std::setw(15) << "\t\t - From   :     < png >" << std::endl;
                std::cout << std::setw(15) << "\t\t - To     :     < jpg >\n\n" << std::endl;
                std::cout << "Serao alterados, Os arquivos .png para .jpg\n\n\n";
            }
            if(a == "resize")
            {
                std::cout << "\nFLAG : trata-se de uma funcionalidade para redimensionar imagens via parametro" << std::endl;
                std::cout << "\n\tOpcoes necessarias:\n" << std::endl;
                std::cout << "\t\t - Width      <int> - Refere-se a extensao do arquivo que deseja converter." << std::endl;
                std::cout << "\t\t - Height     <int> - Refere-se a extensao do arquivo que sera convertido." << std::endl;
                std::cout << "\n\tOpcoes gerais ( igualmente necessaria ):\n" << std::endl;
                std::cout << "\t\t - Folder        <string>  - Refere-se a pasta que esta funcionalidade ira trabalhar." << std::endl;
                std::cout << "\t\t - Filter        <string>  - Refere-se aos arquivos que esta funcionalidade ira trabalhar ." << std::endl;
                std::cout << "\n\tExemplo : \n\n";
                std::cout << std::setw(15) << "\tDigamos que uma imagem tenha as seguintes dimensoes: 1380x820" << std::endl;
                std::cout << std::setw(15) << "\tAo utilizar a flag resize usando o seguinte parametro\n" << std::endl;
                std::cout << std::setw(15) << "\t\t - Width   :     < 720 >" << std::endl;
                std::cout << std::setw(15) << "\t\t - Height  :     < 680 >\n\n" << std::endl;
                std::cout << "\tserá gerado uma imagem com as dimensoes de: 720x680\n\n\n";
            }
            if(a == "scale")
            {
                std::cout << "\nFLAG : trata-se de uma funcionalidade para redimensionar imagens via escala" << std::endl;
                std::cout << "\n\tOpcoes necessarias:\n" << std::endl;
                std::cout << "\t\t - Amount      <float> - Ao valor que será reescalado as dimensoes do arquivo" << std::endl;
                std::cout << "\n\tOpcoes gerais ( igualmente necessaria ):\n" << std::endl;
                std::cout << "\t\t - Folder        <string>  - Refere-se a pasta que esta funcionalidade ira trabalhar." << std::endl;
                std::cout << "\t\t - Filter        <string>  - Refere-se aos arquivos que esta funcionalidade ira trabalhar ." << std::endl;
                std::cout << "\n\tExemplo : \n\n";
                std::cout << std::setw(15) << "\tDigamos que uma imagem tenha as seguintes dimensoes: 1380x820" << std::endl;
                std::cout << std::setw(15) << "\tAo utilizar a flag scale usando o seguinte parametro\n" << std::endl;
                std::cout << std::setw(15) << "\t\tCaso 1:" << std::endl;
                std::cout << std::setw(15) << "\t\t\t - Amout   :     < 0.5 >\n" << std::endl;
                std::cout << "\tSera gerado uma imagem redimensionada com a metade das dimensoes da imagem original 690x410\n\n";
                std::cout << std::setw(15) << "\t\tCaso 2:" << std::endl;
                std::cout << std::setw(15) << "\t\t\t - Amout   :     < 2 >\n" << std::endl;
                std::cout << "\tSera gerado uma imagem redimensionada com o dobro das dimensoes da imagem original 2760x1640\n\n";
            }
        }else
        {
            std::cout << "HELP : >>> GERAL <<<" << std::endl;
        }
    }
}











