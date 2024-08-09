# Symbol DT
# SymOS Makefile
# DiannaoJun
# 2024-04-05

RM  :=  rm -rf

DEFAULT: BUILD CLEAN

BUILD:
	cd lib && $(MAKE)
	cd kernel && $(MAKE)
	# 生成系统原始镜像
	# 要生成 '.vmdk' 格式的虚拟机文件使用参数 'VM_IMAGE'

CLEAN:
	# cd lib && $(MAKE) CLEAN
	cd kernel && $(MAKE) CLEAN
	# 清理

IMG_CLEAN:
	$(RM) ./*.vmdk
	$(RM) ./*.img
	cd kernel && $(MAKE) IMG_CLEAN

VM_IMAGE: BUILD
	rm -rf ./OS.vmdk
	bximage -func=convert -imgmode=vmware4 ./kernel/kernel.img ./OS.vmdk
	$(MAKE) CLEAN
VM_IMAGE: BUILD
	rm -rf ./OS.vmdk
	bximage -func=convert -imgmode=vmware4 ./kernel/kernel.img ./OS.vmdk
	$(MAKE) CLEAN