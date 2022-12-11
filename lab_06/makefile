CC := gcc

C_DIR := ./src
H_DIR := ./inc
OBJ_DIR := ./out
UNIT_C_DIR := ./unit_tests

C_FILES := $(wildcard $(C_DIR)/*.c)
H_FILES := $(wildcard $(H_DIR)/*.h)
UNIT_C_FILES := $(wildcard $(UNIT_C_DIR)/*.c)
OBJ_FILES := $(C_FILES:$(C_DIR)/%.c=$(OBJ_DIR)/%.o)

UNIT_OBJ := $(UNIT_C_FILES:$(UNIT_C_DIR)/%.c=$(OBJ_DIR)/%.o)
UNIT_OBJ += $(filter-out $(OBJ_DIR)/main.o,$(OBJ_FILES))

C_FLAGS := -std=gnu99 -Wall -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -I ./inc
# UNIT_FLAGS := -lcheck -lpthread -lrt -lsubunit -lm
UNIT_FLAGS := -lcheck -lpthread -lrt

APP := app.exe
UNIT := unit_tests.exe
COV := func_tests.exe

$(APP): $(OBJ_FILES)
	$(CC) $(C_FLAGS) $^ -o $@ -lm

$(UNIT): $(UNIT_OBJ)
	$(CC) $(UNIT_OBJ) -o $@ $(UNIT_FLAGS) -lm

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(C_DIR)/%.c $(HEADS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(C_FLAGS) $< -c -o $@


$(OBJ_DIR)/%.o: $(UNIT_C_DIR)/%.c $(H_FILES) $(OBJ_DIR)
	$(CC) $(C_FLAGS) $(UNIT_FLAGS) -c $< -o $@

.PHONY: clean unit func

clean:
	$(RM) -r $(OBJ_DIR)/*.o *.exe $(OBJ_DIR)/*.gcda $(OBJ_DIR)/*.gcno $(OBJ_DIR)/report $(OBJ_DIR)/*.info $(C_DIR)/*.d ./out

unit: $(UNIT)
	./$^

%.d : %.c
	$(CC) -I$(H_DIR) -M $< > $@

include $(C_FILES:.c=.d)

debug: C_FLAGS += -ggdb
debug: app.exe

func: C_FLAGS += --coverage
func: clean $(APP)
	bash ./func_tests/scripts/func_tests.sh
	lcov -t "app" -o app.info -c -d .
	genhtml -o report app.info
	mv report $(OBJ_DIR)
	mv app.info $(OBJ_DIR)

release: $(APP)
