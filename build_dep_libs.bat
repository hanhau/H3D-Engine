@echo on
cd ./dep_libs

:: assimp
cd ./assimp
cmake .
msbuild Assimp.sln
cd ../

:: freetype
cd /freetype 
cmake .

cd ../

:: glew 
cd /glew
./cmake-testbuild.sh
msbuild ./build/vc15/glew.sln
cd ../

:: libogg 
cd /libogg
cd ../

:: libvorbis
cd /livorbis
cd ../

:: lua
cd /lua
cd ../

:: openal
cd /openal
cd ../

@echo Finished  building !
pause