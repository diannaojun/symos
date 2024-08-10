# Symbol DT
# SymOS Makefile
# DiannaoJun
# 2024-04-05

RM  :=  rm -rf

DEFAULT: IMG

BUILD:
	cd lib && $(MAKE)
	cd kernel && $(MAKE)
	# 生成系统原始镜像（.img） 不清理

CLEAN:
	# cd lib && $(MAKE) CLEAN
	cd kernel && $(MAKE) CLEAN
	# 清理

IMG: BUILD CLEAN
	# 生成系统原始镜像（.img） 清理

VM_IMG: BUILD
	rm -rf ./*.vmdk
	bximage -func=convert -imgmode=vmware4 ./kernel/kernel.img ./OS.vmdk
	$(MAKE) CLEAN
	# 生成系统镜像（.vmdk） 清理

DEBUG: BUILD 
	rm -rf ./*.vmdk
	bximage -func=convert -imgmode=vmware4 ./kernel/kernel.img ./OS.vmdk
	# 生成系统镜像（.vmdk） 不清理
