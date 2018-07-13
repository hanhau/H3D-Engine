#pragma once

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define EXTERNAL_PATH ../../../dep_libs
#ifdef _WIN32 || _WIN64

#elif defined _linux_

#endif

#define LUA_PATH       EXTERNAL_PATH/lua
#define SOL2_PATH      EXTERNAL_PATH/sol2
#define OPENAL_PATH	   EXTERNAL_PATH/openal
#define OGG_PATH       EXTERNAL_PATH/libogg
#define LIBVORBIS_PATH EXTERNAL_PATH/libvorbis
#define GLEW_PATH      EXTERNAL_PATH/glew
#define FREETYPE_PATH  EXTERNAL_PATH/freetype

#define LUA_INCLUDE       LUA_PATH/include
#define SOL2_INCLUDE      SOL2_PATH/single
#define OPENAL_INCLUDE	  OPENAL_PATH/include
#define GLEW_INCLUDE      GLEW_PATH/include
#define FREETYPE_INCLUDE  FREETYPE_PATH/include
#define LIBVORBIS_INCLUDE LIBVORBIS_PATH/include