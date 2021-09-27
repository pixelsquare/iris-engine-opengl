LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ENGINE_PATH := ../
ASSETDATABASE_PATH := ../assetdatabase
CAMERA_PATH := ../camera
COLOR_PATH := ../color
COMPONENT_PATH := ../component
DEBUGGABLE_PATH := ../debuggable
DISPOSABLE_PATH := ../disposable
GAMEOBJECT_PATH := ../gameobject
INPUT_PATH := ../input
IRIS_PATH := ../iris
LIGHT_PATH := ../light
MATERIAL_PATH := ../material
MATHF_PATH := ../mathf
MATRIX4X4_PATH := ../matrix4x4
MESH_PATH := ../mesh
OBJECT_PATH := ../object
RECT_PATH := ../rect
RENDERER_PATH := ../renderer
SHADER_PATH := ../shader
TEXTURE2D_PATH := ../texture2d
TRANSFORM_PATH := ../transform
VECTOR3F_PATH := ../vector3f

LOCAL_MODULE := Iris
LOCAL_MODULE_FILENAME := libIris

LOCAL_ARM_MODE	:= arm

LOCAL_CPPFLAGS += -fpermissive
LOCAL_CPPFLAGS += -fexceptions
LOCAL_CFLAGS += -w
LOCAL_CFLAGS += -O2
LOCAL_CFLAGS += -fPIC
LOCAL_CFLAGS += -frtti
LOCAL_CFLAGS += -DPIC
LOCAL_CFLAGS += -DDARWIN_NO_CARBON
LOCAL_CFLAGS += -DPOST_FROYO
LOCAL_CFLAGS += -DAL_ALEXT_PROTOTYPES
LOCAL_CFLAGS += -D_DEBUG
LOCAL_CFLAGS += -D_ANDROID
LOCAL_CFLAGS += -DTU_CONFIG_VERBOSE

LOCAL_C_INCLUDES += \
$(LOCAL_PATH)/$(ENGINE_PATH) \

LOCAL_SRC_FILES := \
$(DISPOSABLE_PATH)/IDisposable.cpp \
$(DEBUGGABLE_PATH)/IDebuggable.cpp \
\
$(CAMERA_PATH)/Camera.cpp \
\
$(COLOR_PATH)/Color.cpp \
\
$(COMPONENT_PATH)/Component.cpp \
\
$(GAMEOBJECT_PATH)/GameObject.cpp \
\
$(INPUT_PATH)/Input.cpp \
\
$(IRIS_PATH)/Iris.cpp \
$(IRIS_PATH)/IrisApplication.cpp \
$(IRIS_PATH)/IrisGL.cpp \
$(IRIS_PATH)/IrisLogger.cpp \
$(IRIS_PATH)/IrisScene.cpp \
$(IRIS_PATH)/IrisTime.cpp \
$(IRIS_PATH)/IrisWindow.cpp \
\
$(MATHF_PATH)/Mathf.cpp\
\
$(MATRIX4X4_PATH)/Matrix4x4.cpp \
\
$(MESH_PATH)/Mesh.cpp \
\
$(OBJECT_PATH)/Object.cpp \
\
$(RECT_PATH)/Rect.cpp \
\
$(RENDERER_PATH)/Renderer.cpp \
\
$(SHADER_PATH)/Shader.cpp \
\
$(TEXTURE2D_PATH)/Texture2D.cpp \
\
$(TRANSFORM_PATH)/Transform.cpp \
\
$(VECTOR3F_PATH)/Vector3f.cpp \
\
$(ASSETDATABASE_PATH)/AssetDatabase.cpp \
\
$(LIGHT_PATH)/Light.cpp \
\
$(MATERIAL_PATH)/Material.cpp \
\

LOCAL_LDLIBS := -llog -lGLESv2 -lEGL -landroid -lz

include $(BUILD_SHARED_LIBRARY)