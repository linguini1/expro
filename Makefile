ifeq ($(OS),Windows_NT)
OUT = poly.exe
else
OUT = poly
endif

CC = gcc

WARNINGS = -Wall -Wextra
CFLAGS += -O3

SRCDIR = $(abspath ./src)
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(OUT)

run: all
	@$(OUT)

%.o: %.c
	$(CC) $(CFLAGS) $(WARNINGS) -c $< -o $@

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT)

clean:
	@rm $(OBJS)
	@rm $(OUT)
