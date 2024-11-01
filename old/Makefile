# Symbol DT
# SymOS Makefile
# DiannaoJun
# 2024-04-05

RM  :=  rm -rf

.silent:

default: image

help:
	# help              Show this
	# build             Generate raw image
	# clean             Clean
	# image(default)    build & clean
	# debug             Generate a .vmdk file
	# vm_image          debug & clean

build:
	cd lib && $(MAKE)
	cd kernel && $(MAKE)

clean:
	# cd lib && $(MAKE) clean
	cd kernel && $(MAKE) clean

image: build

debug: build 
	rm -rf ./*.vmdk
	bximage -func=convert -imgmode=vmware4 ./kernel/kernel.img ./OS.vmdk

vm_image: build clean

