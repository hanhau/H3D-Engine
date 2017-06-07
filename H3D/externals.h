#pragma once

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define EXTERNAL_PATH C:/C++ Libraries

#define LUA_PATH       EXTERNAL_PATH/lua 5.3.4
#define SOL2_PATH      EXTERNAL_PATH/sol2
#define OPENAL_PATH	   EXTERNAL_PATH/OpenAL 1.1 SDK
#define OGG_PATH       EXTERNAL_PATH/libogg-1.3.2
#define LIBVORBIS_PATH EXTERNAL_PATH/libvorbis-1.3.5
#define GLEW_PATH      EXTERNAL_PATH/glew-2.0.0
#define FREETYPE_PATH  EXTERNAL_PATH/freetype-2.7

#define LUA_INCLUDE       LUA_PATH/include
#define SOL2_INCLUDE      SOL2_PATH/single
#define OPENAL_INCLUDE	  OPENAL_PATH/include
#define GLEW_INCLUDE      GLEW_PATH/include
#define FREETYPE_INCLUDE  FREETYPE_PATH/include
#define LIBVORBIS_INCLUDE LIBVORBIS_PATH/include