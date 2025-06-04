# main flag and macros for GCC compiler
CC			=		gcc
CFLAGS		=		-Wall -Werror -Wextra -std=c11 -pedantic
D_FLAGS		=		-g
R_FLAGS		=		-DNDEBUG -O2

# directory with `*.c` files and target dir for saving objects
SOURCE_DIR	=		./
BUILD_DIR	=		./build

# list of source ifles and objects
SOURCE		=		$(wildcard *.c)
OBJECTS		=		$(patsubst %.c, $(BUILD_DIR)/%.o, $(SOURCE))

# main target of Makefile
TARGET		=		s21_string.a

.PHONY: all debug release style-check format check run clean rebuild

all: style-format style-check $(TARGET) memory-check

$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o ../$@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

test:
	$(info Running testing...)

gcov_report:
	$(info Assemble test result into report...)

clean:
	$(info Clear the build folder...)
	@rm -rf $(BUILD_DIR) ../s21_release ../$(TARGET)

# usefull comand for code checking
style-format: $(SOURCE)
	$(info Formatting code with clang-format...)
	@clang-format -i --style="{BasedOnStyle: Google}" $(SOURCE_DIR)/*.c $(SOURCE_DIR)/*.h

style-check: $(SOURCE)
	$(info Checking style with clang-format...)
	@clang-format -n --style="{BasedOnStyle: Google}" $(SOURCE_DIR)/*.c $(SOURCE_DIR)/*.h
	$(info Running cppcheck...)
	@cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCE)

memory-check: $(TARGET)
	$(info Running valgrind...)
	@valgrind --tool=memcheck --leak-check=yes --track-origins=yes ../$(TARGET)

# debug and release versions
s21_release: $(SOURCE)
	$(info Build release version...)
	@$(CC) $(R_FLAGS) $^ -o ../$@

gdb: clean $(SOURCE)
	$(info Build debug version...)

rebuild: clean all
