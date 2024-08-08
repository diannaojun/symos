# Symbol DT
# SymOS
# DiannaoJun
# 2024-04-05

DEFAULT:
	cd lib && $(MAKE)
	cd kernel && $(MAKE)
	# 生成系统原始镜像
	# 要生成 '.vmdk' 格式的虚拟机文件使用参数 'VM_IMAGE'

CLEAN:
	cd kernel && $(MAKE) CLEAN
	# 清理

VM_IMAGE: DEFAULT
	rm -rf ./OS.vmdk
	bximage -func=convert -imgmode=vmware4 ./kernel/kernel.img ./OS.vmdk
