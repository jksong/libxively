LIBXIVELY := $(shell git rev-parse --show-toplevel)
include $(LIBXIVELY)/Makefile.include

XI_LAYER_DIRS := io/$(XI_IO_LAYER)
XI_CFLAGS += -I$(LIBXIVELY)

ifeq ($(XI_NOB_ENABLED),true)
    XI_LAYER_DIRS += nob
endif

ifeq ($(XI_CYASSL_ENABLED),true)
	CYASSL = $(XI_CYASSL_PATH)
	XI_CFLAGS += -I$(XI_CYASSL_INCLUDES)
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

$(CYASSL):
	echo "CYASSL"
	@if [ -f $(XI_CYASSL)/Makefile ]; then make -C $(XI_CYASSL); else cd $(XI_CYASSL) && ./configure --enable-static --enable-shared=no  && make && cd $(LIBXIVELY); fi;

include $(LIBXIVELY)/Makefile.rules

ifneq ($(MAKECMDGOALS),clean)
  -include $(XI_DEPS)
endif
