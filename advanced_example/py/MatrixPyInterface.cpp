#include <Python.h>
#include "Matrix.hpp"
#include <iostream>

extern "C" {

static PyObject* LUFactorization(PyObject* self, PyObject* args) {
    PyObject *listOfLists;
    Py_ssize_t listLen;
    Py_ssize_t xLen;
    int m, n;

    if (!PyArg_ParseTuple(args, "Oii", &listOfLists, &m, &n))
        return NULL;

    if (!PyList_CheckExact(listOfLists)) {
        PyErr_SetString(PyExc_RuntimeError, "Received non-list type object.");
        return NULL;
    }
    Matrix A(m,n);

    listLen = PyList_GET_SIZE(listOfLists);
    for (Py_ssize_t i = 0; i < listLen; ++i) {
        PyObject *listInList = PyList_GET_ITEM(listOfLists, i);

        if (!PyList_CheckExact(listInList)) {
            PyErr_SetString(PyExc_RuntimeError, "Non-list type found in list of lists.");
            return NULL;
        }

        xLen = PyList_GET_SIZE(listInList);
        for (Py_ssize_t j = 0; j < xLen; ++j){
            PyObject *item = PyList_GET_ITEM(listInList, j);
            if (!PyFloat_Check(item)) {
                PyErr_SetString(PyExc_RuntimeError, "Non-float type found in list.");
                return NULL;
            }
            A(i,j) = PyFloat_AsDouble(item);
        }

    }

    auto [L, U] = A.LUFactorization();

    // output L and U
    // Convert L and U to Python lists of lists
    PyObject* pyL = PyList_New(L.Rows());
    for (size_t i = 0; i < L.Rows(); ++i) {
        PyObject* row = PyList_New(L.Cols());
        for (size_t j = 0; j < L.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(L(i, j)));
        }
        PyList_SET_ITEM(pyL, i, row);
    }

    PyObject* pyU = PyList_New(U.Rows());
    for (size_t i = 0; i < U.Rows(); ++i) {
        PyObject* row = PyList_New(U.Cols());
        for (size_t j = 0; j < U.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(U(i, j)));
        }
        PyList_SET_ITEM(pyU, i, row);
    }

    // Return L and U as a tuple
    PyObject* result = PyTuple_New(2);
    PyTuple_SET_ITEM(result, 0, pyL);
    PyTuple_SET_ITEM(result, 1, pyU);

    return result;
}

static PyObject* LUPFactorization(PyObject* self, PyObject* args) {
    PyObject *listOfLists;
    Py_ssize_t listLen;
    Py_ssize_t xLen;
    int m, n;

    if (!PyArg_ParseTuple(args, "Oii", &listOfLists, &m, &n))
        return NULL;

    if (!PyList_CheckExact(listOfLists)) {
        PyErr_SetString(PyExc_RuntimeError, "Received non-list type object.");
        return NULL;
    }
    Matrix A(m,n);

    listLen = PyList_GET_SIZE(listOfLists);
    for (Py_ssize_t i = 0; i < listLen; ++i) {
        PyObject *listInList = PyList_GET_ITEM(listOfLists, i);

        if (!PyList_CheckExact(listInList)) {
            PyErr_SetString(PyExc_RuntimeError, "Non-list type found in list of lists.");
            return NULL;
        }

        xLen = PyList_GET_SIZE(listInList);
        for (Py_ssize_t j = 0; j < xLen; ++j){
            PyObject *item = PyList_GET_ITEM(listInList, j);
            if (!PyFloat_Check(item)) {
                PyErr_SetString(PyExc_RuntimeError, "Non-float type found in list.");
                return NULL;
            }
            A(i,j) = PyFloat_AsDouble(item);
        }

    }

    auto [L,U,P] = A.LUPFactorization();

    // Convert L, U and P to Python lists of lists
    PyObject* pyL = PyList_New(L.Rows());
    for (size_t i = 0; i < L.Rows(); ++i) {
        PyObject* row = PyList_New(L.Cols());
        for (size_t j = 0; j < L.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(L(i, j)));
        }
        PyList_SET_ITEM(pyL, i, row);
    }

    PyObject* pyU = PyList_New(U.Rows());
    for (size_t i = 0; i < U.Rows(); ++i) {
        PyObject* row = PyList_New(U.Cols());
        for (size_t j = 0; j < U.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(U(i, j)));
        }
        PyList_SET_ITEM(pyU, i, row);
    }

    PyObject* pyP = PyList_New(P.Rows());
    for (size_t i = 0; i < P.Rows(); ++i) {
        PyObject* row = PyList_New(P.Cols());
        for (size_t j = 0; j < P.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(P(i, j)));
        }
        PyList_SET_ITEM(pyP, i, row);
    }

    // Return L and U as a tuple
    PyObject* result = PyTuple_New(3);
    PyTuple_SET_ITEM(result, 0, pyL);
    PyTuple_SET_ITEM(result, 1, pyU);
    PyTuple_SET_ITEM(result, 2, pyP);

    return result;
}

