#ifndef SESSIONBINDINGS_H
#define SESSIONBINDINGS_H

#include <pybind11/pybind11.h>
#include "Sessions.h"

/**
 * @brief Intermediate function to bind sessions
 * 
 * @param m pybind11 module
 */
void bind_sessions(pybind11::module &m);

#endif // SESSIONBINDINGS_H