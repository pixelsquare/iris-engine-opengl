#include "Main.h"
#include "IrisWorldDemo.h"
#include "ShaderDemo.h"

#include "iris/Iris.h"
#include "iris/IrisApplication.h"

#include "assetdatabase\AssetDatabase.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32)
#include <conio.h>
#endif

using namespace IrisFramework;

void loadAssets()
{
	IRIS_ASSET_DATABASE.loadAsset("models", "cube3.obj");
	IRIS_ASSET_DATABASE.loadAsset("models", "monster.obj");
	IRIS_ASSET_DATABASE.loadAsset("models/vats", "vats01.obj");
	IRIS_ASSET_DATABASE.loadAsset("models/vats", "vats02.obj");

	//IRIS_ASSET_DATABASE.loadAsset("backgrounds", "bg1.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("backgrounds", "bg2.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("backgrounds", "bg3.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("backgrounds", "bg4.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("backgrounds", "bg5.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("backgrounds", "bg6.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("backgrounds", "bg7.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("backgrounds", "bg8.bmp");

	IRIS_ASSET_DATABASE.loadAsset("bootstrap", "box.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap", "mario.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap", "sample_16.bmp");
	IRIS_ASSET_DATABASE.loadAsset("bootstrap", "sample_24.bmp");
	IRIS_ASSET_DATABASE.loadAsset("bootstrap", "monster_1024.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap", "vintage.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap", "metallic.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap", "bush.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap", "checkered.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap", "sphere_normal_1024.bmp");	
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap", "gray.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap", "shinymetal.bmp");
	IRIS_ASSET_DATABASE.loadAsset("bootstrap", "brickwall.bmp");
	IRIS_ASSET_DATABASE.loadAsset("bootstrap", "brickwall_normal.bmp");
	IRIS_ASSET_DATABASE.loadAsset("bootstrap", "skybox.bmp");
	IRIS_ASSET_DATABASE.loadAsset("bootstrap", "ripple_normal.bmp");

	IRIS_ASSET_DATABASE.loadAsset("bootstrap", "test_texture.bmp");
	IRIS_ASSET_DATABASE.loadAsset("bootstrap", "test_normal.bmp");

	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\barrels", "barrel01_uv_ver01.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\barrels", "barrel01_uv_ver02.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\barrels", "barrel01_uv_ver03.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\barrels", "barrel02_uv_ver01.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\barrels", "barrel02_uv_ver02.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\barrels", "barrel02_uv_ver03.bmp");

	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\clocks", "clock01_uv.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\clocks", "clock02_uv.bmp");

	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\crates", "crate01_uv.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\crates", "crate02_uv.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\crates", "crate03_uv.bmp");

	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\vats", "vats01_uv.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\vats", "vats02_uv01.bmp");
	//IRIS_ASSET_DATABASE.loadAsset("bootstrap\\vats", "vats02_uv02.bmp");

	IRIS_ASSET_DATABASE.loadAsset("bootstrap/vats", "vats01_uv.bmp");
	IRIS_ASSET_DATABASE.loadAsset("bootstrap/vats", "vats02_uv02.bmp");
}

void onApplicationStart()
{
	loadAssets();

#if defined(_WIN32)
	IRIS_APPLICATION.setScreenSize(800, 480);
#elif defined(_ANDROID)
	IRIS_APPLICATION.setScreenSize(1080, 1920);
#endif
	IRIS_APPLICATION.setPlatform(IRIS_ANDROID);
	IRIS_APPLICATION.setTargetFrameRate(25);

	//IrisWorldDemo *irisWorldDemo = new IrisWorldDemo();
	//IRIS_ENGINE.setScene(irisWorldDemo);

	ShaderDemo *shaderDemo = new ShaderDemo();
	IRIS_ENGINE.setScene(shaderDemo);

	IRIS_ENGINE.initialize();
}

void onApplicationQuit()
{
	IRIS_ENGINE.shutdown();
}

int main(int* argc, char** argv)
{
	srand((unsigned int)time(NULL));

	onApplicationStart();
	onApplicationQuit();

#if defined(_WIN32)
	_getch();
#endif

	return 0;
}
