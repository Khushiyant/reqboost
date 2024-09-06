#ifndef APIBINDINGS_H
#define APIBINDINGS_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Api.h"
#include "Models.h"

/**
 * @brief Intermediate function to bind API functions
 *
 * @param m pybind11 module
 */
void bind_api(pybind11::module &m);

#endif // APIBINDINGS_H
