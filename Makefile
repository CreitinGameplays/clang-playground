# Compiler and flags
CC = clang
#CFLAGS = -fsanitize=address -g -fno-omit-frame-pointer -O0 -std=c23 -Wall -Wextra
CFLAGS = -g -fno-omit-frame-pointer -O0 -std=c23 -Wall -Wextra # asan eats memory as hell
SRC = src/vec.c \
	src/conversor.c \
	example.c \

# Directories and targets
BUILD_DIR = build
TARGET = $(BUILD_DIR)/my_simple_vec.exe

# Default rule
all: $(TARGET)

# Build rule
$(TARGET): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean rule
clean:
	rm -rf $(BUILD_DIR)
