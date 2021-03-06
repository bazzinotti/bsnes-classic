include nall/Makefile
snes := snes
ifeq ($(profile),)
  profile := debugger
endif
ifeq ($(ui),)
  ui := ui-qt
endif

# compiler
c       := $(compiler) -x c -std=gnu99
cpp     := $(compiler) -std=gnu++0x
flags   := -g -O3 -fomit-frame-pointer -I. -I$(snes)
link    :=
objects :=

# comment this line to enable asserts
flags += -DNDEBUG

# profile-guided instrumentation
# flags += -fprofile-generate
# link += -lgcov

# profile-guided optimization
# flags += -fprofile-use

# platform
ifeq ($(platform),x)
  link += -s -ldl -lX11 -lXext
  flags += -fPIC
else ifeq ($(platform),osx)
	# Custom QT Path
	QT_PATH ?= /usr/local/Cellar/qt5/5.4.2
else ifeq ($(platform),win)
  link += -mwindows
# link += -mconsole
  link += -mthreads -s -luuid -lkernel32 -luser32 -lgdi32 -lcomctl32 -lcomdlg32 -lshell32 -lole32
  link += -Wl,-enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc
else
  unknown_platform: help;
endif

# implicit rules
compile = \
  $(strip \
    $(if $(filter %.c,$<), \
      $(c) $(flags) $1 -c $< -o $@, \
      $(if $(filter %.cpp,$<), \
        $(cpp) $(flags) $1 -c $< -o $@ \
      ) \
    ) \
  )

%.o: $<; $(call compile)

all: build;

include $(snes)/Makefile
include $(ui)/Makefile

objects := $(patsubst %,obj/%.o,$(objects))

# targets
build: ui_build $(objects)
ifeq ($(platform),osx)
	test -d ../bsnes.app || mkdir -p ../bsnes.app/Contents/MacOS
	$(strip $(cpp) -o ../bsnes.app/Contents/MacOS/bsnes $(objects) $(link))
	cp Info.plist ../bsnes.app/Contents
else
	$(strip $(cpp) -o out/bsnes $(objects) $(link))
endif

install:
ifeq ($(platform),x)
	install -D -m 755 out/bsnes $(DESTDIR)$(prefix)/bin/bsnes
	install -D -m 644 data/bsnes.png $(DESTDIR)$(prefix)/share/pixmaps/bsnes.png
	install -D -m 644 data/bsnes.desktop $(DESTDIR)$(prefix)/share/applications/bsnes.desktop
	test -d ~/.bsnes || mkdir ~/.bsnes
	cp data/cheats.xml ~/.bsnes/cheats.xml
	chmod 777 ~/.bsnes ~/.bsnes/cheats.xml
endif

uninstall:
ifeq ($(platform),x)
	rm $(DESTDIR)$(prefix)/bin/bsnes
	rm $(DESTDIR)$(prefix)/share/pixmaps/bsnes.png
	rm $(DESTDIR)$(prefix)/share/applications/bsnes.desktop
endif

clean: ui_clean
	-@$(call delete,obj/*.o)
	-@$(call delete,obj/*.a)
	-@$(call delete,obj/*.so)
	-@$(call delete,obj/*.dylib)
	-@$(call delete,obj/*.dll)
	-@$(call delete,*.res)
	-@$(call delete,*.pgd)
	-@$(call delete,*.pgc)
	-@$(call delete,*.ilk)
	-@$(call delete,*.pdb)
	-@$(call delete,*.manifest)

archive-all:
	tar -cjf bsnes.tar.bz2 data launcher libco nall obj out ruby snes ui-qt Makefile cc.bat clean.bat sync.sh

help:;
