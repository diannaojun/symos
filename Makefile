# Symbol DT
# SymOS
# DiannaoJun
# 2024-04-05

DEFAULT:
	cd lib && $(MAKE)
	cd kernel && $(MAKE)
VM_IMAGE: DEFAULT
	rm -rf ./OS.vmdk
	bximage -func=convert -imgmode=vmware4 ./kernel/kernel.img ./OS.vmdk
