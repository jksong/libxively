LIBXIVELY := $(shell git rev-parse --show-toplevel)
include $(LIBXIVELY)/Makefile.include

XI_LAYER_DIRS := io/$(XI_IO_LAYER)

ifeq ($(XI_NOB_ENABLED),true)
    XI_LAYER_DIRS += nob
endif

ifeq ($(XI_CYASSL_ENABLED),true)
	CYASSL=cyassl
endif

XI_CFLAGS += -I./ \
	$(foreach layerdir,$(XI_LAYER_DIRS),-I./$(layerdir))

XI_SOURCES = $(wildcard *.c) \
	$(wildcard io/$(XI_IO_LAYER)/*.c) \
	$(wildcard io/$(XI_IO_LAYER)/*.cpp)

ifeq ($(XI_NOB_ENABLED),true)
    XI_SOURCES += $(wildcard nob/*.c)
endif

all: $(XI) $(CYASSL)

objs: $(XI_OBJS)
deps: $(XI_DEPS)

$(XI): $(XI_OBJS)
	$(AR) $(XI_ARFLAGS) $(XI) $(XI_OBJS)

cyassl:
	echo "cyassl"

include $(LIBXIVELY)/Makefile.rules

ifneq ($(MAKECMDGOALS),clean)
  -include $(XI_DEPS)
endif
