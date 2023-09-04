#ifndef _IRIS_PLATFORM_MACROS_H_
#define _IRIS_PLATFORM_MACROS_H_

#include "AppConfig.h"

#include "platform\PlatformConfig.h"
#include "platform\PlatformDefine.h"

//#include <stdio.h>
#include <string>

///	@name namespace macros
///	@{
#ifdef __cplusplus
	#define IRIS_BEGIN		namespace iris {
	#define IRIS_END		}
#define USING_IRIS		    using namespace iris;
	#define NS_IRIS			::iris
#else
	#define IRIS_BEGIN	
	#define IRIS_END	
	#define USING_IRIS	
	#define NS_IRIS		
#endif
///	End of namespace macros
///	@}

///	@name helper definitions
///	@{
#define SAFE_DELETE(p)				do { delete (p); (p) = nullptr; } while (0)
#define SAFE_DELETE_ARRAY(p)		do { if(p) { delete[] (p); (p) = nullptr; } } while (0)
#define SAFE_FREE(p)                do { if(p) { free(p); (p) = nullptr; } } while(0)
#define SAFE_RELEASE(p)             do { if(p) { (p)->release(); } } while(0)
#define SAFE_RELEASE_NULL(p)        do { if(p) { (p)->release(); (p) = nullptr; } } while(0)
#define SAFE_RETAIN(p)              do { if(p) { (p)->retain(); } } while(0)
#define BREAK_IF(cond)				if(cond) break
///	End of helper definitions
///	@}

///	@name iris debug definitions
/// @{
#if !defined(IRIS_DEBUG) || IRIS_DEBUG == 0
	#define IRISLOG(...)			do {} while (0)
	#define IRISLOGINFO(...)		do {} while (0)
	#define IRISLOGWARN(...)		do {} while (0)
	#define IRISLOGERROR(...)		do {} while (0)
#elif defined (IRIS_DEBUG) && IRIS_DEBUG == 1
	#define IRISLOG(...)			do {} while (0)
	#define IRISLOGINFO(...)		do {} while (0)
	#define IRISLOGWARN(...)		do {} while (0)
	#define IRISLOGERROR(...)		do {} while (0)
#elif defined (IRIS_DEBUG) && IRIS_DEBUG > 1
	#define IRISLOG(...)			do {} while (0)
	#define IRISLOGINFO(...)		do {} while (0)
	#define IRISLOGWARN(...)		do {} while (0)
	#define IRISLOGERROR(...)		do {} while (0)
#endif
///	End of iris debug definitions
/// @}

/**
 *	@def DISALLOW_COPY_AND_ASSIGN
 *	A macro to disallow the copy constructor and operator= functions.
 *	This should be used in the private: declarations for a class
 */

#if defined(__GNUC__) && ((__GNUC__ >= 5) || ((__GNUG__ == 4) && (__GNUC_MINOR__ >= 4))) \
    || (defined(__clang__) && (__clang_major__ >= 3)) || (_MSC_VER >= 1800)
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName &) = delete; \
    TypeName &operator =(const TypeName &) = delete;
#else
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName &); \
    TypeName &operator =(const TypeName &);
#endif

#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName)    \
    TypeName();                                     \
    DISALLOW_COPY_AND_ASSIGN(TypeName)

/**
 *	@def PROPERTY_READONLY
 *	It is used to declare a protected variable.
 *	We can use the getter to read the variable.
 */

#define PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const;

#define PROPERTY_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const;

/**
 *	@def PROPERTY
 *	It is used to declare a protected variable.
 *	We can use the getter to read the variable.
 *	we can use the setter to change the variable.
 */

#define PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const;\
public: virtual void set##funName(varType var);

#define PROPERTY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const;\
public: virtual void set##funName(const varType& var);

 /**
 *	@def PROPERTY_INLINE_READONLY
 *	It is used to declare a protected variable.
 *	We can use the inline getter to read the variable.
 */

#define PROPERTY_INLINE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }

#define PROPERTY_INLINE_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }

 /**
 *	@def PROPERTY
 *	It is used to declare a protected variable.
 *	We can use the inline getter to read the variable.
 *	we can use the inline setter to change the variable.
 */

#define PROPERTY_INLINE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

#define PROPERTY_INLINE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }\
public: virtual void set##funName(const varType& var){ varName = var; }

/**
 *	@def DEPRECATED_ATTRIBUTE
 *	Mark methods, functions, etc. as depreciated
 */

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
	#define DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
	#define DEPRECATED_ATTRIBUTE __declspec(deprecated) 
#else
	#define DEPRECATED_ATTRIBUTE
#endif 

/**
 *  @def PROFILING
 */

#if !IRIS_ENABLE_PROFILER

#define IRIS_PROFILER_DISPLAY_TIMERS() NS_IRIS::Profiler::getInstance().displayTimers()
#define IRIS_PROFILER_RELEASE_ALL_TIMERS() NS_IRIS::Profiler::getInstance().releaseTimers()

#define IRIS_PROFILER_START(__name__) NS_IRIS::Profiler::getInstance().beginProfiling(__name__)
#define IRIS_PROFILER_STOP(__name__) NS_IRIS::Profiler::getInstance().endProfiling(__name__)
#define IRIS_PROFILER_REST(__name__) NS_IRIS::Profiler::getInstance().resetProfiler(__name__)

#else

#define IRIS_PROFILER_DISPLAY_TIMERS() do {} while (0)
#define IRIS_PROFILER_RELEASE_ALL_TIMERS() do {} while (0)

#define IRIS_PROFILER_START(__name__) do {} while (0)
#define IRIS_PROFILER_STOP(__name__) do {} while (0)
#define IRIS_PROFILER_REST(__name__) do {} while (0)

#endif

#if defined(IRIS_DEBUG) && IRIS_DEBUG > 0

#define IRIS_ASSERT_LOG(cond, msg) do { \
    if(!(cond)) { \
        if(std::strlen(msg)) { \
            std::printf("Assertion Failed: %s\n", msg); \
        } \
        IRIS_ASSERT(cond); \
    } \
} while(0) \

#endif

#endif // _IRIS_PLATFORM_MACROS_H_