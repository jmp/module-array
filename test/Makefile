CC=gcc
TARGET=test
CFLAGS=-I.. -ansi -pedantic -Wall -Werror -Wextra \
	-DWRAP_MALLOC -Wl,--wrap,malloc \
	-DWRAP_REALLOC -Wl,--wrap,realloc
SOURCES=test.c ../array.c

ifdef ComSpec
	# Windows systems
	TARGET := $(TARGET).exe
	rm = $(wordlist 2,65535,$(foreach FILE,$(subst /,\,$(1)),& del $(FILE) > nul 2>&1)) || (exit 0)
else
	# Unix-like systems
	rm = rm $(1) > /dev/null 2>&1 || true
endif

# For generating coverage reports with gcov
ifdef COVERAGE
	CFLAGS := $(CFLAGS) -fprofile-arcs -ftest-coverage
endif

$(TARGET):
	@$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	@$(call rm,$(TARGET))
	@$(call rm,*.gc*)

.PHONY: clean
