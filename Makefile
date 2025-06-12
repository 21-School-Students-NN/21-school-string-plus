# main flag and macros for GCC compiler
CC				=		gcc
CFLAGS			=		-Wall -Werror -Wextra -std=c11 -pedantic
TST_FLAG		=		-lcheck -lsubunit -lm -lrt -lpthread
D_FLAGS			=		-g
R_FLAGS			=		-DNDEBUG -O2

# directory with `*.c` files and target dir for saving objects
HEADERS			=		./headers

LIB_SOURCE_DIR	=		./src
OBJ_BUILD_DIR	=		./build/obj

TST_SOURCE_DIR	=		./tests
TST_BUILD_DIR	=		./build/test


# list of source ifles and objects
LIB_SOURCE		=		$(wildcard $(LIB_SOURCE_DIR)/*.c)
LIB_OBJECTS		=		$(patsubst $(LIB_SOURCE_DIR)/%.c, $(OBJ_BUILD_DIR)/%.o, $(LIB_SOURCE))

# list of testing ifles and objects
TST_SOURCE		=		$(wildcard $(TST_SOURCE_DIR)/*.c)
TST_OBJECTS		=		$(patsubst $(TST_SOURCE_DIR)/%.c, $(TST_BUILD_DIR)/%.o, $(TST_SOURCE))

# main target of Makefile
LIBRARY			=		s21_string.a


.PHONY: all debug release style-check format check run clean rebuild

all: style-format style-check $(LIBRARY) memory-check

$(LIBRARY): $(LIB_OBJECTS)
	$(info Assembling all together to static lib...)
	ar rcs ../$@ $^
	ranlib ../$@

$(OBJ_BUILD_DIR)/%.o: $(LIB_SOURCE_DIR)/%.c | $(OBJ_BUILD_DIR)
	$(info Building the $@ object file...)
	@$(CC) $(CFLAGS) -c $< -o $@

test: $(TST_OBJECTS) ../$(LIBRARY)
	$(info Assembling and running tests...)
	$(CC) $(CFLAGS) $(TST_FLAG) $^ -o ../$@
	../$@

$(TST_BUILD_DIR)/%.o: $(TST_SOURCE_DIR)/%.c | $(TST_BUILD_DIR)
	$(info Building the $@ object file...)
	@$(CC) $(CFLAGS) $(TST_FLAG) -c $< -o $@

gcov_report:
	$(info Assembling test result into report...)

clean:
	$(info Cleaning the build artifacts...)
	@rm -rf ./build ../s21_release ../$(LIBRARY)

# usefull comand for code checking
style-format: $(LIB_SOURCE)
	$(info Formatting code with clang-format...)
	@clang-format -i --style="{BasedOnStyle: Google}" $(LIB_SOURCE) code-samples/*.c

style-check: $(LIB_SOURCE)
	$(info Checking style with clang-format...)
	@clang-format -n --style="{BasedOnStyle: Google}" $(LIB_SOURCE)
	$(info Running cppcheck...)
	@cppcheck --enable=all --suppress=missingIncludeSystem $(LIB_SOURCE)

memory-check: $(LIBRARY)
	$(info Running valgrind...)
	@valgrind --tool=memcheck --leak-check=yes --track-origins=yes ../$(LIBRARY)

# debug and release versions
s21_release: $(LIB_SOURCE)
	$(info Building release version...)
	@$(CC) $(CFLAGS) $(R_FLAGS) $^ -o ../$@

gdb: clean $(LIB_SOURCE)
	$(info Building debug version...)

rebuild: clean all

$(OBJ_BUILD_DIR):
	$(info Create a directory for objective file...)
	@mkdir -p ./build $(OBJ_BUILD_DIR)

$(TST_BUILD_DIR):
	$(info Create a directory for test-objective file...)
	@mkdir -p ./build $(TST_BUILD_DIR)