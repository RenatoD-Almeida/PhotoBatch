#include "mode.hpp"
#include <iomanip>
#include <vector>

Mode::Mode(const std::string& Folder, const std::string& Filter):
m_Folder(Folder), m_Filter(Filter)
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

RenameMode::RenameMode(const std::string& Folder, const std::string& Filter, const std::string Prefix, const int StartNumber):
Mode(Folder, Filter), m_Prefix(Prefix), m_StartNumber(StartNumber){}

const std::string& RenameMode::getModeName() const
{
    static const std::string RenameModeName = "[Renomear] : ";
    return RenameModeName;
}

void RenameMode::runImpl()
{
    std::cout << "\n";
    std::cout << getModeName() << "Pasta         " << std::setw(20) << " : " << std::setw(15) << " " << this->getFolder() << std::endl;
    std::cout << getModeName() << "Filtro        " << std::setw(20) << " : " << std::setw(15) << " " << this->getFilter() << std::endl;
    std::cout << getModeName() << "Prefix        " << std::setw(20) << " : " << std::setw(15) << " " << this->m_Prefix << std::endl;
    std::cout << getModeName() << "Numero Inicial" << std::setw(20) << " : " << std::setw(15) << " " << this->m_StartNumber << std::endl;

    std::vector<std::filesystem::path> filesToRename;
    int numSkippedFiles = 0;

    //Coletar todos os arquivos que correspondem ao filtro
    for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(getFolder()))
    {
        const bool bIsFile = std::filesystem::is_regular_file(entry.path());
        const bool bMatchFilter = getFilter().empty() || (entry.path().string().find(getFilter()) != std::string::npos);
        if(bIsFile && bMatchFilter)
        {
            filesToRename.push_back(entry.path());
        }else
        {
            numSkippedFiles++;
        }
    }
    std::cout << std::endl;
    std::cout << getModeName() << "Numero de arquivos encontrados" << std::setw(3) << ":" << std::setw(17) << filesToRename.size() << std::endl;
    std::cout << getModeName() << "Numero de arquivos ignorados  " << std::setw(3) << ":" << std::setw(17) << numSkippedFiles << std::endl;
    std::cout << std::endl;

    int currentNumber = m_StartNumber;
    for(std::filesystem::path& filePath : filesToRename)
    {
        const std::filesystem::path extension = filePath.extension();
        const std::string newFileName = this->m_Prefix + std::to_string(currentNumber) + extension.string();

        std::filesystem::path newFilePath = filePath;
        newFilePath.replace_filename(newFileName);

        std::cout << getModeName() <<  filePath  << "  ->  " << newFilePath << std::endl;
        std::filesystem::rename(filePath, newFilePath);
        currentNumber++;
    }
    std::cout << std::endl;
}

/* ============================ Validação Argumentos ============================ */
std::unique_ptr<Mode> createMode(const ArgumentParser& argParser)
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
            return nullptr;
        }else /* ---------------------------- Help com nenhum flag ativa */
        {
            utility::helpGetMessage(Args::Flags::i_NOARGS);
            return nullptr;
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
        return std::make_unique<RenameMode>(folder, filter, prefix, startNumber);        
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

    return nullptr;
}