static PyObject* LUPFactorization_Parallel(PyObject* self, PyObject* args) {
    PyObject *listOfLists;
    Py_ssize_t listLen;
    Py_ssize_t xLen;
    int m, n;

    if (!PyArg_ParseTuple(args, "Oii", &listOfLists, &m, &n))
        return NULL;

    if (!PyList_CheckExact(listOfLists)) {
        PyErr_SetString(PyExc_RuntimeError, "Received non-list type object.");
        return NULL;
    }
    Matrix A(m,n);

    listLen = PyList_GET_SIZE(listOfLists);
    for (Py_ssize_t i = 0; i < listLen; ++i) {
        PyObject *listInList = PyList_GET_ITEM(listOfLists, i);

        if (!PyList_CheckExact(listInList)) {
            PyErr_SetString(PyExc_RuntimeError, "Non-list type found in list of lists.");
            return NULL;
        }

        xLen = PyList_GET_SIZE(listInList);
        for (Py_ssize_t j = 0; j < xLen; ++j){
            PyObject *item = PyList_GET_ITEM(listInList, j);
            if (!PyFloat_Check(item)) {
                PyErr_SetString(PyExc_RuntimeError, "Non-float type found in list.");
                return NULL;
            }
            A(i,j) = PyFloat_AsDouble(item);
        }

    }

    auto [L,U,P] = A.LUPFactorization_Parallel();

    // Convert L, U and P to Python lists of lists
    PyObject* pyL = PyList_New(L.Rows());
    for (size_t i = 0; i < L.Rows(); ++i) {
        PyObject* row = PyList_New(L.Cols());
        for (size_t j = 0; j < L.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(L(i, j)));
        }
        PyList_SET_ITEM(pyL, i, row);
    }

    PyObject* pyU = PyList_New(U.Rows());
    for (size_t i = 0; i < U.Rows(); ++i) {
        PyObject* row = PyList_New(U.Cols());
        for (size_t j = 0; j < U.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(U(i, j)));
        }
        PyList_SET_ITEM(pyU, i, row);
    }

    PyObject* pyP = PyList_New(P.Rows());
    for (size_t i = 0; i < P.Rows(); ++i) {
        PyObject* row = PyList_New(P.Cols());
        for (size_t j = 0; j < P.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(P(i, j)));
        }
        PyList_SET_ITEM(pyP, i, row);
    }

    // Return L and U as a tuple
    PyObject* result = PyTuple_New(3);
    PyTuple_SET_ITEM(result, 0, pyL);
    PyTuple_SET_ITEM(result, 1, pyU);
    PyTuple_SET_ITEM(result, 2, pyP);

    return result;
}

