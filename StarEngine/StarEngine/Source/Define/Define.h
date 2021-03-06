#pragma once
//#include "Core/SObject/SObject.h"
#include <map>
#include <stdarg.h>
#include <windows.h>
#include <thread>
#include <chrono>
#include <list>
#include <iostream>
#include <algorithm>
#include <functional>

// Unsigned base types.
typedef unsigned char 		uint8;		// 8-bit  unsigned.
typedef unsigned short int	uint16;		// 16-bit unsigned.
typedef unsigned int		uint32;		// 32-bit unsigned.
typedef unsigned long long	uint64;		// 64-bit unsigned.

// Signed base types.
typedef	signed char			int8;		// 8-bit  signed.
typedef signed short int	int16;		// 16-bit signed.
typedef signed int	 		int32;		// 32-bit signed.
typedef signed long long	int64;		// 64-bit signed.

// Character types.
typedef char				ANSICHAR;	// An ANSI character       -                  8-bit fixed-width representation of 7-bit characters.
typedef wchar_t				WIDECHAR;	// A wide character        - In-memory only.  ?-bit fixed-width representation of the platform's natural wide character set.  Could be different sizes on different platforms.
typedef uint8				CHAR8;		// An 8-bit character type - In-memory only.  8-bit representation.  Should really be char8_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
typedef uint16				CHAR16;		// A 16-bit character type - In-memory only.  16-bit representation.  Should really be char16_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
typedef uint32				CHAR32;		// A 32-bit character type - In-memory only.  32-bit representation.  Should really be char32_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
typedef WIDECHAR			TCHAR;		// A switchable character  - In-memory only.  Either ANSICHAR or WIDECHAR, depending on a licensee's requirements.

#define BODY_MACRO_COMBINE_INNER(A,B) A##B
#define BODY_MACRO_COMBINE(A,B) BODY_MACRO_COMBINE_INNER(A,B)

#define STAR_DEFINE_CODE(...) BODY_MACRO_COMBINE(CURFILENAMEID,__LINE__)

#define SCLASS(...)

#define SPROPERTY(...)

#define SFUNCTION(...)

#define MAX_HORIZONTAL_LAYOUT_COUNT 20

#define MAX_VERTICAL_LAYOUT_COUNT 20

template <class T>
static inline T* NewSObject()
{
	T* obj = new T();
	SObject* sobj = dynamic_cast<SObject*>(obj);
	if (sobj == nullptr)
	{
		delete obj;
		return nullptr;
	}
	sobj->ConfigGCRef();
	SGarbageCollectionMgr* GarbageCollectionMgr = SGarbageCollectionMgr::GetInstance();
	GarbageCollectionMgr->AddGcObject(obj);
	return obj;
}
