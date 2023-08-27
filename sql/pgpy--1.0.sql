
-- pgpy--1.0.sql

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pgpy" to load this file. \quit


CREATE FUNCTION fetch_and_process() RETURNS text
    AS '$libdir/pgpy', 'fetch_and_process'
    LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION pgpy_hello()
    RETURNS text AS 'MODULE_PATHNAME', 'pgpy_hello'
    LANGUAGE C STRICT;