CXX = g++
CXXFLAGS = -std=c++20 -Wall -Iinclude -Iexternal/SFML-2.6.2/include -Iexternal/box2d/include -MMD -MP
LDFLAGS = -Lexternal/SFML-2.6.2/lib -Lexternal/box2d/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

SRCDIR = src
BUILDDIR = build
TARGET = build/game

SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))
DEPS = $(OBJECTS:.o=.d)

all: $(TARGET) copy-sfml-binaries copy-assets

$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

copy-sfml-binaries:
	cp external/SFML-2.6.2/bin/*.dll $(BUILDDIR)

# Rule to copy assets to the build directory
copy-assets:
	cp -r assets $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

-include $(DEPS)

.PHONY: all clean copy-sfml-binaries copy-assets
