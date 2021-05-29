# Simple makefile for gcc written by stext editor.
CC?=gcc
CFLAGS+=-std=c11 -W -O -pedantic -fPIC -I$(INCDIR)
LDFLAGS=

BACKUPS=$(shell find . -iname "*.bak")
SRCDIR=$(shell basename $(shell pwd))
DESTDIR?=
PREFIX?=usr
VERSION=1.0

INCDIR=./include
SOURCE=$(wildcard ./src/*.c)
OBJECTS=$(SOURCE:%.c=%.c.o)
DEPS=$(SOURCE:%.c=%.c.d)
TARGET=$(SRCDIR)

.PHONY: all install uninstall clean distclean dist
all: lib$(TARGET).so lib$(TARGET).a

%.c.d: %.c #$(INCDIR)/*.h
	@set -e; rm -f $@; \
	$(CC) $(CFLAGS) -MM $< > $@; \
	echo Dependency $@ created...

%.c.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

lib$(TARGET).so: $(DEPS) $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJECTS) $(LDFLAGS)

lib$(TARGET).a: $(DEPS) $(OBJECTS)
	$(AR) rcs $@ $(OBJECTS)

install: all
	mkdir -p $(DESTDIR)/$(PREFIX)/include/$(TARGET)
	mkdir -p $(DESTDIR)/$(PREFIX)/lib
	install $(INCDIR)/*.h $(DESTDIR)/$(PREFIX)/include/$(TARGET)
	install lib$(TARGET).so $(DESTDIR)/$(PREFIX)/lib/lib$(TARGET).so
	install lib$(TARGET).a $(DESTDIR)/$(PREFIX)/lib/lib$(TARGET).a

uninstall:
	rm -rf $(DESTDIR)/$(PREFIX)/include/$(TARGET)
	rm -f $(DESTDIR)/$(PREFIX)/lib/lib$(TARGET).so
	rm -f $(DESTDIR)/$(PREFIX)/lib/lib$(TARGET).a

clean:
	rm -f $(OBJECTS) lib$(TARGET).so lib$(TARGET).a

distclean: clean
ifneq ($(BACKUPS),)
	rm -f $(BACKUPS)
endif
	rm -f $(DEPS)

dist: distclean
	cd .. && tar -cv --exclude=.git ./$(SRCDIR) | xz -9 > $(SRCDIR)-$(VERSION).tar.xz
