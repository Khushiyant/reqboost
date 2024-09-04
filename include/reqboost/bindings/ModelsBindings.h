#ifndef MODELSBINDINGS_H
#define MODELSBINDINGS_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Models.h" // Include the header where Response, ParsedURL, and RequestOptions are defined

/**
 * @brief Intermediate function to bind models
 * 
 * @param m pybind11 module
 */
void bind_models(pybind11::module &m);

#endif // MODELSBINDINGS_H