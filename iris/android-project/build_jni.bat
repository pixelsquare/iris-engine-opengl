@ECHO OFF
SETLOCAL

SET JAVA_CLASS=JNIBridge
SET CPLUSPLUS_CLASS=_JNIBridge.h
SET PACKAGE_NAME=com.iris.irisapp

CD bin\classes

javah -o ../../jni/%CPLUSPLUS_CLASS% %PACKAGE_NAME%.%JAVA_CLASS%

ECHO SUCCESS!
PAUSE

ENDLOCAL