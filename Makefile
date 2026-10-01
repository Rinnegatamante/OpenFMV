SOURCES	:= .

CFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.c))
CPPFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.cpp))
BINFILES := $(foreach dir,$(DATA), $(wildcard $(dir)/*.bin))
OBJS     := $(addsuffix .o,$(BINFILES)) $(CFILES:.c=.o) $(CPPFILES:.cpp=.o) 

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
PKG_CONFIG = arm-vita-eabi-pkg-config
MEDIA_CFLAGS := $(shell $(PKG_CONFIG) --cflags SDL2_mixer_ext sndfile)
MEDIA_LIBS := $(shell $(PKG_CONFIG) --static --libs SDL2_mixer_ext sndfile)
CFLAGS  = -fno-lto -g -Wl,-q $(MEDIA_CFLAGS)
LIBS := -limgui $(MEDIA_LIBS)

# Available audio backends
# ALmixer
#CFLAGS += -DHAVE_ALMIXER -I${VITASDK}/arm-vita-eabi/include/AL
#LIBS += -lALmixer -lopenal -lmpg123 -lvorbisfile -lvorbis -logg -lSceAudioIn_stub
# SoLoud
CFLAGS += -DHAVE_SOLOUD
LIBS += -lsoloud
# SDL2 Mixer X
CFLAGS += -DHAVE_SDL2_MIXER_EXT
LIBS += -lSDL2_mixer_ext -lSDL2 -lSceMotion_stub -lSceIme_stub -lSceHid_stub -lmpg123 -lvorbisfile -lvorbis \
	-lmikmod -lFLAC -lSceAudioIn_stub -lopusfile -lopus -logg -lxmp -lmodplug

LIBS += -lz -lm -lvitaGL -lvitashark -lSceShaccCgExt -lmathneon -ltaihen_stub \
  -lSceAppMgr_stub -lSceAppUtil_stub -lSceAudio_stub -lSceCtrl_stub -lSceCommonDialog_stub \
  -lSceDisplay_stub -lSceFios2_stub -lSceGxm_stub -lSceShaccCg_stub -lSceSysmodule_stub \
  -lScePower_stub -lSceKernelDmacMgr_stub -lSceAvPlayer_stub -lSceTouch_stub \
  -pthread -lSceNpTrophy_stub

ifeq ($(LATE_SHIFT),1)
CFLAGS += -DLATE_SHIFT -DHAVE_TROPHIES
TARGET := lateshift
APP_NAME := "Late Shift"
DATA_FILES := "data/Late Shift"
TITLEID := LATE00001
endif

ifeq ($(FIVE_DATES),1)
CFLAGS += -DFIVE_DATES
TARGET := fivedates
APP_NAME := "Five Dates"
DATA_FILES := "data/Five Dates"
TITLEID := FIVE00001
endif

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG
endif

CXXFLAGS  = $(CFLAGS) -fno-exceptions -std=gnu++11 -fpermissive
ASFLAGS = $(CFLAGS)

all: $(TARGET).vpk

%.vpk: eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLEID) -d ATTRIBUTE2=12 $(APP_NAME) param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin $@ \
		-a assets/$(TARGET)/bg.png=sce_sys/livearea/contents/bg.png \
		-a assets/$(TARGET)/template.xml=sce_sys/livearea/contents/template.xml \
		-a assets/$(TARGET)/startup.png=sce_sys/livearea/contents/startup.png \
		-a assets/$(TARGET)/icon0.png=sce_sys/icon0.png \
		-a assets/$(TARGET)/TROPHY.TRP=sce_sys/trophy/$(TITLEID)_00/TROPHY.TRP \
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