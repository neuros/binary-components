ifndef PRJROOT
    $(error You must first source the BSP environment: "source neuros-env")
endif

install: clean
	mkdir -p .tmp_versions
	echo $(shell pwd)/neuros_rtc.ko > .tmp_versions/neuros_rtc.mod
	touch neuros_rtc.o
	
	make -C $(KNL_INSTALL_DIR) M=$(shell pwd) ARCH=$(ARCH) modules_install CROSS_COMPILE=$(CROSS_COMPILE)

clean:
	rm -rf .tmp_versions
	rm -f *.o