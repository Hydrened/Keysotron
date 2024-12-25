CC = g++
CPP_VERSION = c++17
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include
APP_NAME = Keysotron.exe

all:
	make app
	make run

app:
	$(CC) -std=$(CPP_VERSION) -m64 -o $(BIN_DIR)/$(APP_NAME) $(SRC_DIR)/*.cpp -I$(INCLUDE_DIR)

wl:
	$(CC) -std=$(CPP_VERSION) -m64 -mwindows -o $(BIN_DIR)/$(APP_NAME) $(SRC_DIR)/*.cpp -I$(INCLUDE_DIR)

run:
	cd $(BIN_DIR) && $(APP_NAME)

test:
	cd $(BIN_DIR) && $(APP_NAME) -d 1
