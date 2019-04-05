CC = mpic++

SRCS = $(shell find $(SRCDIR) -name *.cpp)

TARGET = mpi_radix_sort

all: $(TARGET)

$(TARGET):
	$(CC) -o $(TARGET) ./src/$(TARGET).cpp

clean:
	$(RM) $(TARGET)

