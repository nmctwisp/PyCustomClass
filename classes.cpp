#pragma once
#include "classes.h"

typedef struct {
    PyObject_HEAD
        /* Type-specific fields go here. */
} CustomObject;

static PyTypeObject CustomType = {
    .ob_base = { _PyObject_EXTRA_INIT {1, 0}, 0},
    .tp_name = "custom.Custom",
    .tp_basicsize = sizeof(CustomObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = PyDoc_STR("Custom objects"),
    .tp_new = PyType_GenericNew,
};