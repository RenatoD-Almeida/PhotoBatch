#include "utility.hpp"
#include <fstream>

#include<ctime>

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
                std::cout << "\t - chamada:\n\n\t\t./Photobatch --rename --folder:\"/home/<username>/<workfolder>\" --filter=\".jpg\" --prefix=\"image_\" --StartNumber=0\n\n";
                std::cout << "\t - Digamos que tenha arquivos .jpg em um folder, o Photobatch ira renomear os arquivos usando o <prefix + StartNumber>" << std::endl;
                std::cout << "\n\n\t\t <image_0>, <image_1>, <image_2> ...\n\n";
                std::cout << "FLAG: --convert\n\n";
                std::cout << "\t - chamada:\n\n\t\t./Photobatch --convert --folder:\"/home/<username>/<workfolder>\" --filter=\".jpg\" --from=\"jpg\" --to=\"png\"\n\n";
                std::cout << "\t - Digamos que tenha arquivos .jpg em um folder, o Photobatch ira converter os arquivos usando o <from|to>" << std::endl;
                std::cout << "\n\tFrom:";
                std::cout << "\n\n\t\t <image_1.jpg>, <image_2.jpg>, <image_3.jpg> ...\n";
                std::cout << "\n\tTo:";
                std::cout << "\n\n\t\t <image_1.png>, <image_2.png>, <image_3.png> ...\n\n";
                std::cout << "FLAG: --Resize\n\n";
                std::cout << "\t - chamada:\n\n\t\t./Photobatch --resize --folder:\"/home/<username>/<workfolder>\" --filter=\".jpg\" --width=1280 --height=720\n\n";
                std::cout << "\t - Digamos que tenha arquivos .jpg em um folder,Com dimensoes 680x440, o Photobatch ira redimensionar os arquivos usando o <width|height>" << std::endl;
                std::cout << "\n\tAntes:";
                std::cout << "\n\t\t <image_1.jpg> : 680x440...\n";
                std::cout << "\n\tDepois:";
                std::cout << "\n\t\t <image_1.jpg> : 1280x720...\n\n";
                std::cout << "FLAG: --scale\n\n";
                std::cout << "\t - chamada:\n\n\t\t./Photobatch --scale --folder:\"/home/<username>/<workfolder>\" --filter=\".jpg\" --amout=0.5\n\n";
                std::cout << "\t - Digamos que tenha arquivos .jpg em um folder, com dimensoes 680x440, o Photobatch ira redimensionar os arquivos usando o <amount> atraves de escala" << std::endl;
                std::cout << "\n\tAntes:";
                std::cout << "\n\t\t <image_1.jpg> : 1280x720...\n";
                std::cout << "\n\tDepois:";
                std::cout << "\n\t\t <image_1.jpg> : 640x360...\n\n";
                break;
        }
        std::cout << "\nEnter para continuar: "; getchar();
    }

    void getLogError(Args::Flags::flagsEnum FlagsEnum, Args::Flags::FlagsEnumError FlagsError)
    {
        std::ofstream fout; char buffer[80];
        fout.open("LogError.txt", std::ios::app);

        time_t tt; struct tm *infoTime;

        time(&tt);
        infoTime = localtime(&tt);
        strftime(buffer, 80, "%c", infoTime);
        fout << buffer << "----------------------" << "\n";

        switch(FlagsEnum)
        {
            case Args::Flags::i_RENAME:
                fout << "Mode:------ FLAGS: RENAME\t";
                break;
            case Args::Flags::i_CONVERT:
                fout << "Mode:------ FLAGS: CONVERT\t";
                break;
            case Args::Flags::i_RESIZE:
                fout << "Mode:------ FLAGS: RESIZE\t";
                break;
            case Args::Flags::i_SCALE:
                fout << "Mode:------ FLAGS: SCALE\t";
                break;
            case Args::Flags::i_NOARGS:
                fout << "Mode:------ ";
                break;                
            default:
                break;

        }

        switch(FlagsError)
        {
            //   -------- Option Folder
            case Args::Flags::i_EmptyFolder:
                fout << "OPTION\tERRO : < Folder > Vazio.\n\n";
                break;
            case Args::Flags::i_FolderNotExists:
                fout << "OPTION\tERRO : < Folder > Nao existe.\n\n";
                break;

            //   -------- Option Filter
            case Args::Flags::i_InvalidFilter:
                fout << "OPTION\tERRO : Caracteres Invalidos no Argumento < Filter > Vazio.\n\n";
                break;

            //   -------- Flags 
            case Args::Flags::i_NoFlags:
                fout << "FLAGS\tERRO : Nenhuma Flag ativa.\n\n";
                break;
            case Args::Flags::i_FlagsALot:
                fout << "FLAGS\tERRO : Mais de uma flag ativa.\n\n";
                break;

            //  -------- --------
            //  -------- Rename
            case Args::Flags::i_EmptyPrefix:
                fout << "ERRO : < Prefixo > Vazio.\n\n";
                break;
            case Args::Flags::i_InvalidPrefix:
                fout << "ERRO : Caracteres Invalidos no argumento < PREFIX >.\n\n";
                break;
            case Args::Flags::i_InvalidTypeStartNumber:
                fout << "ERRO : Tipo invalido < StartNumber > \"not a number\" \n\n";
                break;
            case Args::Flags::i_StartNumberLessEqualZero:
                fout << "ERRO : O argumento de < StartNumber > menor do que 0 \n\n";
                break;    

            //  -------- Convert
            case Args::Flags::i_FromToInvalidExtension:
                fout << "ERRO : Argumetos de < To > ou < From > nao estao cadastrados nas opcoes.\n\n";
                break;
            case Args::Flags::i_FromAndToEqual:
                fout << "ERRO : Argumetos de < To > ou < From > sao Iguais.\n\n";
                break;
            case Args::Flags::i_EmptyFromTo:
                fout << "ERRO : < To > ou < From > Vazios.\n\n";
                break; 

            //  -------- Resize
            case Args::Flags::i_InvalidTypeWidthHeight:
                fout << "ERRO : Tipo invalido <Width> ou <Height> \"not a number\"\n\n";
                break;
            case Args::Flags::i_WidthHeightLessThanZero:
                fout << "ERRO : Argumetos de < Width > ou < Height > Menores ou iguais a 0.\n\n";
                break;
            case Args::Flags::i_ResizeNoFilter:
                fout << "ERRO : Option < Filtro > esta vazio.\n\n";
                break;
            
            //  -------- Scale
            case Args::Flags::i_InvalidTypeAmount:
                fout << "ERRO : Tipo Invalido < Amount > \"Not a number\"\n\n";
                break;
            case Args::Flags::i_AmountLessEqualZero:
                fout << "ERRO : Argumetos de < Amount > Menor ou igual a 0.\n\n";
                break;
            case Args::Flags::i_ScaleNoFilter:
                fout << "ERRO : Option < Filtro > esta vazio.\n\n";
                break;
        }


        fout.close();
    }
}
