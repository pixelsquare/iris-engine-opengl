/*
 * JNIBridge.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: Anthony.Ganzon
 */

#include "JNIBridge.h"
#include "iris/Iris.h"
#include "iris/IrisGL.h"
#include "assetdatabase/AssetDatabase.h"
#include "game/Main.h"

#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

using namespace IrisFramework;

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_InitializeGL
  (JNIEnv * env, jclass cls)
{
	IRIS_GL.initialize();
}

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_OnWindowChanged
  (JNIEnv * env, jclass cls, jint width, jint height)
{
	IRIS_GL.resizeWindow(width, height);
}

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_Awake
  (JNIEnv * env, jclass cls)
{
	onApplicationStart();
	IRIS_ENGINE.awake();
}

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_Start
  (JNIEnv * env, jclass cls)
{
	IRIS_ENGINE.start();
}

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_FixedUpdate
  (JNIEnv * env, jclass cls)
{
	IRIS_ENGINE.fixedUpdate();
}

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_Update
  (JNIEnv * env, jclass cls)
{
	IRIS_ENGINE.update();
}

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_LateUpdate
  (JNIEnv * env, jclass cls)
{
	IRIS_ENGINE.lateUpdate();
}

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_OnPreRender
  (JNIEnv * env, jclass cls)
{
	IRIS_ENGINE.onPreRender();
}

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_OnRender
  (JNIEnv * env, jclass cls)
{
	IRIS_ENGINE.onRender();
}

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_OnPostRender
  (JNIEnv * env, jclass cls)
{
	IRIS_ENGINE.onPostRender();
}

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_Shutdown
  (JNIEnv * env, jclass cls)
{
	IRIS_ENGINE.shutdown();
}

JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_SetAssetManager
  (JNIEnv * env, jclass cls, jobject assetManager, jstring internalDir)
{
	IRIS_ASSET_DATABASE.initAndroidAssetManager(env, assetManager);
}
