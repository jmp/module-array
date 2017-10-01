CC=gcc
CFLAGS=-I.. -ansi -pedantic -Wall -fprofile-arcs -ftest-coverage \
	-DWRAP_MALLOC -Wl,--wrap,malloc \
	-DWRAP_REALLOC -Wl,--wrap,realloc
SOURCES=test.c ../array.c
PRGNAME=test
TARGET=$(PRGNAME)
RM=rm -f

ifdef SystemRoot
	TARGET=$(PRGNAME).exe
	RM=del /Q /F
endif

$(TARGET):
	@$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	@$(RM) $(TARGET)
	@$(RM) *.gc*

.PHONY: clean
