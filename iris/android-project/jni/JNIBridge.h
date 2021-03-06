/*
 * JNIBridge.h
 *
 *  Created on: Jan 23, 2017
 *      Author: Anthony.Ganzon
 */

#ifndef JNIBRIDGE_H_
#define JNIBRIDGE_H_

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_iris_irisapp_JNIBridge */

#ifndef _Included_com_iris_irisapp_JNIBridge
#define _Included_com_iris_irisapp_JNIBridge
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    InitializeGL
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_InitializeGL
  (JNIEnv *, jclass);

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    OnWindowChanged
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_OnWindowChanged
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    Awake
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_Awake
  (JNIEnv *, jclass);

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    Start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_Start
  (JNIEnv *, jclass);

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    FixedUpdate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_FixedUpdate
  (JNIEnv *, jclass);

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    Update
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_Update
  (JNIEnv *, jclass);

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    LateUpdate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_LateUpdate
  (JNIEnv *, jclass);

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    OnPreRender
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_OnPreRender
  (JNIEnv *, jclass);

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    OnRender
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_OnRender
  (JNIEnv *, jclass);

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    OnPostRender
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_OnPostRender
  (JNIEnv *, jclass);

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    Shutdown
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_Shutdown
  (JNIEnv *, jclass);

/*
 * Class:     com_iris_irisapp_JNIBridge
 * Method:    LoadAssets
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_iris_irisapp_JNIBridge_SetAssetManager
  (JNIEnv *, jclass, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif

#endif /* JNIBRIDGE_H_ */
