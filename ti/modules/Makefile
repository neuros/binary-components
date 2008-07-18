ifndef PRJROOT
    $(error You must first source the BSP environment: "source neuros-env")
endif

install: clean
	mkdir -p .tmp_versions
	echo $(shell pwd)/cmemk.ko > .tmp_versions/cmemk.mod
	touch cmemk.o
	echo $(shell pwd)/dsplinkk.ko > .tmp_versions/dsplinkk.mod
	touch dsplinkk.o
	
	make -C $(KNL_INSTALL_DIR) M=$(shell pwd) ARCH=$(ARCH) modules_install CROSS_COMPILE=$(CROSS_COMPILE)

clean:
	rm -rf .tmp_versions
	rm -f *.o