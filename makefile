TARGET:=main
CC:=gcc
CFLAGS:=-g -Wall -Wextra -Werror -std=c11 -Wpedantic -MD -MP
SRC:=src
BIN:=./bin

# search subdirs for pattern
filesearch:=	$(wildcard $1$2) $(foreach dir,$(wildcard $1*),$(call filesearch,$(dir)/,$2))

# check all subdirs for source files
SOURCES:=	$(call filesearch,$(SRC),*.c)	

# remove main file					
SOURCES:=	$(filter-out %$(TARGET).c, $(SOURCES))											

# build object list
OBJECTS:=	$(patsubst %.c, $(BIN)/%.o, $(notdir $(SOURCES)))								

# Create output directories
$(shell mkdir -p $(BIN))

all: $(TARGET) ## Compile object files and then into an executable
$(BIN)/%.o: $(SRC)/views/%.c
	$(info [i] Generating object files)
	$(CC) -c $(CFLAGS) $^ -o $@

$(BIN)/%.o: $(SRC)/models/%.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(BIN)/%.o: $(SRC)/utils/%.c
	$(CC) -c $(CFLAGS) $^ -o $@
	
$(TARGET): $(SRC)/$(TARGET).c $(OBJECTS)
	$(info [i] Generating binary files)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@
	
.PHONY: help
help: ## Display this help message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

clean: ## Delete the build folder
	$(info [i] Deleting build folder: $(BIN))
	rm -rf $(BIN)