CC 			= g++
CFLAGS 		= -Wall
OBJFILES 	= Server.o HttpRequest.o HttpRequestParser.o HttpResponse.o HttpResponseBuilder.o LinuxSocket.o Main.o
TARGET 		= prism

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~