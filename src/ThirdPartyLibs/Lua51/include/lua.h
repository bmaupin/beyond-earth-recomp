/* Preserve the SDK include path, but use Beyond Earth's Havok Script API. */
#ifndef lua_h
#define lua_h

// CvLuaSupport retains the Civ 5 extern "C" include block. Havok's API and
// runtime entry points have C++ linkage in the Linux Beyond Earth game core.
extern "C++" {
#include <ThirdPartyLibs/HavokScript/include/hksApi.h>
}
#endif