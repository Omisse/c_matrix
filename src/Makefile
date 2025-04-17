#with targets all, clean, test, matrix.a, gcov_report

TARGET := matrix.a
TEST := test

SRCDIR := core
HDIR := core
OBJDIR := objects

SOURCES := $(wildcard $(SRCDIR)/*.c)
HEADERS := $(wildcard $(HDIR)/*.h) matrix.h
OBJECTS := $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(patsubst %.c,%.o,$(SOURCES)))

TSRCDIR := tests/sources
THDIR := tests/headers

TESTS_SOURCES := $(wildcard $(TSRCDIR)/*.c)
TESTS_HEADERS := $(wildcard $(THDIR)/*.h)
TESTS_OBJECTS := $(patsubst $(TSRCDIR)%,$(OBJDIR)%,$(patsubst %.c,%.o,$(TESTS_SOURCES)))

CC := gcc
CCFLAGS := -Wall -Werror -Wextra -std=c11
CCFLAGS_COMMON := -Wall -Werror -Wextra -std=c11
CCFLAGS_GCOV := --coverage

LINK := -lcheck -lm

RUN := ./
RUN_VG := CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./
ifneq ($(findstring subunit,$(shell ld -lsubunit 2>&1)), subunit)
	LINK += -lsubunit
endif

all: gcov_report
	@ make $(TEST)

clean:
	@ echo Removing all that we were building for so long...
	@ rm -rf $(OBJDIR)
	@ rm -rf $(TARGET)
	@ rm -rf $(TEST)
	@ rm -rf gcov
	@ rm -rf coverage.info

	@ echo All built files commited sudoku.

$(TARGET): $(OBJECTS)
	@ echo Building $@
	@ ar rcs $@ $(OBJECTS)
	
$(TEST): $(TARGET) $(TESTS_OBJECTS)
	@ echo Building $@
	@ $(CC) $(CCFLAGS) $(TESTS_OBJECTS) -o $@ $< $(LINK)
	@ echo Running tests...
	@ $(RUN)$@	

.report: $(TEST) $(OBJDIR)
	@ lcov -t "unit-tests lib coverage" -o coverage.info -c -d $(OBJDIR)
	@ genhtml -o gcov coverage.info

gcov_report: CCFLAGS=$(CCFLAGS_COMMON) $(CCFLAGS_GCOV)

gcov_report: .report

valgrind: RUN=$(RUN_VG)

valgrind: $(TEST)


$(OBJDIR)/%.o: $(SRCDIR)/%.c .FORCE
	@ mkdir -p $(OBJDIR)
	@ $(CC) $(CCFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TSRCDIR)/%.c .FORCE
	@ mkdir -p $(OBJDIR)
	@ $(CC) $(CCFLAGS) -c $< -o $@


format-all: $(SOURCES) $(TESTS_SOURCES) $(HEADERS) $(TESTS_HEADERS)
	@ echo Starting format...
	@ clang-format --style=file:../materials/linters/.clang-format -n $^
	@ clang-format --style=file:../materials/linters/.clang-format -i $^
	@ echo Formatting done.

lsubstatus:
	@ echo $(LINK)

tellme:
	@ echo $(OBJECTS)

.FORCE:
	@ echo Force-rebuilding...

.PHONY: clean all format-all lsubstatus .report gcov_report .FORCE tellme
