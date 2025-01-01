AS		:=	nasm
PRJ		:=	./build
TEMP	:=	$(PRJ)/temp

build:
	- mkdir $(PRJ)
	- mkdir $(TEMP)
	$(MAKE) ./arch

clean:
	$(MAKE) ./arch clean_all
