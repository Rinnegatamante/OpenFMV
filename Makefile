SOURCES	:= .

LIBS = -lsoloud -lz -lm -limgui -lvitaGL -lvitashark -lSceShaccCgExt -lmathneon -ltaihen_stub \
  -lSceAppMgr_stub -lSceAppUtil_stub -lSceAudio_stub -lSceCtrl_stub -lSceCommonDialog_stub \
  -lSceDisplay_stub -lSceFios2_stub -lSceGxm_stub -lSceShaccCg_stub -lSceSysmodule_stub \
  -lScePower_stub -lSceKernelDmacmgr_stub -lSceAvPlayer_stub -lSceTouch_stub \
  -Wl,--whole-archive -lpthread -Wl,--no-whole-archive

CFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.c))
CPPFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.cpp))
BINFILES := $(foreach dir,$(DATA), $(wildcard $(dir)/*.bin))
OBJS     := $(addsuffix .o,$(BINFILES)) $(CFILES:.c=.o) $(CPPFILES:.cpp=.o) 

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
CFLAGS  = -fno-lto -g -Wl,-q

ifeq ($(LATE_SHIFT),1)
CFLAGS += -DLATE_SHIFT
TARGET := lateshift
APP_NAME := "Late Shift"
DATA_FILES := "data/Late Shift"
TITLEID := LATESHIFT
endif

ifeq ($(FIVE_DATES),1)
CFLAGS += -DFIVE_DATES
TARGET := fivedates
APP_NAME := "Five Dates"
DATA_FILES := "data/Five Dates"
TITLEID := FIVEDATES
endif

CXXFLAGS  = $(CFLAGS) -fno-exceptions -std=gnu++11 -fpermissive
ASFLAGS = $(CFLAGS)

all: $(TARGET).vpk

%.vpk: eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLEID) -d ATTRIBUTE2=12 $(APP_NAME) param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin $@ \
		-a $(DATA_FILES)=data

eboot.bin:$(TARGET).elf
	cp $< $<.unstripped.elf
	$(PREFIX)-strip -g $<
	vita-elf-create $< $@
	vita-make-fself -c -s $@ eboot.bin

$(TARGET).elf: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf eboot.bin $(TARGET).elf $(TARGET).elf.unstripped.elf $(TARGET).vpk $(OBJS)