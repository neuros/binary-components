ifndef PRJROOT
    $(error You must first source the BSP environment: "source neuros-env")
endif

CODEC_INSTALL_DIR=$(INSTALL_MOD_PATH)/opt/ticel

install:
	mkdir -p $(TOOLCHAIN_USR_INSTALL)/lib/ti
	
	@echo Installing codec servers to rootfs.
	@mkdir -p $(CODEC_INSTALL_DIR)/codecs
	@install -m 666 codecs/*.x64P $(CODEC_INSTALL_DIR)

	@echo Installing codec engine static libraries to toolchain-

	@echo - common libraries.
	@mkdir -p $(TOOLCHAIN_USR_INSTALL)/lib/ti/common
	@install -m 666 lib/common/*.a $(TOOLCHAIN_USR_INSTALL)/lib/ti/common
	@cd $(TOOLCHAIN_USR_INSTALL)/lib/ti/common && \
	for lib in *.a ; do ln -sf ti/common/$$lib $(TOOLCHAIN_USR_INSTALL)/lib/$$lib ; done

	@echo - VISA libraries.
	@mkdir -p $(TOOLCHAIN_USR_INSTALL)/lib/ti/visa
	@install -m 666 lib/visa/*.a $(TOOLCHAIN_USR_INSTALL)/lib/ti/visa
	@cd $(TOOLCHAIN_USR_INSTALL)/lib/ti/visa && \
	for lib in *.a ; do ln -sf ti/visa/$$lib $(TOOLCHAIN_USR_INSTALL)/lib/$$lib ; done

	@echo - codec server libraries.
	@mkdir -p $(TOOLCHAIN_USR_INSTALL)/lib/ti/codec
	@install -m 666 lib/codec/*.a $(TOOLCHAIN_USR_INSTALL)/lib/ti/codec
	@cd $(TOOLCHAIN_USR_INSTALL)/lib/ti/codec && \
	for lib in *.a ; do ln -sf ti/codec/$$lib $(TOOLCHAIN_USR_INSTALL)/lib/$$lib ; done

	@echo - module libraries
	@mkdir -p $(TOOLCHAIN_USR_INSTALL)/lib/ti/module
	@install -m 666 lib/module/cmem.a $(TOOLCHAIN_USR_INSTALL)/lib/ti/module
	@install -m 666 lib/module/dsplink.lib $(TOOLCHAIN_USR_INSTALL)/lib/ti/module
	@cd $(TOOLCHAIN_USR_INSTALL)/lib/ti/module && ln -sf ti/module/cmem.a $(TOOLCHAIN_USR_INSTALL)/lib/cmem.a
	@cd $(TOOLCHAIN_USR_INSTALL)/lib/ti/module && ln -sf ti/module/dsplink.lib $(TOOLCHAIN_USR_INSTALL)/lib/dsplink.lib

	@echo Installing headers to toolchain.
	@mkdir -p $(TOOLCHAIN_USR_INSTALL)/include/ti
	@cp -a include/* $(TOOLCHAIN_USR_INSTALL)/include/ti

	@echo Installing config toolchain
	mkdir -p $(TOOLCHAIN_USR_INSTALL)/bin
	install -m 776 ticel-config $(TOOLCHAIN_USR_INSTALL)/bin/ticel-config

	make -C modules $@

