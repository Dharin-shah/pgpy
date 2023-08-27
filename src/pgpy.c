// pgpy.c
#include "postgres.h"
#include "fmgr.h"
#include "executor/spi.h"  // for SPI functions
#include <Python.h>
#include "utils/builtins.h"


PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(fetch_and_process);
// Declare a new function for the Python call
PG_FUNCTION_INFO_V1(pgpy_hello);

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

// ... [Your existing includes]



Datum
pgpy_hello(PG_FUNCTION_ARGS)
{
    elog(NOTICE, "Starting pgpy_hello function");

    // Construct the path to the Python script
    char *dataDir = GetConfigOption("data_directory", false, false);
    char scriptPath[MAXPGPATH];
    snprintf(scriptPath, sizeof(scriptPath), "%s/extension/pgpy/scripts/pgpy_script.py", dataDir);

    // Add the script directory to the Python path
    PyRun_SimpleString("import sys");
    char pythonPathCmd[MAXPGPATH + 50];
    snprintf(pythonPathCmd, sizeof(pythonPathCmd), "sys.path.append('%s/extension/pgpy/scripts')", dataDir);
    PyRun_SimpleString(pythonPathCmd);

    elog(NOTICE, "Initializing Python");
    Py_Initialize();
    elog(NOTICE, "Python initialized");

    PyObject *pName, *pModule, *pFunc;
    PyObject *pValue;

    pName = PyUnicode_DecodeFSDefault("pgpy_script");
    elog(NOTICE, "Init python script COMPLETE");
    pModule = PyImport_Import(pName);
    elog(NOTICE, "Importing python script COMPLETE");
    Py_DECREF(pName);
    elog(NOTICE, "Dereferencing pName Complete");

    char *result = NULL;

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "hello_world");
        elog(NOTICE, "Function initialisation Complete");
        if (PyCallable_Check(pFunc)) {
            pValue = PyObject_CallObject(pFunc, NULL);
            elog(NOTICE, "Function Call Complete");
            if (pValue != NULL) {
                result = PyUnicode_AsUTF8(pValue);
                Py_DECREF(pValue);
            }
        } else {
            PyErr_Print();
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        elog(NOTICE, "pModule not found");
        PyErr_Print();
    }

    Py_Finalize();

    elog(NOTICE, "Ending pgpy_hello function");
    PG_RETURN_TEXT_P(cstring_to_text("Hello from pgpy_hello!"));
}