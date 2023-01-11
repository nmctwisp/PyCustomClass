#pragma once
#include "Python.h"
#include "structmember.h"

typedef struct {
    PyObject_HEAD
    PyObject* first; /* first name */
    PyObject* last;  /* last name */
    int number;
} Custom2Object;

static void Custom2_dealloc(Custom2Object* self) {

    Py_XDECREF(self->first);
    Py_XDECREF(self->last);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* Custom2_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {

    Custom2Object* self;
    self = (Custom2Object*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->first = PyUnicode_FromString("");
        if (self->first == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->last = PyUnicode_FromString("");
        if (self->last == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->number = 0;
    }
    return (PyObject*)self;
}

static int Custom2_init(Custom2Object* self, PyObject* args, PyObject* kwds) {
    static const char* kwlist[] = { "first", "last", "number", NULL };
    PyObject* first = NULL, * last = NULL, * tmp;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", (char**)kwlist,
        &first, &last,
        &self->number))
        return -1;

    if (first) {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_XDECREF(tmp);
    }
    if (last) {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_XDECREF(tmp);
    }
    return 0;
}

static PyMemberDef Custom2_members[] = {
    {"first", T_OBJECT_EX, offsetof(Custom2Object, first), 0,
     "first name"},
    {"last", T_OBJECT_EX, offsetof(Custom2Object, last), 0,
     "last name"},
    {"number", T_INT, offsetof(Custom2Object, number), 0,
     "custom number"},
    {NULL}  /* Sentinel */
};

static PyObject* Custom2_name(Custom2Object* self, PyObject* Py_UNUSED(ignored)) {

    if (self->first == NULL) {
        PyErr_SetString(PyExc_AttributeError, "first");
        return NULL;
    }
    if (self->last == NULL) {
        PyErr_SetString(PyExc_AttributeError, "last");
        return NULL;
    }
    return PyUnicode_FromFormat("%S %S", self->first, self->last);
}

static PyMethodDef Custom2_methods[] = {
    {"name", (PyCFunction)Custom2_name, METH_NOARGS,
     "Return the name, combining the first and last name"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject Custom2Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)

    .tp_name = "custom.Custom2",
    .tp_basicsize = sizeof(Custom2Object),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)Custom2_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = PyDoc_STR("Custom2 objects"),
    .tp_methods = Custom2_methods,
    .tp_members = Custom2_members,
    .tp_init = (initproc)Custom2_init,
    .tp_new = Custom2_new,
};
