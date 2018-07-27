#pragma once

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#ifdef _WIN32 || _WIN64

#elif defined _linux_

#endif

#define ASSIMP_INCLUDE    ../../dep_libs/assimp/include
#define LUA_INCLUDE       ../../dep_libs/lua/src 
#define SOL2_INCLUDE      ../../dep_libs/sol2/single 
#define OPENAL_INCLUDE	  ../../dep_libs/openal/include 
#define GLEW_INCLUDE      ../../dep_libs/glew/include
#define FREETYPE_INCLUDE  ../../dep_libs/freetype/windows/freetype
#define LIBVORBIS_INCLUDE ../../dep_libs/libvorbis/include