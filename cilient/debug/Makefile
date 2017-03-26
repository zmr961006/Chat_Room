OBJ = cilent

all:
	cc -o $(OBJ) ./*.o -g `pkg-config --cflags --libs gtk+-2.0` -lpthread
	mv $(OBJ) ../ 
clean:
	rm -rf *.o
