#######################################
#
#   Makefile for Parallel
#

EXE=run-d
EXETEST=test.$(EXE)
TESTOUTFILE=test.out

BASEDIR := ./
ROOTSRC=../src/
ROOTTEST=../test/
ROOTUNIT=../utest/

MKDIR_P=mkdir -p
OUTDIR=../obj/

GCC=gcc
GCCFLAGS=-Wall -g -O3 -o 

CIN=-I ../include
CINLIB= -I ../Libs/include


#Test parameters
CINUNIT=-I $(ROOTUNIT)
TEST_C := $(wildcard $(ROOTTEST)*.c)
TEST_O := $(patsubst $(ROOTTEST)%.c, %.o,$(TEST_C))
UNI_C= $(ROOTUNIT)uni.c
UNI_O= $(OUTDIR)uni.o

#Libraries
LIBS = \
	../Libs/myLib 
	
LIBLINK := $(foreach lib, $(LIBS), -L$(BASEDIR)/$(lib)/build -l$(notdir $(lib)) ) 
 

#Files for executable
MAIN_C=$(ROOTSRC)main/main.c
MAIN_O=$(OUTDIR)main.o


OBJS=$(MAIN_O) $(SRC_O) $(TEST_O)

#debug level
ifeq ($(D),error)
	DEBUG_LEVEL=1
	C99=-std=c99
else 
	ifeq ($(D),trace)
		DEBUG_LEVEL=2
		C99=--std=c99
	else
		ifeq ($(D),all)
			DEBUG_LEVEL=3
			C99=--std=c99
		else
			DEBUG_LEVEL=0
		endif
	endif
endif

#precompile variables
DFLAGS=-DDEBUG_LEVEL=$(DEBUG_LEVEL)

# Targets 

ifeq ($(SKIP_TEST),true)
all: directories libs default
else
all: directories libs default install_lib test_all
endif

directories: $(OUTDIR)

libs:
	$(foreach lib,$(LIBS),$(MAKE) -C $(lib)/build D=$(D);)
	

default: $(EXE)

run: $(EXE)
	./$(EXE)

memtest: directories test $(EXE) $(EXETEST)
	rm -f $(TEST_O)
	valgrind --leak-check=yes -v ./$(EXE)
	valgrind --leak-check=yes -v ./$(EXETEST) reg

install_lib:
	$(foreach libpath, $(LIBS), sudo cp $(BASEDIR)/$(libpath)/build/lib* /usr/lib;)

test_all: test $(EXETEST)
	rm -f $(TEST_O)
	./$(EXETEST) reg > $(TESTOUTFILE)
	
test:
	$(foreach file,$(TEST_C),($(GCC) -c $(file) $(CINUNIT) $(CIN) $(CINLIB) );)

$(OUTDIR):
	$(MKDIR_P) $(OUTDIR)

$(EXE): $(MAIN_O)
	$(GCC) $(GCCFLAGS) $(EXE) $(MAIN_O) $(LIBLINK)

$(EXETEST): $(TEST_O) $(UNI_O)
	$(GCC) $(GCCFLAGS) $(EXETEST) $(TEST_O) $(UNI_O) $(LIBLINK)
	

$(MAIN_O): $(MAIN_C)
	$(GCC) -c $(MAIN_C) -o $(MAIN_O) $(CIN) $(DFLAGS)

$(SRC_O): $(SRC_C)
	$(GCC) -c $(SRC_C) -o $(SRC_O) $(CIN) $(DFLAGS)

$(UNI_O): $(UNI_C)
	$(GCC) -c $(UNI_C) -o $(UNI_O) $(CIN) $(DFLAGS)
	

clean:
	rm -rf ${OUTDIR}
	$(foreach file,$(TEST_O),(rm -f $(file) );)
	$(foreach lib, $(LIBS), $(MAKE) -C $(lib)/build/ clean;)	
	rm -f $(EXE) $(EXETEST) $(TESTOUTFILE)
	





