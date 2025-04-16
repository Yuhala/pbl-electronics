SRC_DIR := .
OBJ_DIR := .

EXE := vector_add
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude 
CFLAGS   := -Wall
LDFLAGS  := -Llib
LDLIBS   := 

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) 
		$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
		$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


clean:
		@$(RM) $(OBJ_DIR)/*.o $(EXE)

-include $(OBJ:.o=.d)

#