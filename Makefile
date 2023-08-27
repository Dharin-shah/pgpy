# Makefile for pgpy

EXTENSION = pgpy
EXTVERSION=1.0
MODULE_big = pgpy
OBJS = src/pgpy.o  # Assuming your C source file is src/pgpy.c

# Point to the Python headers
PG_CFLAGS += -I/opt/homebrew/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/include/python3.11
SHLIB_LINK = -L/opt/homebrew/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/lib -lpython3.11

PG_CONFIG ?= pg_config
PGXS := /opt/homebrew/opt/postgresql@15/lib/postgresql/pgxs/src/makefiles/pgxs.mk
include $(PGXS)

DATA = sql/$(EXTENSION)--$(EXTVERSION).sql

# Add the Python script to the DATA variable so it gets installed
DATA += scripts/pgpy_script.py

all: sql/$(EXTENSION)--$(EXTVERSION).sql

sql/$(EXTENSION)--$(EXTVERSION).sql: sql/$(EXTENSION).sql
	cp $< $@

EXTRA_CLEAN = sql/$(EXTENSION)--$(EXTVERSION).sql
