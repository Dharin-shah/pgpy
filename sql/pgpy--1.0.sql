-- pgpy--1.0.sql
CREATE FUNCTION fetch_and_process() RETURNS text
    AS '$libdir/pgpy', 'fetch_and_process'
    LANGUAGE C STRICT;