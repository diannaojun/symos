PRJ		:=	$(CURDIR)

build: clean
	$(MAKE) -C ./arch build PRJ=$(PRJ)

debug: clean
	$(MAKE) -C ./arch debug PRJ=$(PRJ)

run: debug
	- bochs

clean: *
ifeq ($(wildcard $(PRJ)/kernel), )
	- mkdir $(PRJ)/kernel
else
	- rm $(PRJ)/kernel/*
	$(MAKE) -C ./arch clean PRJ=$(PRJ)
endif
