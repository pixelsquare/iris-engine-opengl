@echo off
setlocal

SET ASSETDATABASE="%~dp0\assetdatabase"
SET ASSETS="%~dp0\assets"
SET CAMERA="%~dp0\camera"
SET COLOR="%~dp0\color"
SET COMPONENT="%~dp0\component"
SET DEBUGGABLE="%~dp0\debuggable"
SET DISPOSABLE="%~dp0\disposable"
SET GAME="%~dp0\game"
SET GAMEOBJECT="%~dp0\gameobject"
SET GL="%~dp0\gl"
SET INPUT="%~dp0\input"
SET IRIS="%~dp0\iris"
SET LIGHT="%~dp0\light"
SET MATERIAL="%~dp0\material"
SET MATHF="%~dp0\mathf"
SET MATRIX4X4="%~dp0\matrix4x4"
SET MESH="%~dp0\mesh"
SET OBJECT="%~dp0\object"
SET RECT="%~dp0\rect"
SET RENDERER="%~dp0\renderer"
SET SHADER="%~dp0\shader"
SET TEXTURE2D="%~dp0\texture2d"
SET TRANSFORM="%~dp0\transform"
SET VECTOR3F="%~dp0\vector3f"

mklink /j "%~dp0android-project\assets" 	%ASSETS%
mklink /j "%~dp0android-project\jni\assetdatabase" 	%ASSETDATABASE%
mklink /j "%~dp0android-project\jni\camera" %CAMERA%
mklink /j "%~dp0android-project\jni\color" %COLOR%
mklink /j "%~dp0android-project\jni\component" %COMPONENT%
mklink /j "%~dp0android-project\jni\debuggable" %DEBUGGABLE%
mklink /j "%~dp0android-project\jni\disposable" %DISPOSABLE%
mklink /j "%~dp0android-project\jni\game" %GAME%
mklink /j "%~dp0android-project\jni\gameobject" %GAMEOBJECT%
mklink /j "%~dp0android-project\jni\gl" %GL%
mklink /j "%~dp0android-project\jni\input" %INPUT%
mklink /j "%~dp0android-project\jni\iris" %IRIS%
mklink /j "%~dp0android-project\jni\light" %LIGHT%
mklink /j "%~dp0android-project\jni\material" %MATERIAL%
mklink /j "%~dp0android-project\jni\mathf" %MATHF%
mklink /j "%~dp0android-project\jni\matrix4x4" %MATRIX4X4%
mklink /j "%~dp0android-project\jni\mesh" %MESH%
mklink /j "%~dp0android-project\jni\object" %OBJECT%
mklink /j "%~dp0android-project\jni\rect" %RECT%
mklink /j "%~dp0android-project\jni\renderer" %RENDERER%
mklink /j "%~dp0android-project\jni\shader" %SHADER%
mklink /j "%~dp0android-project\jni\texture2d" %TEXTURE2D%
mklink /j "%~dp0android-project\jni\transform" %TRANSFORM%
mklink /j "%~dp0android-project\jni\vector3f" %VECTOR3F%

pause