OBJ = ../debug 
TGT = $(shell pwd)

all:
	cc -c ./*.c  `pkg-config --cflags --libs gtk+-2.0` -lpthread
	cp -p $(TGT)/*.o $(OBJ)
	rm -rf ./*.o
clean:
	rm -rf ./*.o
