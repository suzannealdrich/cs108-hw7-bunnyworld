// ===========================================================================//	Complete_DebugHeaders.h			�1996-1998 Metrowerks Inc. All rights reserved.// ===========================================================================	// Use PowerPlant-specific Precompiled header	#if __POWERPC__	#include "Complete_DebugHeadersPPC++"	#else	#include "Complete_DebugHeaders68K++"#endif	// Headers not in Complete_DebugHeaders.cp won't force PCH to recompile