static PyObject* QRFactorization(PyObject* self, PyObject* args) {
    PyObject *listOfLists;
    Py_ssize_t listLen;
    Py_ssize_t xLen;
    int m, n;

    if (!PyArg_ParseTuple(args, "Oii", &listOfLists, &m, &n))
        return NULL;

    if (!PyList_CheckExact(listOfLists)) {
        PyErr_SetString(PyExc_RuntimeError, "Received non-list type object.");
        return NULL;
    }
    Matrix A(m,n);

    listLen = PyList_GET_SIZE(listOfLists);
    for (Py_ssize_t i = 0; i < listLen; ++i) {
        PyObject *listInList = PyList_GET_ITEM(listOfLists, i);

        if (!PyList_CheckExact(listInList)) {
            PyErr_SetString(PyExc_RuntimeError, "Non-list type found in list of lists.");
            return NULL;
        }

        xLen = PyList_GET_SIZE(listInList);
        for (Py_ssize_t j = 0; j < xLen; ++j){
            PyObject *item = PyList_GET_ITEM(listInList, j);
            if (!PyFloat_Check(item)) {
                PyErr_SetString(PyExc_RuntimeError, "Non-float type found in list.");
                return NULL;
            }
            A(i,j) = PyFloat_AsDouble(item);
        }

    }

    auto [Q, R] = A.QRFactorization();

    // Convert Q and R to Python lists of lists
    PyObject* pyQ = PyList_New(Q.Rows());
    for (size_t i = 0; i < Q.Rows(); ++i) {
        PyObject* row = PyList_New(Q.Cols());
        for (size_t j = 0; j < Q.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(Q(i, j)));
        }
        PyList_SET_ITEM(pyQ, i, row);
    }

    PyObject* pyR = PyList_New(R.Rows());
    for (size_t i = 0; i < R.Rows(); ++i) {
        PyObject* row = PyList_New(R.Cols());
        for (size_t j = 0; j < R.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(R(i, j)));
        }
        PyList_SET_ITEM(pyR, i, row);
    }

    // Return Q and R as a tuple
    PyObject* result = PyTuple_New(2);
    PyTuple_SET_ITEM(result, 0, pyQ);
    PyTuple_SET_ITEM(result, 1, pyR);

    return result;
}

static PyObject* QRCPFactorization(PyObject* self, PyObject* args) {
    PyObject *listOfLists;
    Py_ssize_t listLen;
    Py_ssize_t xLen;
    int m, n;

    if (!PyArg_ParseTuple(args, "Oii", &listOfLists, &m, &n))
        return NULL;

    if (!PyList_CheckExact(listOfLists)) {
        PyErr_SetString(PyExc_RuntimeError, "Received non-list type object.");
        return NULL;
    }
    Matrix A(m,n);

    listLen = PyList_GET_SIZE(listOfLists);
    for (Py_ssize_t i = 0; i < listLen; ++i) {
        PyObject *listInList = PyList_GET_ITEM(listOfLists, i);

        if (!PyList_CheckExact(listInList)) {
            PyErr_SetString(PyExc_RuntimeError, "Non-list type found in list of lists.");
            return NULL;
        }

        xLen = PyList_GET_SIZE(listInList);
        for (Py_ssize_t j = 0; j < xLen; ++j){
            PyObject *item = PyList_GET_ITEM(listInList, j);
            if (!PyFloat_Check(item)) {
                PyErr_SetString(PyExc_RuntimeError, "Non-float type found in list.");
                return NULL;
            }
            A(i,j) = PyFloat_AsDouble(item);
        }

    }

    auto [Q, R, P] = A.QRCPFactorization();

    // Convert Q, R, and P to Python lists of lists
    PyObject* pyQ = PyList_New(Q.Rows());
    for (size_t i = 0; i < Q.Rows(); ++i) {
        PyObject* row = PyList_New(Q.Cols());
        for (size_t j = 0; j < Q.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(Q(i, j)));
        }
        PyList_SET_ITEM(pyQ, i, row);
    }

    PyObject* pyR = PyList_New(R.Rows());
    for (size_t i = 0; i < R.Rows(); ++i) {
        PyObject* row = PyList_New(R.Cols());
        for (size_t j = 0; j < R.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(R(i, j)));
        }
        PyList_SET_ITEM(pyR, i, row);
    }

    PyObject* pyP = PyList_New(P.Rows());
    for (size_t i = 0; i < P.Rows(); ++i) {
        PyObject* row = PyList_New(P.Cols());
        for (size_t j = 0; j < P.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(P(i, j)));
        }
        PyList_SET_ITEM(pyP, i, row);
    }

    // Return Q, R, and P as a tuple
    PyObject* result = PyTuple_New(3);
    PyTuple_SET_ITEM(result, 0, pyQ);
    PyTuple_SET_ITEM(result, 1, pyR);
    PyTuple_SET_ITEM(result, 2, pyP);

    return result;
}

