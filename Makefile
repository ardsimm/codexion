# ========== FLAGS ==========
CFLAGS = -Wall -Wextra -Werror

# ========== PROGRAM ARGUMENTS ==========

# ---------- MARKERS ----------
NUMBER_OF_CODERS_MARKER =				--number_of_coders
TIME_TO_BURNOUT_MARKER =				--time_to_burnout
TIME_TO_COMPILE_MARKER =				--time_to_compile
TIME_TO_DEBUG_MARKER =					--time_to_debug
TIME_TO_REFACTOR_MARKER =				--time_to_refactor
NUMBER_OF_COMPILES_REQUIRED_MARKER =	--number_of_compiles_required
DONGLE_COOLDOWN_MARKER =				--dongle_cooldown
SCHEDULER_MARKER =						--scheduler

# ---------- VALUES ----------
NUMBER_OF_CODERS_VALUE =			42
TIME_TO_BURNOUT_VALUE =				240
TIME_TO_COMPILE_VALUE =				30
TIME_TO_DEBUG_VALUE =				30
TIME_TO_REFACTOR_VALUE =			30
NUMBER_OF_COMPILES_REQUIRED_VALUE =	12
DONGLE_COOLDOWN_VALUE =				60
SCHEDULER_VALUE =					FIFO

# ---------- FULL ARGUMENTS ----------
NUMBER_OF_CODERS =				$(NUMBER_OF_CODERS_MARKER) $(NUMBER_OF_CODERS_VALUE)
TIME_TO_BURNOUT =				$(TIME_TO_BURNOUT_MARKER) $(TIME_TO_BURNOUT_VALUE)
TIME_TO_COMPILE =				$(TIME_TO_COMPILE_MARKER) $(TIME_TO_COMPILE_VALUE)
TIME_TO_DEBUG =					$(TIME_TO_DEBUG_MARKER) $(TIME_TO_DEBUG_VALUE)
TIME_TO_REFACTOR =				$(TIME_TO_REFACTOR_MARKER) $(TIME_TO_REFACTOR_VALUE)
NUMBER_OF_COMPILES_REQUIRED =	$(NUMBER_OF_COMPILES_REQUIRED_MARKER) $(NUMBER_OF_COMPILES_REQUIRED_VALUE)
DONGLE_COOLDOWN =				$(DONGLE_COOLDOWN_MARKER) $(DONGLE_COOLDOWN_VALUE)
SCHEDULER =						$(SCHEDULER_MARKER) $(SCHEDULER_VALUE)

# ---------- COMBINED ARGUMENTS ----------
ARGUMENTS =	$(NUMBER_OF_CODERS) \
			$(TIME_TO_BURNOUT) \
			$(TIME_TO_COMPILE) \
			$(TIME_TO_DEBUG) \
			$(TIME_TO_REFACTOR) \
			$(NUMBER_OF_COMPILES_REQUIRED) \
			$(DONGLE_COOLDOWN) \
			$(SCHEDULER)

# ========== DIRECTORIES ==========

# ---------- MAIN ----------

MAIN_DIR = src

PARSE_DIR = parse

# ---------- HEADERS ----------

HEADERS_DIR = headers

# ========== INCLUDES ==========

INCLUDES =	-I$(MAIN_DIR)/$(HEADERS_DIR)

# ========== FILES ==========

# ---------- MAIN ----------

MAIN_FILES =	$(MAIN_DIR)/main.c \
				$(MAIN_DIR)/heap_queue.c \
				$(MAIN_DIR)/logging.c \
				$(MAIN_DIR)/routine.c \
				$(MAIN_DIR)/simulation.c \
				$(MAIN_DIR)/utils.c \
				$(MAIN_DIR)/$(PARSE_DIR)/parse.c \
				$(MAIN_DIR)/$(PARSE_DIR)/parse_validate.c \
				$(MAIN_DIR)/$(PARSE_DIR)/parse_free.c \

ALL_FILES =				$(MAIN_FILES)

# ========== OBJ ==========

SRCS_OBJ = $(MAIN_FILES:.c=.o)

ALL_OBJ = $(SRCS_OBJ)

# ========== DFILES ==========

DFILES = $(ALL_OBJ:.o=.d)

# ========== NAMES ==========

NAME_MAIN = codexion

# ========== PROGRESS TRACKING ==========

TOTAL_FILES := $(words $(ALL_FILES))

# Counter file to track progress across make invocations
COUNTER_FILE := .compile_counter

# ========== RULES ==========

run: $(NAME_MAIN)
	./codexion $(ARGUMENTS)

all: reset_counter $(NAME_MAIN)

$(NAME_MAIN): $(SRCS_OBJ)
	@echo "\033[1;32m[LINKING]\033[0m $@"
	@$(CC) $(CFLAGS) $(SRCS_OBJ) -o $@
	@echo "\033[1;32m[SUCCESS]\033[0m $(NAME_MAIN) compiled successfully!"
	@rm -f $(COUNTER_FILE)

reset_counter:
	@echo "0" > $(COUNTER_FILE)
	@echo "$(TOTAL_FILES)" >> $(COUNTER_FILE)

# ========================================
#           COMMON RULES
# ========================================

# ########## IMPLICIT RULES ##########

# Rule for mandatory files
$(MAIN_DIR)/%.o: $(MAIN_DIR)/%.c
	@COMPILED=$$(head -n 1 $(COUNTER_FILE) 2>/dev/null || echo "0"); \
	TOTAL=$$(tail -n 1 $(COUNTER_FILE) 2>/dev/null || echo "$(TOTAL_FILES)"); \
	COMPILED=$$((COMPILED + 1)); \
	PERCENT=$$((COMPILED * 100 / TOTAL)); \
	printf "\033[1;36m[%3d%%]\033[0m %s\n" $$PERCENT $<; \
	echo "$$COMPILED" > $(COUNTER_FILE); \
	echo "$$TOTAL" >> $(COUNTER_FILE)
	@$(CC) $(CFLAGS) -MMD -c $< -o $@ $(INCLUDES)

# ---------- CLEAN ----------

clean:
	@echo "\033[1;31m[CLEAN]\033[0m Removing object files and dependencies..."
	@rm -rf $(DFILES) $(ALL_OBJ)
	@rm -f $(COUNTER_FILE)
	@echo "\033[1;32m[DONE]\033[0m Clean completed!"

fclean: clean
	@echo "\033[1;31m[FCLEAN]\033[0m Removing executables..."
	@rm -rf $(NAME_MAIN)
	@echo "\033[1;32m[DONE]\033[0m Full clean completed!"

# ---------- re ----------

re: fclean all

.PHONY: all clean fclean re reset_counter run

-include $(DFILES)
