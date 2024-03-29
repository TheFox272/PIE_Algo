CC = g++
CFLAGS = -Wall -Werror -std=c++20
INC = include/
LIBS = -lm
SRC = src/
BUILD = build/
EXEC = main


all: $(BUILD)$(EXEC)

$(BUILD)$(EXEC): $(BUILD)main.o $(BUILD)eulerien.o $(BUILD)genetic.o $(BUILD)augmentation.o $(BUILD)evolution.o $(BUILD)graph.o
	$(CC) $(CFLAGS) -g $^ -o $@ $(LIBS)

$(BUILD)%.o: $(SRC)%.cpp $(INC)%.hpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INC) -g -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD)