static PyObject* QRCPFactorization_Parallel(PyObject* self, PyObject* args) {
    PyObject *listOfLists;
    Py_ssize_t listLen;
    Py_ssize_t xLen;
    int m, n;

    if (!PyArg_ParseTuple(args, "Oii", &listOfLists, &m, &n))
        return NULL;

    if (!PyList_CheckExact(listOfLists)) {
        PyErr_SetString(PyExc_RuntimeError, "Received non-list type object.");
        return NULL;
    }
    Matrix A(m,n);

    listLen = PyList_GET_SIZE(listOfLists);
    for (Py_ssize_t i = 0; i < listLen; ++i) {
        PyObject *listInList = PyList_GET_ITEM(listOfLists, i);

        if (!PyList_CheckExact(listInList)) {
            PyErr_SetString(PyExc_RuntimeError, "Non-list type found in list of lists.");
            return NULL;
        }

        xLen = PyList_GET_SIZE(listInList);
        for (Py_ssize_t j = 0; j < xLen; ++j){
            PyObject *item = PyList_GET_ITEM(listInList, j);
            if (!PyFloat_Check(item)) {
                PyErr_SetString(PyExc_RuntimeError, "Non-float type found in list.");
                return NULL;
            }
            A(i,j) = PyFloat_AsDouble(item);
        }

    }

    auto [Q, R, P] = A.QRCPFactorization_Parallel();

    // Convert Q, R, and P to Python lists of lists
    PyObject* pyQ = PyList_New(Q.Rows());
    for (size_t i = 0; i < Q.Rows(); ++i) {
        PyObject* row = PyList_New(Q.Cols());
        for (size_t j = 0; j < Q.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(Q(i, j)));
        }
        PyList_SET_ITEM(pyQ, i, row);
    }

    PyObject* pyR = PyList_New(R.Rows());
    for (size_t i = 0; i < R.Rows(); ++i) {
        PyObject* row = PyList_New(R.Cols());
        for (size_t j = 0; j < R.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(R(i, j)));
        }
        PyList_SET_ITEM(pyR, i, row);
    }

    PyObject* pyP = PyList_New(P.Rows());
    for (size_t i = 0; i < P.Rows(); ++i) {
        PyObject* row = PyList_New(P.Cols());
        for (size_t j = 0; j < P.Cols(); ++j) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(P(i, j)));
        }
        PyList_SET_ITEM(pyP, i, row);
    }

    // Return Q, R, and P as a tuple
    PyObject* result = PyTuple_New(3);
    PyTuple_SET_ITEM(result, 0, pyQ);
    PyTuple_SET_ITEM(result, 1, pyR);
    PyTuple_SET_ITEM(result, 2, pyP);

    return result;
}

static PyMethodDef MatrixutilMethods[] = {
    {"LUFactorization", LUFactorization, METH_VARARGS, "Computes LU factorization of a matrix."},
    {"LUPFactorization", LUPFactorization, METH_VARARGS, "Computes LUP factorization of a matrix."},
    {"LUPFactorization_Parallel", LUPFactorization_Parallel, METH_VARARGS, "Computes LUP factorization in parallel of a matrix."},
    {"QRFactorization", QRFactorization, METH_VARARGS, "Computes QR factorization of a matrix."},
    {"QRCPFactorization", QRCPFactorization, METH_VARARGS, "Computes QRCP factorization of a matrix."},
    {"QRCPFactorization_Parallel", QRCPFactorization, METH_VARARGS, "Computes QRCP factorization of a matrix in paralel."},
    {NULL, NULL, 0, NULL} // Sentinel
};

static struct PyModuleDef Matrixutil = {
    PyModuleDef_HEAD_INIT,
    "Matrix", // Module name
    "Basic dense Linear Algebra Operations.", // Module documentation
    -1,
    MatrixutilMethods
};

PyMODINIT_FUNC PyInit_Matrixutil(void) {
    return PyModule_Create(&Matrixutil);
}

} // extern "C"