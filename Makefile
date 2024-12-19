CXX = g++
CXXFLAGS = -std=c++20 -Wall -Iinclude -Iexternal/SFML-2.6.2/include
LDFLAGS = -Lexternal/SFML-2.6.2/lib -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
BUILDDIR = build
TARGET = build/game

SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

all: $(TARGET) copy-sfml-binaries

$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

copy-sfml-binaries:
	cp external/SFML-2.6.2/bin/*.dll $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean copy-sfml-binaries
