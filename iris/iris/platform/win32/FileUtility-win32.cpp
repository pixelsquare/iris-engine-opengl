#include "platform\win32\FileUtility-win32.h"
#include "platform\Logger.h"
#include "base\Data.h"

#if TARGET_PLATFORM == PLATFORM_WIN32

IRIS_BEGIN

FileUtilityWin32::FileUtilityWin32()
{
    if(m_projectPath.empty())
    {
        char projectPath[512];
        GetModuleFileName(NULL, projectPath, 512);

        std::string path(projectPath);
        std::vector<std::string> splitPath;

        size_t pos = 0;
        std::string token;
        std::string delimiter("\\");

        // Store delimited path
        while((pos = path.find(delimiter)) != std::string::npos)
        {
            token = path.substr(0, pos);
            splitPath.push_back(token);
            path.erase(0, pos + delimiter.length());
        }

        token.clear();
        path.clear();
        delimiter.clear();

        // Remove the last 2 directories from the project path
        for(unsigned int i = 0; i < splitPath.size() - 2; i++)
        {
            m_projectPath += splitPath[i];
            m_projectPath += "\\";
        }

        if(m_assetPath.empty())
        {
            m_assetPath = m_projectPath + "assets\\";
        }

        m_projectPath = convertPathToUnixFormat(m_projectPath);
        m_assetPath = convertPathToUnixFormat(m_assetPath);

        if(!isFileExist(m_assetPath))
        {
            m_assetPath = "assets\\";
            m_assetPath = convertPathToUnixFormat(m_assetPath);
        }

        //if(isFileExist(m_projectPath))
        //{
        //    Logger::error("Project Path not found!");
        //}

        //if(isFileExist(m_assetPath))
        //{
        //    Logger::error("Assets Path not found!");
        //}
    }
}

FileUtilityWin32::~FileUtilityWin32()
{
}

FileUtility& FileUtility::getInstance()
{
    if(s_sharedInstance == nullptr)
    {
        s_sharedInstance = new (std::nothrow) FileUtilityWin32();

        if(!s_sharedInstance)
        {
            SAFE_DELETE(s_sharedInstance);
        }
    }

    return *s_sharedInstance;
}

std::string FileUtilityWin32::getStringFromFile(const std::string& p_filename)
{
    std::string retVal;
    return retVal;
}

Data FileUtilityWin32::getDataFromFile(const std::string& p_filename)
{
    Data retVal;

    std::string fullFilename = getFullPathForFilename(p_filename);

    if(!isFileExist(fullFilename) || fullFilename.empty())
    {
        return retVal;
    }

    long fileSize = getFileSize(fullFilename) + 1;
    unsigned char *data = new unsigned char[fileSize];
    memset(data, 0, fileSize);

#if TARGET_PLATFORM == PLATFORM_WIN32
    FILE *file = fopen(fullFilename.c_str(), "rb");

    if(NULL == file)
    {
        return retVal;
    }

    fread(data, 1, fileSize, file);
    fclose(file);
#endif // TARGET_PLATFORM == PLATFORM_WIN32

    retVal.copy(data, fileSize);

    delete data;
    data = nullptr;

    return retVal;
}

std::string FileUtilityWin32::getFullPathForFilename(const std::string& p_filename)
{
    std::string retVal;

    if(isFileExist(m_assetPath + p_filename))
    {
        retVal = m_assetPath + p_filename;
        //m_fullPathCache.insert(std::pair<std::string, std::string>(p_filename, retVal));
    }

    return retVal;
}

long FileUtilityWin32::getFileSize(const std::string& p_filename)
{
    WIN32_FILE_ATTRIBUTE_DATA fad;
    if(!GetFileAttributesEx(p_filename.c_str(), GetFileExInfoStandard, &fad))
    {
        return 0;
    }

    LARGE_INTEGER size;
    size.HighPart = fad.nFileSizeHigh;
    size.LowPart = fad.nFileSizeLow;
    return (long)size.QuadPart;
}

std::wstring FileUtilityWin32::stringUtf8ToWideChar(const std::string& p_strUtf8)
{
    std::wstring ret;
    if(!p_strUtf8.empty())
    {
        int nNum = MultiByteToWideChar(CP_UTF8, 0, p_strUtf8.c_str(), -1, nullptr, 0);
        if(nNum)
        {
            WCHAR* wideCharString = new WCHAR[nNum + 1];
            wideCharString[0] = 0;

            nNum = MultiByteToWideChar(CP_UTF8, 0, p_strUtf8.c_str(), -1, wideCharString, nNum + 1);

            ret = wideCharString;
            delete[] wideCharString;
        }
        else
        {
            //LOG("Wrong convert to WideChar code:0x%x", GetLastError());
        }
    }
    return ret;
}

std::string FileUtilityWin32::stringWideCharToUtf8(const std::wstring& p_strWideChar)
{
    std::string ret;
    if(!p_strWideChar.empty())
    {
        int nNum = WideCharToMultiByte(CP_UTF8, 0, p_strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
        if(nNum)
        {
            char* utf8String = new char[nNum + 1];
            utf8String[0] = 0;

            nNum = WideCharToMultiByte(CP_UTF8, 0, p_strWideChar.c_str(), -1, utf8String, nNum + 1, nullptr, FALSE);

            ret = utf8String;
            delete[] utf8String;
        }
        else
        {
            //LOG("Wrong convert to Utf8 code:0x%x", GetLastError());
        }
    }

    return ret;
}

std::string FileUtilityWin32::UTF8StringToMultiByte(const std::string& p_strUtf8)
{
    std::string ret;
    if(!p_strUtf8.empty())
    {
        std::wstring strWideChar = stringUtf8ToWideChar(p_strUtf8);
        int nNum = WideCharToMultiByte(CP_ACP, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
        if(nNum)
        {
            char* ansiString = new char[nNum + 1];
            ansiString[0] = 0;

            nNum = WideCharToMultiByte(CP_ACP, 0, strWideChar.c_str(), -1, ansiString, nNum + 1, nullptr, FALSE);

            ret = ansiString;
            delete[] ansiString;
        }
        else
        {
            //LOG("Wrong convert to Ansi code:0x%x", GetLastError());
        }
    }

    return ret;
}

bool FileUtilityWin32::isFileExist(const std::string& p_filename)
{
    if(INVALID_FILE_ATTRIBUTES == GetFileAttributes(p_filename.c_str())
       && GetLastError() == ERROR_FILE_NOT_FOUND)
    {
        return false;
    }

    return true;
}

IRIS_END

#endif // TARGET_PLATFORM == PLATFORM_WIN32
