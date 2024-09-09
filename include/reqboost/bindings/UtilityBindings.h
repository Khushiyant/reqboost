#ifndef UTILITYBINDINGS_H
#define UTILITYBINDINGS_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // For automatic conversion of STL types

#include "Utility.h"

/**
 * @brief Intermediate function to bind utility
 *
 * @param m pybind11 module
 */
void bind_utility(pybind11::module &m);

#endif // UTILITYBINDINGS_H
