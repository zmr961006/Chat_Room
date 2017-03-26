COM = $(shell pwd)/common
PER = $(shell pwd)/prest
SER = $(shell pwd)/srv
OBJ = $(shell pwd)/debug
VIE = $(shell pwd)/view

all:
	cd $(COM) && make
	cd $(PER) && make
	cd $(SER) && make
	cd $(VIE) && make
	cd $(OBJ) && make
clean:
	rm -rf *.o
