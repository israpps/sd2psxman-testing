IOP_BIN = irx/sd2psxman.irx

IOP_OBJS = sd2psxman.o ioplib.o imports.o

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

ifeq ($(DEBUG), 1)
  $(info -- SD2PSXMAN debug enabled)
  IOP_CFLAGS += -DDEBUG=1
endif

ifeq ($(SUPPORT_CARD_FILESYSTEM), 1)
  $(info -- SD2PSXMAN filesystem enabled)
  IOP_CFLAGS += -DSUPPORT_CARD_FILESYSTEM=1
  IOP_OBJS += filesystem.o
endif

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
