# main flag and macros for GCC compiler
CC				=		gcc
CFLAGS			=		-Wall -Werror -Wextra -std=c11 -pedantic
TST_FLAG		:=		$(shell pkg-config --cflags --libs check)
COV_FLAGS		=		-fprofile-arcs -ftest-coverage
DBG_FLAGS		=		-g
REL_FLAG		=		-DNDEBUG -O2

# Add coverage flags if COVERAGE=1
ifeq ($(COVERAGE),1)
    CFLAGS += $(COV_FLAGS)
endif

ifeq ($(RELEASE),1)
    CFLAGS += $(REL_FLAG)
endif

ifeq ($(DEBUG),1)
    CFLAGS += $(DBG_FLAGS)
endif

ifeq ($(shell uname),Darwin)
    OPENCMD = open
else
    OPENCMD = xdg-open
endif

# directory with `*.c` files and target dir for saving objects
HEADERS			=		./headers

LIB_SOURCE_DIR	=		./src
OBJ_BUILD_DIR	=		./build/obj

TST_SOURCE_DIR	=		./tests
TST_BUILD_DIR	=		./build/test

COV_REPORT_DIR	=		../coverage
COV_FRONT_DIR	=		../coverage/web

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
	@ar rcs ../$@ $^
	@ranlib ../$@

$(OBJ_BUILD_DIR)/%.o: $(LIB_SOURCE_DIR)/%.c | $(OBJ_BUILD_DIR)
	$(info Building the $@ object file...)
	@$(CC) $(CFLAGS) -c $< -o $@

test: clean $(TST_OBJECTS) $(LIBRARY)
	$(info Assembling tests...)
	@$(CC) $(CFLAGS) $(TST_FLAG) $(TST_OBJECTS) ../$(LIBRARY) -o ../$@
	$(info Runing tests with valgrind...)
	@CK_FORK=no valgrind --tool=memcheck --leak-check=full ../$@ 2>>../test.log

%.test: clean $(TST_OBJECTS) $(LIBRARY)
	$(info Assembling tests...)
	@$(CC) $(CFLAGS) $(TST_FLAG) $(TST_OBJECTS) ../$(LIBRARY) -o ../$@
	$(info Runing $*-test with valgrind...)
	@CK_RUN_SUITE="$*" CK_FORK=no valgrind --tool=memcheck --leak-check=full ../$@ 2>>../$*.log

$(TST_BUILD_DIR)/%.o: $(TST_SOURCE_DIR)/%.c | $(TST_BUILD_DIR)
	$(info Building the $@ object file...)
	@$(CC) $(CFLAGS) $(TST_FLAG) -c $< -o $@

gcov_report: clean
	$(info Generating coverage report...)
	@COVERAGE=1 $(MAKE) test
	@mkdir -p $(COV_REPORT_DIR) $(COV_FRONT_DIR)
	@lcov --test-name "s21_string" --output-file $(COV_REPORT_DIR)/coverage.info --capture --directory $(OBJ_BUILD_DIR)
	@genhtml $(COV_REPORT_DIR)/coverage.info --dark-mode --output-directory $(COV_FRONT_DIR)
	@$(OPENCMD) $(COV_FRONT_DIR)/index.html || true

clean:
	$(info Cleaning the build artifacts...)
	@rm -rf ./build ../$(LIBRARY) ../test* ../*.test ../coverage

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
release: clean
	$(info Building release version...)
	@RELEASE=1 $(MAKE) $(LIBRARY)

gdb: clean
	$(info Building debug version...)
	@DEBUG=1 $(MAKE) test
	@gdb ../test

rebuild: clean all

$(OBJ_BUILD_DIR):
	$(info Create a directory for objective file...)
	@mkdir -p ./build $(OBJ_BUILD_DIR)

$(TST_BUILD_DIR):
	$(info Create a directory for test-objective file...)
	@mkdir -p ./build $(TST_BUILD_DIR)