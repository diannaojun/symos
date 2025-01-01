default: build_all

build_all: amd64_build

amd64_build: ./amd64/*
	$(MAKE) -C ./amd64 build AS=$(AS) PRJ=$(PRJ) TEMP=$(TEMP)

clean_all: amd64_clean

amd64_clean:
	$(MAKE) -C ./amd64 clean AS=$(AS) PRJ=$(PRJ) TEMP=$(TEMP)
