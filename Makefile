# Symbol DT
# SymOS
# DiannaoJun
# 2024-04-05

DEFAULT:
	cd lib && $(MAKE)
	cd kernel && $(MAKE)
	# 生成系統原始鏡像
	# 要生成`.vmdk'格式的虛擬檔案請使用`VM_IMAGE’
VM_IMAGE: DEFAULT
	rm -rf ./OS.vmdk
	bximage -func=convert -imgmode=vmware4 ./kernel/kernel.img ./OS.vmdk
