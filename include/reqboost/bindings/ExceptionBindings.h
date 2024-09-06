#ifndef EXCEPTIONBINDINGS_H
#define EXCEPTIONBINDINGS_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // For automatic conversion of STL types

#include "Exceptions.h"

/**
 * @brief Intermediate function to bind exceptions
 *
 * @param m pybind11 module
 */
void bind_exceptions(pybind11::module &m);

#endif // EXCEPTIONBINDINGS_H
