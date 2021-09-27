#include "AssetDatabase.h"
#include "iris\IrisLogger.h"
#include "texture2d\Texture2D.h"
#include "shader\Shader.h"
#include "iris\IrisGL.h"

#if defined(_WIN32)
#include <Windows.h>
#endif

#include <vector>

namespace IrisFramework
{
	AssetDatabase::AssetDatabase()
	: m_projectPath(0)
	{
#if defined(_WIN32)
		std::string projectPath;
		char absolutePath[MAX_PATH];
		std::string filepath(absolutePath, GetModuleFileName(NULL, absolutePath, MAX_PATH));

		char *path = (char*)filepath.c_str();
		char *token = strtok(path, "\\");

		projectPath.append(token);
		projectPath.append("\\");

		while(token != NULL)
		{
			token = strtok(NULL, "\\");

            if(strcmp(token, "game.exe") == 0)
            {
                break;
            }

			projectPath.append(token);
			projectPath.append("\\");

			if(strstr(token, "src"))
			{
				break;
			}
		}

		m_projectPath = new char[projectPath.length()];
		strcpy(m_projectPath, projectPath.c_str());

		std::string assetPath(projectPath);
		assetPath.append("assets\\");

		m_assetPath = new char[assetPath.length()];
		strcpy(m_assetPath, assetPath.c_str());

		path = 0;
		delete[] path;

		token = 0;
		delete[] token;
#endif
	}

	AssetDatabase::~AssetDatabase() {}

	AssetDatabase &AssetDatabase::Instance()
	{
		static AssetDatabase instance;
		return instance;
	}

#if defined(_ANDROID)
	void AssetDatabase::initAndroidAssetManager(JNIEnv * p_env, jobject p_assetManager)
	{
		m_assetManager = AAssetManager_fromJava(p_env, p_assetManager);
	}
#endif

	void AssetDatabase::loadAsset(const char* p_directory, const char* p_filename)
	{
		int pathBuffer = 0;
		char *assetPath = NULL;

#if defined(_WIN32)
		pathBuffer= strlen(m_assetPath) + strlen(p_directory) + strlen(p_filename) + 2;
		assetPath = new char[pathBuffer];
		strcpy(assetPath, m_assetPath);
		strcat(assetPath, p_directory);
		strcat(assetPath, "\\");
		strcat(assetPath, p_filename);
#elif defined(_ANDROID)
		pathBuffer = strlen(p_directory) + strlen(p_filename) + 2;
		assetPath = new char[pathBuffer];
		strcpy(assetPath, p_directory);
		strcat(assetPath, "/");
		strcat(assetPath, p_filename);
#endif

#if defined(_WIN32)
		loadAssetAtPath(p_filename, assetPath);
#else defined(__ANDRIOD__)
		if(NULL != m_assetManager)
		{
			char *filename = (const char*) NULL;
			AAssetDir *assetDirectory = AAssetManager_openDir(m_assetManager, p_directory);

			while((filename = AAssetDir_getNextFileName(assetDirectory)) != NULL)
			{
				if(strcmp(filename, p_filename) == 0)
				{
					IRIS_LOG.log("Asset Successfully Found: %s", filename);
					AAsset *asset = AAssetManager_open(m_assetManager, assetPath, AASSET_MODE_STREAMING);
					long bufferSize = AAsset_getLength(asset);

					const unsigned char *buffer = (const unsigned char*)NULL;
					buffer = (const unsigned char*)AAsset_getBuffer(asset);

					unsigned char *tmpBuffer = new unsigned char[bufferSize+1];
					memset(tmpBuffer, 0, bufferSize+1);
					memcpy(tmpBuffer, buffer, bufferSize);

					int filenameSize = strlen(filename)+1;
					char *tmpFilename = new char[filenameSize];
					memset(tmpFilename, 0, filenameSize);
					memcpy(tmpFilename, filename, filenameSize);

					appendAsset(tmpFilename, tmpBuffer);

					AAsset_close(asset);
					break;
				}
			}
		}
#endif
		IRIS_LOG.internalLog("Asset Loaded ... [%s]", assetPath);

		assetPath = 0;
		delete[] assetPath;
	}

