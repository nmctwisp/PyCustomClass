#pragma once
#include "Python.h"

typedef struct {
    PyObject_HEAD
        /* Type-specific fields go here. */
} Custom1Object;

static PyTypeObject Custom1Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)

    .tp_name = "custom.Custom1",
    .tp_basicsize = sizeof(Custom1Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = PyDoc_STR("Custom1 objects"),
    .tp_new = PyType_GenericNew,
};
