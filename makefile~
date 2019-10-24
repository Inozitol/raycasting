# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11

# Libraries
LIBS = -lm -lSDL2

# Source files
SOURCE = CApp.cpp CApp_OnCleanup.cpp CApp_OnEvent.cpp CApp_OnInit.cpp CApp_OnLoop.cpp CApp_OnRender.cpp CAnimation.cpp CEntity.cpp CEvent.cpp CMap.cpp CPlayer.cpp CSurface.cpp

# Header files
HEADER = CApp.h CAnimation.h CEntity.h CEvent.h CMap.h CPlayer.h CSurface.h

# Build target executable name
TARGET = CAPP

all: $(TARGET)

$(TARGET): $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) $(LIBS) -o $(TARGET) $(SOURCE)

clean:
	$(RM) $(TARGET)
