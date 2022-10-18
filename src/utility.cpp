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

    void helpGetMessage(Args::Flags::flagsEnum flagsEnum)
    {
        switch(flagsEnum)
        {
            case Args::Flags::i_RENAME:
                std::cout << "\nFLAG : trata-se de uma funcionalidade para automatizar a renomeacao de arquivos" << std::endl;
                std::cout << "\n\tOpcoes necessarias:\n" << std::endl;
                std::cout << "\t\t - Prefix        <string>  - Refere-se ao prefixo dos arquivos que deseja renomear." << std::endl;
                std::cout << "\t\t - StartNumber   <int>     - Refere-se a contagem do arquivo que sera iniciado o renomeamento" << std::endl;
                std::cout << "\n\tOpcoes gerais ( igualmente necessaria ):\n" << std::endl;
                std::cout << "\t\t - Folder        <string>  - Refere-se a pasta que esta funcionalidade ira trabalhar." << std::endl;
                std::cout << "\t\t - Filter        <string>  - Refere-se aos arquivos que esta funcionalidade ira trabalhar ." << std::endl;
                std::cout << "\n\tExemplo : \n\n";
                std::cout << "\n\tHa os seguintes arquivos em uma pasta:" << std::endl;
                std::cout << "\n\t< imagem_0 >, < imagem_1 >, < imagem_2 >, < imagem_3 >, < imagem_4 >\n" << std::endl;
                std::cout << "\tAo utilizar a flag rename com os seguintes parametros:\n\n";
                std::cout << std::setw(15) << "\t\t - Prefix        :     < a_ >" << std::endl;
                std::cout << std::setw(15) << "\t\t - StartNumber   :     < 2 >\n\n" << std::endl;
                std::cout << "\tSerao alterados, todas as imagens filtradas, para  (Prefix + StartNumber)\n";
                std::cout << "\t\t< a_2 >, < a_3 >, < a_4 >, < a_5 >, < a_6 >, < a_7 >\n\n\n";
                break;
            case Args::Flags::i_CONVERT:
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
                break;
            case Args::Flags::i_RESIZE:
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
                break;
            case Args::Flags::i_SCALE:
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
                break;
            default:
                std::cout << "\nPhotoBatch.\n" << std::endl;
                std::cout << "Ha quatro flags cadastradas no Photobatch, e sao elas:\n";
                std::cout << "\n\t--[rename]  : Automatiza o renomear de arquivos.\n";
                std::cout << "\n\t--[convert] : Converte a extensao de imagens. \n";
                std::cout << "\n\t--[resize]  : Redimensiona imagem por parametro\n";
                std::cout << "\n\t--[scale]   : Redimensiona imagem por escala\n";
                std::cout << "\nPara utilizar cada uma, sera necessario configurar os parametros necessarios.\n";
                std::cout << "Ha dois tipos de parametros: Gerais e Individuais.\n";
                std::cout << "\n----- Opt Geral -----\n\n";
                std::cout << "* Opts gerais sao utilizadas por todas as flags *\n\n";
                std::cout << "\t--[Folder] : seta a pasta que o Photobatch ira trabalhar. (aceita caminho relativo e absoluto)\n";
                std::cout << "\t--[Filter] : seta os arquivos que o Photobatch ira trabalhar\n\n";
                std::cout << "----- Opt Individual -----\n\n";
                std::cout << "FLAG: --rename\n\n";
                std::cout << "\t--[prefix]       : Configura um prefixo para o novo nome das imagens.\n";
                std::cout << "\t--[StartNumber]  : Configura um valor numerico para o novo nome das imagens.\n\n";
                std::cout << "FLAG: --convert\n\n";
                std::cout << "\t--[From]         : Configura a extensao do arquivo que sera convertido.\n";
                std::cout << "\t--[To]           : Configura a nova extensao do arquivo selecionado.\n\n";
                std::cout << "FLAG: --resize\n\n";
                std::cout << "\t--[Width]        : Configura a nova largura da imagem a ser redimensionada.\n";
                std::cout << "\t--[Height]       : Configura a nova altura da imagem a ser redimensionada.\n\n";
                std::cout << "FLAG: --scale\n\n";
                std::cout << "\t--[amout]        : Configura a quantidade do escalonamento da imagem.\n";
                std::cout << "\n ----- Exemplos -----\n\n";
                std::cout << "FLAG: --rename\n\n";
                std::cout << "chamada:\n\n./app/Photobatch --rename --folder:\"/home/<username>/<workfolder>\" --filter=\".jpg\" --prefix=\"imagem\" --StartNumber=0\n";
                break;
        }
        std::cout << "\nEnter para continuar: "; getchar();
    }
}