	void AssetDatabase::loadAllShaders()
	{
		//loadAsset("shaders", "sample.vrt");
		//loadAsset("shaders", "sample.frg");

		//Shader *sampleShader = new Shader("sample");
		//sampleShader->loadShaderData(getAsset("sample.vrt"), getAsset("sample.frg"));
		//appendShader("sample", sampleShader);

		//loadAsset("shaders", "skybox.vrt");
		//loadAsset("shaders", "skybox.frg");

		//Shader *skyboxShader = new Shader("skybox");
		//skyboxShader->loadShaderData(getAsset("skybox.vrt"), getAsset("skybox.frg"));
		//appendShader("skybox", skyboxShader);

		loadAsset("shaders", "noshader.vrt");
		loadAsset("shaders", "noshader.frg");

		Shader *plainColorShader = new Shader("noshader");
		plainColorShader->loadShaderData(getAsset("noshader.vrt"), getAsset("noshader.frg"));
		appendShader("noshader", plainColorShader);

		//loadAsset("shaders", "default.vrt");
		//loadAsset("shaders", "default.frg");

		//Shader *defaultShader = new Shader("default");
		//defaultShader->loadShaderData(getAsset("default.vrt"), getAsset("default.frg"));
		//appendShader("default", defaultShader);

		loadAsset("shaders", "diffuse.vrt");
		loadAsset("shaders", "diffuse.frg");

		Shader *diffuseShader = new Shader("diffuse");
		diffuseShader->loadShaderData(getAsset("diffuse.vrt"), getAsset("diffuse.frg"));
		appendShader("diffuse", diffuseShader);

		loadAsset("shaders", "specular.vrt");
		loadAsset("shaders", "specular.frg");

		Shader *specularShader = new Shader("specular");
		specularShader->loadShaderData(getAsset("specular.vrt"), getAsset("specular.frg"));
		appendShader("specular", specularShader);

		loadAsset("shaders", "normalmap.vrt");
		loadAsset("shaders", "normalmap.frg");

		Shader *normalMapShader = new Shader("normalmap");
		normalMapShader->loadShaderData(getAsset("normalmap.vrt"), getAsset("normalmap.frg"));
		appendShader("normalmap", normalMapShader);
	}

	void AssetDatabase::unloadAsset(const char* p_filename)
	{
		unsigned int assetCount = m_assetList.size();
		typedef assetListMap_t::iterator iterator_t;
		for(iterator_t iterator = m_assetList.begin(); iterator != m_assetList.end();)
		{
			if(strcmp((*iterator).first, p_filename) == 0)
			{
				delete[](*iterator).second;
				m_assetList.erase(iterator);
			}
			else
			{
				++iterator;
			}
		}

		IRIS_LOG.internalLog("Unloading Asset ... [%s] [%i -> %i]", p_filename, assetCount, m_assetList.size());
	}

	unsigned char *AssetDatabase::getAsset(const char* p_assetName) const
	{
		typedef assetListMap_t::const_iterator iterator_t;
		for (iterator_t iterator = m_assetList.begin(); iterator != m_assetList.end(); ++iterator)
		{
			if (strcmp((*iterator).first, p_assetName) == 0)
			{
				return (*iterator).second;
			}
		}

		return NULL;
	}

	Shader AssetDatabase::getShaderAsset(const char *p_assetName) const
	{
		Shader retVal;
		typedef shaderListMap_t::const_iterator iterator_t;
		for (iterator_t iterator = m_shaderList.begin(); iterator != m_shaderList.end(); ++iterator)
		{
			if (strcmp((*iterator).first, p_assetName) == 0)
			{
				retVal = *(*iterator).second;
			}
		}

		return retVal;
	}

	unsigned int AssetDatabase::getAssetCount() const
	{
		return m_assetList.size();
	}

	unsigned int AssetDatabase::getShaderAssetCount() const
	{
		return m_shaderList.size();
	}

	const char* AssetDatabase::getProjectPath() const
	{
		return m_projectPath;
	}

	const char* AssetDatabase::getAssetPath() const
	{
		return m_assetPath;
	}

	const char* AssetDatabase::getAssetPath(const char *p_directory, const char *p_filename) const
	{
		int pathBuffer = strlen(m_assetPath) + strlen(p_directory) + strlen(p_filename) + 2;
		char *assetPath = new char[pathBuffer];
		strcpy(assetPath, m_assetPath);
		strcat(assetPath, p_directory);
		strcat(assetPath, "\\");
		strcat(assetPath, p_filename);
		return assetPath;
	}

	shaderListPair_t AssetDatabase::appendShader(const char *p_assetName, Shader *p_shader)
	{
		shaderListPair_t retVal(p_assetName, p_shader);
		m_shaderList.insert(retVal);
		return retVal;
	}
	
	assetListPair_t AssetDatabase::appendAsset(const char* p_assetName, unsigned char* p_assetContent)
	{
		assetListPair_t retVal(p_assetName, p_assetContent);
		m_assetList.insert(retVal);
		return retVal;
	}

	long AssetDatabase::getFileSize(const char* p_assetPath)
	{
		long retVal = 0;

#if defined(_WIN32)
		FILE *file = NULL;
		file = fopen(p_assetPath, "rb");
		fseek(file, 0, SEEK_END);
		retVal = ftell(file);
		fclose(file);
#endif

		return retVal;
	}

	const char* AssetDatabase::getFileName(const char* p_assetPath)
	{
		// WIP
		const char* retVal = NULL;
		return retVal;
	}

	void AssetDatabase::loadAssetAtPath(const char* p_assetName, const char* p_assetPath)
	{
		long fileSize = getFileSize(p_assetPath)+1;
		unsigned char *data = new unsigned char[fileSize];
		memset(data, 0, fileSize);

#if defined(_WIN32)
		FILE *file = fopen(p_assetPath, "rb");

		if(NULL == file)
		{
			IRIS_LOG.internalLog("Unable to read asset file!");
			return;
		}

		fread(data, 1, fileSize, file);
		fclose(file);
#endif

		appendAsset(p_assetName, data);
	}
}
