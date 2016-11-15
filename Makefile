CXX = clang++
SDL = -framework SDL2
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c++11 -Iemulate -include emulate/emulate.h
LDFLAGS = $(SDL) -lstdc++
# default sketch to compile
SKETCH = test1
SOURCES=$(shell find . \( -name "*.cpp" -o -name "*.c" \) -not -path \"./sketches/*\")
OBJECTS=$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))
EXE = bin/$(SKETCH)

all: $(EXE)

$(EXE): main.o $(OBJECTS)
	mkdir -p ./bin && $(CXX) $(LDFLAGS) $^ -o $@

VPATH = libraries:emulate:sketches/$(SKETCH)

%.o: %.c
	$(CXX) $(CXXFLAGS) -DSKETCH=\"sketches/$(SKETCH)/$(SKETCH).ino\" $< -o $@
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -DSKETCH=\"sketches/$(SKETCH)/$(SKETCH).ino\" $< -o $@
	
clean:
	find . -name '*.o' -delete; rm -f $(EXE)
