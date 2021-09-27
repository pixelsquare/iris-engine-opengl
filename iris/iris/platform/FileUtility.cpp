#include "platform\FileUtility.h"
#include "base\Data.h"

IRIS_BEGIN

FileUtility *FileUtility::s_sharedInstance = nullptr;

FileUtility::FileUtility()
{
}

FileUtility::~FileUtility()
{
}

std::string FileUtility::convertPathToUnixFormat(const std::string p_path)
{
    std::string retVal = p_path;
    for(unsigned int i = 0; i < retVal.length(); ++i)
    {
        if(retVal[i] == '\\')
        {
            retVal[i] = '/';
        }
    }

    return retVal;
}

std::string FileUtility::convertPathToWinFormat(const std::string p_path)
{
    std::string retVal = p_path;
    for(unsigned int i = 0; i < retVal.length(); ++i)
    {
        if(retVal[i] == '/')
        {
            retVal[i] = '\\';
        }
    }

    return retVal;
}

std::string FileUtility::getStringFromFile(const std::string& p_filename)
{
    std::string retVal;
    return retVal;
}

Data FileUtility::getDataFromFile(const std::string& p_filename)
{
    Data retVal;
    return retVal;
}

std::string FileUtility::getFullPathForFilename(const std::string& p_filename)
{
    std::string retVal(p_filename);
    return retVal;
}

long FileUtility::getFileSize(const std::string& p_filename)
{
    return 0;
}

bool FileUtility::isFileExist(const std::string& p_filename)
{
    return false;
}

std::vector<std::string> FileUtility::getSearchPaths() const
{
    return m_searchPaths;
}

void FileUtility::setSearchPaths(std::vector<std::string> p_searchPaths)
{
    m_searchPaths = p_searchPaths;
}

std::string FileUtility::getProjectPath() const
{
    return m_projectPath;
}

std::string FileUtility::getAssetPath() const
{
    return m_assetPath;
}

IRIS_END
