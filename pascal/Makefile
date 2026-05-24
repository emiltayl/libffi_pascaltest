FPC ?= fpc
FPCFLAGS ?= -Mobjfpc -Pi386 -Tlinux -Cg -g

TARGET := libstruct_abi.so
SOURCE := struct_abi.pas

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(FPC) $(FPCFLAGS) -o$(TARGET) $(SOURCE)

clean:
	$(RM) $(TARGET) struct_abi.o struct_abi.ppu struct_abi.a struct_abi.s link.res
