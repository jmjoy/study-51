SDCC ?= sdcc
STCGAL ?= stcgal
TTY ?= /dev/ttyCH341USB0

TARGETS := $(wildcard */main.c)
BUILD_TARGETS := $(patsubst %/main.c,%,$(TARGETS))

.PHONY: all $(BUILD_TARGETS)

all: help

help:
	@echo "========== HELP =========="
	@echo "'$(MAKE) <TARGET>'：构建并烧录。"
	@echo "'$(MAKE) <TARGET>-build'：只构建。"
	@echo "'$(MAKE) <TARGET>-flash'：只烧录。"
	@echo "========== 可选<TARGET> =========="
	@echo "$(BUILD_TARGETS)"

$(foreach target,$(BUILD_TARGETS),$(eval $(target): $(target)-build $(target)-flash;))

$(foreach target,$(BUILD_TARGETS),$(eval $(target)-build: _build/$(target).hex;))

_build/%.hex: %/main.c
	$(SDCC) $*/main.c -o _build/$*.hex

%-flash:
	$(STCGAL) -P auto -p $(TTY) -a _build/$*.hex
