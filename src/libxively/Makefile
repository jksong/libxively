LIBXIVELY := $(shell git rev-parse --show-toplevel)
include $(LIBXIVELY)/Makefile.include

XI_LAYER_DIRS := comm_layers/$(XI_COMM_LAYER)

XI_CFLAGS += -I. \
	$(foreach layerdir,$(XI_LAYER_DIRS),-I./$(layerdir))

XI_SOURCES = $(wildcard *.c) \
	$(wildcard comm_layers/$(XI_COMM_LAYER)/*.c)

all: $(XI)

objs: $(XI_OBJS)
deps: $(XI_DEPS)

$(XI): $(XI_OBJS)
ifeq ($(findstring CYGWIN,$(shell uname)),CYGWIN)
	$(AR) $(XI_ARFLAGS) $(shell cygpath -a -m $(XI)) $(shell cygpath -a -m $(XI_OBJS))
else
	$(AR) $(XI_ARFLAGS) $(XI) $(XI_OBJS)
endif

include $(LIBXIVELY)/Makefile.rules

ifneq ($(MAKECMDGOALS),clean)
  -include $(XI_DEPS)
endif
