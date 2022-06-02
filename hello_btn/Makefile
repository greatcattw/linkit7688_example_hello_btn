#gcat 2022.0426.2

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=hello_btn
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define KernelPackage/$(PKG_NAME)
	SUBMENU:=Other modules
	TITLE:=kernel btn test
	VERSION:=$(LINUX_VERSION)-$(BOARD)-$(PKG_RELEASE)
	FILES:= $(PKG_BUILD_DIR)/$(PKG_NAME).$(LINUX_KMOD_SUFFIX)
	DEPENDS:=+kmod-i2c-core
	AUTOLOAD:=$(call AutoLoad,60,$(PKG_NAME))
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	ARCH="$(LINUX_KARCH)" \
	SUBDIRS="$(PKG_BUILD_DIR)" \
	EXTRA_CFLAGS="$(BUILDFLAGS)" \
	modules
endef

#define KernelPackage/demo/install
#  $(INSTALL_DIR) $(1)/lib/network/
#endef

$(eval $(call KernelPackage,$(PKG_NAME)))
