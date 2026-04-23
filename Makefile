CFLAGS = -Wall -Wextra -Werror

# ========== DIRECTORIES ==========

# ---------- MAIN ----------

MAIN_DIR = src

# ---------- HEADERS ----------

HEADERS_DIR = headers

# ========== INCLUDES ==========

INCLUDES = -I$(MAIN_DIR)/$(HEADERS_DIR)

# ========== FILES ==========

# ---------- MAIN ----------

MAIN_FILES =			$(MAIN_DIR)/main.c \
						$(MAIN_DIR)/heap_queue.c \
						$(MAIN_DIR)/logging.c \
						$(MAIN_DIR)/routine.c \
						$(MAIN_DIR)/simulation.c \
						$(MAIN_DIR)/utils.c \
						$(MAIN_DIR)/parse.c

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

.PHONY: all clean fclean re reset_counter

-include $(DFILES)
