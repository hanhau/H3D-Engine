objects = dllmain.o

H3D.so : $(objects)
	g++ -o H3D.so $(objects)

.PHONY : clean
clean :
	rm demo $(objects)
