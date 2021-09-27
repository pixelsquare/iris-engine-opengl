#ifndef __IRIS_ASSET_DATABASE_H__
#define __IRIS_ASSET_DATABASE_H__
#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>

#if defined(_ANDROID)
#include <jni.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#endif

namespace IrisFramework
{
	#define IRIS_ASSET_DATABASE AssetDatabase::Instance()

	class Texture2D;
	class Shader;

	typedef std::pair<const char*, Shader*> shaderListPair_t;
	typedef std::map<const char*, Shader*> shaderListMap_t;

	typedef std::pair<const char*, unsigned char*> assetListPair_t;
	typedef std::map<const char*, unsigned char*> assetListMap_t;

	class AssetDatabase
	{
	public:
		static AssetDatabase &Instance();

#if defined(_ANDROID)
		void initAndroidAssetManager(JNIEnv * p_env, jobject p_assetManager);
#endif

		void loadAsset(const char* p_directory, const char* p_filename);
		void loadAllShaders();

		void unloadAsset(const char* p_fileName);

		unsigned char* getAsset(const char* p_assetName) const;
		Shader getShaderAsset(const char* p_assetName) const;

		unsigned int getAssetCount() const;
		unsigned int getShaderAssetCount() const;

		const char* getProjectPath() const;
		const char* getAssetPath() const;

		const char* getAssetPath(const char* p_directory, const char* p_filename) const;

	private:
		AssetDatabase();
		~AssetDatabase();

		assetListPair_t appendAsset(const char* p_assetName, unsigned char* p_assetContent);
		shaderListPair_t appendShader(const char* p_assetName, Shader* p_shader);

		long getFileSize(const char* p_assetPath);
		const char* getFileName(const char* p_assetPath);

		void loadAssetAtPath(const char* p_assetName, const char* p_assetPath);

		char* m_projectPath;
		char* m_assetPath;

#if defined(_ANDROID)
		AAssetManager *m_assetManager;
#endif

		std::map<const char*, Shader*> m_shaderList;
		std::map<const char*, unsigned char*> m_assetList;

	protected:			
	};
}

#endif
