CC = g++
CFLAGS = -Wall -std=c++11 -O2

################!! MODIFY HERE !!####################
_OBJ = MipsSimulatorClass.o UsefulStructures.o CommandClass.o PipelineClass.o main.o
_DEPS = MipsSimulatorClass.h UsefulStructures.h CommandClass.h PipelineClass.h
#####################################################

ODIR = obj
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

IDIR = .
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(shell mkdir -p bin)
	$(shell mkdir -p obj)
	$(CC) -c -o $@ $< $(CFLAGS)

mips: $(OBJ)
	$(CC) -o bin/mips $^ $(CFLAGS)

.PHONY: clean all rebuild

clean:
	rm -f $(ODIR)/*
	rm -f bin/*

all:
	mips

rebuild: clean all
