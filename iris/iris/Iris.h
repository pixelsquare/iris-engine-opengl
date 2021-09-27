#ifndef _IRIS_H_
#define _IRIS_H_

// base
#include "base\Bundle3D.h"
#include "base\Camera.h"
#include "base\Color.h"
#include "base\Component.h"
#include "base\Data.h"
#include "base\Director.h"
#include "base\GameObject.h"
#include "base\Input.h"
#include "base\IStringable.h"
#include "base\Light.h"
#include "base\Material.h"
#include "base\Mesh.h"
#include "base\MeshRenderer.h"
#include "base\Object.h"
#include "base\PooledObject.h"
#include "base\PoolManager.h"
#include "base\Primitives.h"
#include "base\Profiler.h"
#include "base\Rect.h"
#include "base\Renderer.h"
#include "base\RenderTexture.h"
#include "base\Scene.h"
#include "base\Shader.h"
#include "base\ShaderCache.h"
#include "base\Size.h"
#include "base\Texture2D.h"
#include "base\Time.h"
#include "base\Transform.h"

// math
#include "math\Mathf.h"
#include "math\Matrix4x4.h"
#include "math\Vector2f.h"
#include "math\Vector3f.h"
#include "math\Vector4f.h"
#include "math\Quaternion.h"

// platform
#include "platform\Application.h"
#include "platform\Logger.h"
#include "platform\PlatformGL.h"
#include "platform\PlatformMacros.h"
#include "platform\StdC.h"

#if TARGET_PLATFORM == PLATFORM_ANDROID
#elif TARGET_PLATFORM == PLATFORM_WIN32
#include "platform\win32\GLView-win32.h"
#include "platform\win32\FileUtility-win32.h"
#endif

#endif  // _IRIS_H_
