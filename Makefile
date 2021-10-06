SOURCES=

CXX=g++
LDFLAGS=-std=c++11 -Wall -Wextra
CPPFLAGS=-std=c++11 -Wall -Wextra -Wno-ignored-attributes
LDLIBS=

OBJETS=$(subst .cpp,.o,$(SOURCES))

all: build

build: $(OBJETS)
	$(CXX) $(LDFLAGS) -o run $(OBJETS) $(LDLIBS)

depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	rm $(OBJETS)

dist-clean: clean
	rm -f *~ .depend

include .depend
