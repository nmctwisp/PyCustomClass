#pragma once

#include <Python.h>
#include "structmember.h"

typedef struct {
    PyObject_HEAD
    PyObject* first; /* first name */
    PyObject* last;  /* last name */
    int number;
} Custom3Object;

static void Custom3_dealloc(Custom3Object* self) {
    Py_XDECREF(self->first);
    Py_XDECREF(self->last);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* Custom3_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    Custom3Object* self;
    self = (Custom3Object*)type->tp_alloc(type, 0);
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

static int Custom3_init(Custom3Object* self, PyObject* args, PyObject* kwds) {

    static const char* kwlist[] = { "first", "last", "number", NULL };
    PyObject* first = NULL, * last = NULL, * tmp;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|UUi", (char**)kwlist,
        &first, &last,
        &self->number))
        return -1;

    if (first) {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_DECREF(tmp);
    }
    if (last) {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_DECREF(tmp);
    }
    return 0;
}

static PyMemberDef Custom3_members[] = {
    {"number", T_INT, offsetof(Custom3Object, number), 0,
     "custom number"},
    {NULL}  /* Sentinel */
};

static PyObject* Custom3_getfirst(Custom3Object* self, void* closure) {
    Py_INCREF(self->first);
    return self->first;
}

static int Custom3_setfirst(Custom3Object* self, PyObject* value, void* closure) {
    
    PyObject* tmp;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the first attribute");
        return -1;
    }
    if (!PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
            "The first attribute value must be a string");
        return -1;
    }
    tmp = self->first;
    Py_INCREF(value);
    self->first = value;
    Py_DECREF(tmp);
    return 0;
}

static PyObject* Custom3_getlast(Custom3Object* self, void* closure) {

    Py_INCREF(self->last);
    return self->last;
}

static int Custom3_setlast(Custom3Object* self, PyObject* value, void* closure) {

    PyObject* tmp;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
        return -1;
    }
    if (!PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
            "The last attribute value must be a string");
        return -1;
    }
    tmp = self->last;
    Py_INCREF(value);
    self->last = value;
    Py_DECREF(tmp);
    return 0;
}

static PyGetSetDef Custom3_getsetters[] = {
    {"first", (getter)Custom3_getfirst, (setter)Custom3_setfirst,
     "first name", NULL},
    {"last", (getter)Custom3_getlast, (setter)Custom3_setlast,
     "last name", NULL},
    {NULL}  /* Sentinel */
};

static PyObject* Custom3_name(Custom3Object* self, PyObject* Py_UNUSED(ignored)) {
    return PyUnicode_FromFormat("%S %S", self->first, self->last);
}

static PyMethodDef Custom3_methods[] = {
    {"name", (PyCFunction)Custom3_name, METH_NOARGS,
     "Return the name, combining the first and last name"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject Custom3Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)

    .tp_name = "custom.Custom3",
    .tp_basicsize = sizeof(Custom3Object),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)Custom3_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = PyDoc_STR("Custom3 objects"),
    .tp_methods = Custom3_methods,
    .tp_members = Custom3_members,
    .tp_getset = Custom3_getsetters,
    .tp_init = (initproc)Custom3_init,
    .tp_new = Custom3_new,

};
