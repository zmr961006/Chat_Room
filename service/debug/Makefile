OBJ = serve
all:
	cc -o $(OBJ) ./*.o -g `pkg-config --cflags --libs gtk+-2.0`
	mv $(OBJ) ../ 
clean:
	rm -rf *.o

