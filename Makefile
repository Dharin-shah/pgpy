# Makefile for pgpy

EXTENSION = pgpy
MODULE_big = pgpy
OBJS = src/pgpy.o  # Assuming your C source file is src/pgpy.c

# Point to the Python headers
PG_CFLAGS += -I/opt/homebrew/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/include/python3.11

PG_CONFIG ?= pg_config
PGXS := /opt/homebrew/opt/postgresql@15/lib/postgresql/pgxs/src/makefiles/pgxs.mk
include $(PGXS)
