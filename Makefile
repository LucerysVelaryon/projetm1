SOURCES = code/__main__.cpp code/annexes.cpp code/grille.cpp code/joueur.cpp

CXX = g++
LDFLAGS = -std=c++11 -Wall -Wextra
CPPFLAGS = -std=c++11 -Wall -Wextra -Wno-ignored-attributes
LDLIBS =

OBJETS = $(subst .cpp,.o,$(SOURCES))

all: build

build: $(OBJETS)
	$(CXX) $(LDFLAGS) -o Othello $(OBJETS) $(LDLIBS)

depend: .depend

.depend: $(SOURCES)
	rm -f ./code/.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./code/.depend ;

clean:
	rm $(OBJETS)

dist-clean: build clean
	rm -f *~ code/.depend 
	rm Othello 

include .depend
