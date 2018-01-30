###########################################3
#
#    Makefile for ServDiscLib
#

GCC          = gcc
C99          = -std=c99
CFLO         = -c -Wall -g -Werror -fpic
CFLSO        = -shared -o
CIN          = -I../include/
CINLIB       = -I../../include/
CFLAGS       = -fPIC -shared 

TARGET  = libmyLib.so

#debug level
ifeq ($(D),error)
	DEBUG_LEVEL=1
else 
	ifeq ($(D),trace)
		DEBUG_LEVEL=2
	else
		ifeq ($(D),all)
			DEBUG_LEVEL=3
		else
			DEBUG_LEVEL=0
		endif
	endif
endif

#precompile variables
DFLAGS=-DDEBUG_LEVEL=$(DEBUG_LEVEL)


# Source file of Lib
SOURCES = \
	../src/IORaw.c \
	../src/Filters.c \
	../src/shared.c \
	../src/ApplyFiltersSimple.c

	
BASESRC = $(foreach file, $(SOURCES), $(notdir $(file) ) )
OBJECT := $(BASESRC:.c=.o)

all: obj $(TARGET)

obj:
	$(GCC) $(CFLO) ../src/IORaw.c $(CINLIB) $(CIN) $(C99) $(DFLAGS)
	$(GCC) $(CFLO) ../src/Filters.c $(CINLIB) $(CIN) $(C99) $(DFLAGS)
	$(GCC) $(CFLO) ../src/shared.c $(CINLIB) $(CIN) $(C99) $(DFLAGS)
	$(GCC) $(CFLO) ../src/ApplyFiltersSimple.c $(CINLIB) $(CIN) $(C99) $(DFLAGS)
#	$(foreach file, $(SOURCES), ($(GCC) $(CFLO) $(file) $(CINLIB) $(CIN) $(C99) $(DFLAGS)))

$(TARGET):
	$(GCC) $(CFLSO) $(TARGET) $(OBJECT)
	
clean:
	rm -f $(TARGET) $(wildcard *.o)