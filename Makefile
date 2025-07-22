# =============================================================================
# Compiler Configuration
# =============================================================================
CC				::=		gcc
CFLAGS			::=		-Wall -Werror -Wextra -std=c11 -pedantic -I./headers -lm
TST_FLAG		::=		$(shell pkg-config --cflags --libs check)
COV_FLAGS		::=		-fprofile-arcs -ftest-coverage
DBG_FLAGS		::=		-g
REL_FLAG		::=		-DNDEBUG -O2

# =============================================================================
# Build Mode Configuration using MAKECMDGOALS
# =============================================================================
ifeq ($(MAKECMDGOALS),gcov_report)
    CFLAGS 		+= 		$(COV_FLAGS)
endif

ifeq ($(MAKECMDGOALS),release)
    CFLAGS 		+= 		$(REL_FLAG)
endif

ifeq ($(MAKECMDGOALS),gdb)
    CFLAGS 		+= 		$(DBG_FLAGS)
endif

# =============================================================================
# Platform-Specific Configuration
# =============================================================================
ifeq ($(shell uname),Darwin)
    OPENCMD ::= open
else ifneq ($(shell uname -r | grep -i microsoft),)
    ifneq ($(shell which wslview 2>/dev/null),)
        OPENCMD ::= wslview
    else
        OPENCMD ::= cmd.exe /c start
    endif
else
    OPENCMD ::= xdg-open
endif

# =============================================================================
# Directory Structure
# =============================================================================
HEADERS			::=		./headers

LIB_SOURCE_DIR	::=		./src
OBJ_BUILD_DIR	::=		./build/obj

TST_SOURCE_DIR	::=		./tests
TST_BUILD_DIR	::=		./build/test

COV_REPORT_DIR	::=		../coverage
COV_FRONT_DIR	::=		../coverage/web

STAMP			::=		./build/cflags.stamp

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
LIBRARY			::=		s21_string.a

.PHONY: all debug release style_format style_check gcov_report clean rebuild gdb help

# =============================================================================
# Flag Change Detection
# =============================================================================
FLAG_FILE 		::=		./build/cflags.current
LAST_CFLAGS 	::= 	$(shell cat $(FLAG_FILE) 2>/dev/null)

# Only proceed with rebuild if flags have changed or flag file doesn't exist
ifneq ($(CFLAGS),$(LAST_CFLAGS))
    .PHONY: FORCE
    FORCE:
    $(shell mkdir -p ./build && echo "$(CFLAGS)" > $(FLAG_FILE))
    $(info Compiler flags changed - forcing rebuild...)
    REBUILD 	::= 	FORCE
else
    REBUILD 	::=
endif

# =============================================================================
# All(general) and Help targets
# =============================================================================
all: style_check test

help:
	@printf "TARGETS:\n"
	@printf "\t%-20s %s\n" "all" "Build and run tests with style check"
	@printf "\t%-20s %s\n" "test" "Compile and run all tests"
	@printf "\t%-20s %s\n" "release" "Build optimized release version"
	@printf "\t%-20s %s\n" "gdb" "Build debug version and run with gdb"
	@printf "\t%-20s %s\n" "style_format" "Format code with clang-format"
	@printf "\t%-20s %s\n" "style_check" "Check code style and run cppcheck"
	@printf "\t%-20s %s\n" "gcov_report" "Generate coverage report"
	@printf "\t%-20s %s\n" "clean" "Remove all build artifacts"
	@printf "\t%-20s %s\n" "rebuild" "Clean and rebuild everything"
	@printf "\t%-20s %s\n" "help" "Show this help message"
	@printf "\n"
	@printf "DIRECTORIES:\n"
	@printf "\t%-20s %s\n" "$(COV_REPORT_DIR)" "directory with coverage info"
	@printf "\t%-20s %s\n" "$(COV_FRONT_DIR)" "directory with coverage static web-page"
	@printf "\t%-20s %s\n" "$(OBJ_BUILD_DIR)" "directory with object files"
	@printf "\t%-20s %s\n" "$(TST_BUILD_DIR)" "directory with test object files"
	@printf "\t%-20s %s\n" "$(HEADERS)" "directory with header files"

