LIBXIVELY := $(shell git rev-parse --show-toplevel)
include $(LIBXIVELY)/Makefile.include

XI_SOURCES = $(wildcard *.c) \
	$(wildcard io/$(XI_IO_LAYER)/*.c) \
	$(wildcard io/$(XI_IO_LAYER)/*.cpp)

XI_LAYER_DIRS := io/$(XI_IO_LAYER)

ifeq ($(XI_NOB_ENABLED),true)
    XI_LAYER_DIRS += nob
    XI_SOURCES += $(wildcard nob/*.c)
endif

ifeq ($(XI_MQTT_ENABLED),true)
    XI_SOURCES += $(wildcard mqtt/codec/*.c)
    XI_LAYER_DIRS += mqtt mqtt/codec
endif

XI_CFLAGS += -I./ \
	$(foreach layerdir,$(XI_LAYER_DIRS),-I./$(layerdir))

all: $(XI)

objs: $(XI_OBJS)
deps: $(XI_DEPS)

$(XI): $(XI_OBJS)
	$(AR) $(XI_ARFLAGS) $(XI) $(XI_OBJS)

include $(LIBXIVELY)/Makefile.rules

ifneq ($(MAKECMDGOALS),clean)
  -include $(XI_DEPS)
endif
