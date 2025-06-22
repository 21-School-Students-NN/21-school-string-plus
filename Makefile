# =============================================================================
# Compiler Configuration
# =============================================================================
CC				=		gcc
CFLAGS			=		-Wall -Werror -Wextra -std=c11 -pedantic
TST_FLAG		:=		$(shell pkg-config --cflags --libs check)
COV_FLAGS		=		-fprofile-arcs -ftest-coverage
DBG_FLAGS		=		-g
REL_FLAG		=		-DNDEBUG -O2

# =============================================================================
# Build Mode Configuration
# =============================================================================
ifeq ($(COVERAGE),1)
    CFLAGS += $(COV_FLAGS)
endif

ifeq ($(RELEASE),1)
    CFLAGS += $(REL_FLAG)
endif

ifeq ($(DEBUG),1)
    CFLAGS += $(DBG_FLAGS)
endif

# =============================================================================
# Platform-Specific Configuration
# =============================================================================
ifeq ($(shell uname),Darwin)
    OPENCMD = open
else
    OPENCMD = xdg-open
endif

# =============================================================================
# Directory Structure
# =============================================================================
HEADERS			=		./headers

LIB_SOURCE_DIR	=		./src
OBJ_BUILD_DIR	=		./build/obj

TST_SOURCE_DIR	=		./tests
TST_BUILD_DIR	=		./build/test

COV_REPORT_DIR	=		../coverage
COV_FRONT_DIR	=		../coverage/web

# =============================================================================
# Source and Object Files
# =============================================================================
LIB_SOURCE		=		$(wildcard $(LIB_SOURCE_DIR)/*.c)
LIB_OBJECTS		=		$(patsubst $(LIB_SOURCE_DIR)/%.c, $(OBJ_BUILD_DIR)/%.o, $(LIB_SOURCE))


TST_SOURCE		=		$(wildcard $(TST_SOURCE_DIR)/*.c)
TST_OBJECTS		=		$(patsubst $(TST_SOURCE_DIR)/%.c, $(TST_BUILD_DIR)/%.o, $(TST_SOURCE))

# =============================================================================
# Main Targets
# =============================================================================
LIBRARY			=		s21_string.a

.PHONY: all debug release style-format style-check test gcov_report clean rebuild gdb

# =============================================================================
# Build Rules
# =============================================================================
all: style-check test

$(LIBRARY): $(LIB_OBJECTS)
	$(info Assembling all together to static lib...)
	@ar rcs ../$@ $^
	@ranlib ../$@

$(OBJ_BUILD_DIR)/%.o: $(LIB_SOURCE_DIR)/%.c | $(OBJ_BUILD_DIR)
	$(info Building the $@ object file...)
	@$(CC) $(CFLAGS) -c $< -o $@

# =============================================================================
# Testing Rules
# =============================================================================
test: clean style-check $(TST_OBJECTS) $(LIBRARY)
	$(info Assembling tests...)
	@$(CC) $(CFLAGS) $(TST_OBJECTS) ../$(LIBRARY) $(TST_FLAG) -o ../$@
	$(info Runing tests with valgrind...)
	@CK_FORK=no valgrind --tool=memcheck --leak-check=full --track-origins=yes ../$@

%.test: clean style-check $(TST_OBJECTS) $(LIBRARY)
	$(info Assembling tests...)
	@$(CC) $(CFLAGS) $(TST_OBJECTS) ../$(LIBRARY) $(TST_FLAG) -o ../$@
	$(info Runing $*-test with valgrind...)
	@CK_RUN_SUITE="$*" CK_FORK=no valgrind --tool=memcheck --leak-check=full --track-origins=yes ../$@

$(TST_BUILD_DIR)/%.o: $(TST_SOURCE_DIR)/%.c | $(TST_BUILD_DIR)
	$(info Building the $@ object file...)
	@$(CC) $(CFLAGS) -c $< $(TST_FLAG) -o $@

gcov_report: clean
	$(info Generating coverage report...)
	@COVERAGE=1 $(MAKE) test
	@$(MAKE) $(COV_FRONT_DIR)
	@lcov --test-name "s21_string" --output-file $(COV_REPORT_DIR)/coverage.info --capture --directory $(OBJ_BUILD_DIR)
	@genhtml $(COV_REPORT_DIR)/coverage.info --dark-mode --output-directory $(COV_FRONT_DIR)
	@$(OPENCMD) $(COV_FRONT_DIR)/index.html || true

clean:
	$(info Cleaning the build artifacts...)
	@rm -rf ./build ../$(LIBRARY) ../test* ../*.test ../coverage

# =============================================================================
# Code Quality Rules
# =============================================================================
style-format: $(LIB_SOURCE) $(TST_SOURCE)
	$(info Formatting code with clang-format...)
	@clang-format -i --verbose --style="{BasedOnStyle: Google}" $(LIB_SOURCE) $(TST_SOURCE)

style-check: $(LIB_SOURCE) $(TST_SOURCE)
	$(info Checking style with clang-format...)
	@clang-format -n --style="{BasedOnStyle: Google}" $(LIB_SOURCE) $(TST_SOURCE)
	$(info Running cppcheck...)
	@cppcheck --enable=all --force --suppress=missingIncludeSystem $(LIB_SOURCE) $(TST_SOURCE)

# =============================================================================
# Build Mode Rules
# =============================================================================
release: clean
	$(info Building release version...)
	@RELEASE=1 $(MAKE) $(LIBRARY)

gdb: clean
	$(info Building debug version...)
	@DEBUG=1 $(MAKE) test
	$(info Running...)
	@CK_FORK=no gdb ../test

rebuild: clean all

# =============================================================================
# Directory creation
# =============================================================================
$(OBJ_BUILD_DIR):
	$(info Creating a directory for objective file...)
	@mkdir -p ./build $(OBJ_BUILD_DIR)

$(TST_BUILD_DIR):
	$(info Creating a directory for test-objective file...)
	@mkdir -p ./build $(TST_BUILD_DIR)

$(COV_FRONT_DIR):
	$(info Creating a direcory for coverage report...)
	@mkdir -p $(COV_REPORT_DIR) $(COV_FRONT_DIR)