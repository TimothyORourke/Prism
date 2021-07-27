CC 			= g++
CFLAGS 		= -Wall
OBJFILES 	= Server.o HttpResponse.o HttpRequest.o HttpRequestParser.o LinuxSocket.o Main.o
TARGET 		= prism

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~