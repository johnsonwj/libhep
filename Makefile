CC := g++

all: math

math: LorentzVector.o

LorentzVector.o: include/math/LorentzVector.h src/math/LorentzVector.cc
	$(CC) src/math/