# =============================================================================
# Build Rules
# =============================================================================
$(LIBRARY): $(LIB_OBJECTS) $(REBUILD)
	$(info Assembling all together to static lib...)
	@ar rcs ../$@ $(LIB_OBJECTS)
	@ranlib ../$@

$(OBJ_BUILD_DIR)/%.o: $(LIB_SOURCE_DIR)/%.c $(FLAG_FILE) | $(OBJ_BUILD_DIR)
	$(info Building the $@ object file...)
	@$(CC) $(CFLAGS) -c $< -o $@

# =============================================================================
# Testing Rules
# =============================================================================
test: $(TST_OBJECTS) $(LIBRARY)
	$(info Compile tests and running with valgrind...)
	@$(CC) $(CFLAGS) $(TST_OBJECTS) ../$(LIBRARY) $(TST_FLAG) -o ../$@
	@CK_FORK=no valgrind --tool=memcheck --leak-check=full --track-origins=yes ../$@

$(TST_BUILD_DIR)/%.o: $(TST_SOURCE_DIR)/%.c $(FLAG_FILE) | $(TST_BUILD_DIR)
	$(info Building the $@ object file...)
	@$(CC) $(CFLAGS) -c $< $(TST_FLAG) -o $@


%.test: ../test
	$(info Runing $*-test with valgrind...)
	@CK_RUN_SUITE="$*" CK_FORK=no valgrind --tool=memcheck --leak-check=full --track-origins=yes ../test

# =============================================================================
# Assemble Coverage Data to Web-Page
# =============================================================================
gcov_report: $(COV_FRONT_DIR) test
	$(info Generating coverage report...)
	@lcov --test-name "s21_string" --output-file $(COV_REPORT_DIR)/coverage.info --capture --directory $(OBJ_BUILD_DIR)
	@genhtml $(COV_REPORT_DIR)/coverage.info --dark-mode --output-directory $(COV_FRONT_DIR)
	@$(OPENCMD) $(COV_FRONT_DIR)/index.html || true

# =============================================================================
# Code Quality Rules
# =============================================================================
style_format: $(LIB_SOURCE) $(TST_SOURCE)
	$(info Formatting code with clang-format...)
	@clang-format -i --verbose --style="{BasedOnStyle: Google}" ./*/*.[h,c]

style_check: $(LIB_SOURCE) $(TST_SOURCE)
	$(info Checking style with clang-format and cppcheck...)
	@clang-format -n --style="{BasedOnStyle: Google}" --Werror ./*/*.[h,c]
	@cppcheck --enable=all --force --suppress=missingIncludeSystem --check-level=exhaustive --error-exitcode=1 $(LIB_SOURCE) $(TST_SOURCE)
	@echo "Style check passed successfully!"

# =============================================================================
# Build Mode Rules
# =============================================================================
release: $(LIBRARY)
	$(info Release build completed.)

gdb: test
	$(info Running with gdb...)
	@CK_FORK=no gdb ../test

clean:
	$(info Cleaning the build artifacts...)
	@rm -rf $(OBJ_BUILD_DIR) $(TST_BUILD_DIR) ../$(LIBRARY) ../test* ../*.test ../coverage

rebuild: clean all

# =============================================================================
# Directory creation
# =============================================================================
$(OBJ_BUILD_DIR):
	$(info Creating a directory for objective file...)
	@mkdir -p $(OBJ_BUILD_DIR)

$(TST_BUILD_DIR):
	$(info Creating a directory for test-objective file...)
	@mkdir -p $(TST_BUILD_DIR)

$(COV_FRONT_DIR):
	$(info Creating a direcory for coverage report...)
	@mkdir -p $(COV_REPORT_DIR) $(COV_FRONT_DIR)
