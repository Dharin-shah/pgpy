// pgpy.c
#include "postgres.h"
#include "fmgr.h"
#include "executor/spi.h"  // for SPI functions
#include <Python.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(fetch_and_process);

Datum
fetch_and_process(PG_FUNCTION_ARGS)
{
    char *result;
    int ret;
    char *query = "SELECT column_name FROM your_table LIMIT 10";  // Modify this query as needed

    // Initialize SPI (Server Programming Interface) to run SQL commands
    SPI_connect();

    ret = SPI_exec(query, 0);  // 0 means unlimited row count
    if (ret != SPI_OK_SELECT)
        elog(ERROR, "Failed to execute SQL query");

    // For simplicity, let's just fetch the first row, first column value
    if (SPI_processed > 0)
    {
        bool isnull;
        Datum datum = SPI_getbinval(SPI_tuptable->vals[0], SPI_tuptable->tupdesc, 1, &isnull);
        if (!isnull)
            result = SPI_getvalue(SPI_tuptable->vals[0], SPI_tuptable->tupdesc, 1);
    }

    SPI_finish();

    // TODO: Pass the fetched data to a Python function and process it

    // For now, let's just return the fetched value
    PG_RETURN_TEXT_P(cstring_to_text(result));
}
