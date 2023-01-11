#pragma once

#define PY_SSIZE_T_CLEAN

#include "Custom1.h"
#include "Custom2.h"
#include "Custom3.h"

static PyModuleDef custommodule = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "custom",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_custom(void) {
    PyObject* m;
    if (PyType_Ready(&Custom1Type) < 0)
        return NULL;

    if (PyType_Ready(&Custom2Type) < 0)
        return NULL;

    if (PyType_Ready(&Custom3Type) < 0)
        return NULL;

    m = PyModule_Create(&custommodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&Custom1Type);
    if (PyModule_AddObject(m, "Custom1", (PyObject*)&Custom1Type) < 0) {
        Py_DECREF(&Custom1Type);
        Py_DECREF(m);
        return NULL;
    }

    Py_INCREF(&Custom2Type);
    if (PyModule_AddObject(m, "Custom2", (PyObject*)&Custom2Type) < 0) {
        Py_DECREF(&Custom2Type);
        Py_DECREF(m);
        return NULL;
    }

    Py_INCREF(&Custom3Type);
    if (PyModule_AddObject(m, "Custom3", (PyObject*)&Custom3Type) < 0) {
        Py_DECREF(&Custom3Type);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}