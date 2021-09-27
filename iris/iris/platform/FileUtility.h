#ifndef _IRIS_FILE_UTILITY_H_
#define _IRIS_FILE_UTILITY_H_

#include "platform\PlatformMacros.h"
#include "platform\StdC.h"
#include <unordered_map>

IRIS_BEGIN

#define IRIS_FILEUTILS FileUtility::getInstance()

class Data;
class IRIS_DLL FileUtility
{
public:
    virtual ~FileUtility();

    static FileUtility &getInstance();

    static std::string convertPathToUnixFormat(const std::string p_path);

    static std::string convertPathToWinFormat(const std::string p_path);

    virtual std::string getStringFromFile(const std::string& p_filename);

    virtual Data getDataFromFile(const std::string& p_filename);

    virtual std::string getFullPathForFilename(const std::string& p_filename);

    virtual long getFileSize(const std::string& p_filename);

    virtual bool isFileExist(const std::string& p_filename);

    PROPERTY(std::vector<std::string>, m_searchPaths, SearchPaths);

    PROPERTY_READONLY(std::string, m_projectPath, ProjectPath);

    PROPERTY_READONLY(std::string, m_assetPath, AssetPath);

private:
    static FileUtility* s_sharedInstance;

protected:
    DISALLOW_IMPLICIT_CONSTRUCTORS(FileUtility);
    typedef std::unordered_map<std::string, std::string> FullPathCache;
    FullPathCache m_fullPathCache;
};

IRIS_END

#endif // _IRIS_FILE_UTILITY_H_