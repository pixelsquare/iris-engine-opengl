#ifndef _IRIS_FILE_UTILITY_WIN32_H_
#define _IRIS_FILE_UTILITY_WIN32_H_

#include "platform\PlatformMacros.h"
#include "platform\FileUtility.h"

#if TARGET_PLATFORM == PLATFORM_WIN32

IRIS_BEGIN

class IRIS_DLL FileUtilityWin32 : public FileUtility
{
public:
    FileUtilityWin32();
    virtual ~FileUtilityWin32();

    std::string getStringFromFile(const std::string& p_filename) override;

    Data getDataFromFile(const std::string& p_filename) override;

    std::string getFullPathForFilename(const std::string& p_filename) override;

    long getFileSize(const std::string& p_filename);

    bool isFileExist(const std::string& p_filename);

private:
    std::wstring stringUtf8ToWideChar(const std::string& p_strUtf8);
    std::string stringWideCharToUtf8(const std::wstring& p_strWideChar);
    std::string UTF8StringToMultiByte(const std::string& p_strUtf8);

protected:
};

IRIS_END

#endif // TARGET_PLATFORM == PLATFORM_WIN32

#endif // _IRIS_FILE_UTILITY_WIN32_H_