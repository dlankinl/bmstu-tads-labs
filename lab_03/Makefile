CC := gcc

C_DIR := ./src
H_DIR := ./inc
OBJ_DIR := ./out

C_FILES := $(wildcard $(C_DIR)/*.c)
H_FILES := $(wildcard $(H_DIR)/*.h)
OBJ_FILES := $(C_FILES:$(C_DIR)/%.c=$(OBJ_DIR)/%.o)

C_FLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion

APP := app.exe

$(APP): $(OBJ_FILES)
	$(CC) $^ -o $@


$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(C_DIR)/%.c $(H_FILES) $(OBJ_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(OBJ_DIR)/*.o *.exe $(OBJ_DIR)/*.gcda $(OBJ_DIR)/*.gcno $(OBJ_DIR)/report $(OBJ_DIR)/*.info

release: clean $(APP)