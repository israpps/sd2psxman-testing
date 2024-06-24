IOP_BIN_DIR = irx/
IOP_SRC_DIR = src/
IOP_BIN = $(IOP_BIN_DIR)sd2psxman.irx
IOP_OBJS = sd2psxman.o ioplib.o imports.o

MODE ?= RPC
MODES = 'FS' 'RPC'

ifeq ($(DEBUG), 1)
  $(info -- SD2PSXMAN debug enabled)
  IOP_CFLAGS += -DDEBUG=1
endif

ifeq ($(MODE),FS)
  IOP_BIN = $(IOP_BIN_DIR)sd2psxman_fs.irx
  $(info -- SD2PSXMAN: filesystem mode)
  IOP_CFLAGS += -DSUPPORT_CARD_FILESYSTEM=1
  IOP_OBJS += filesystem.o
else ifeq ($(MODE),RPC)
  $(info -- SD2PSXMAN: RPC mode)
  IOP_CFLAGS += -DRPC_SUPPORT=1
  IOP_OBJS += rpc.o
else
  $(error unknown MODE '$(MODE)', available modes are $(MODES))
endif

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
