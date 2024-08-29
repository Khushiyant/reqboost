#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // For automatic conversion of STL types

// Include the C++ libcurl functions
#include "bindings/ApiBindings.h"
#include "bindings/ModelsBindings.h"
#include "bindings/UtilityBindings.h"
#include "bindings/ExceptionBindings.h"


namespace py = pybind11;

PYBIND11_MODULE(reqboost, m) {
     m.doc() = "Python package for HTTP requests based on C++ libcurl";

#ifdef VERSION_INFO
     m.attr("__version__") = VERSION_INFO;
#endif

     bind_models(m);
     bind_api(m);
     bind_utility(m);
     bind_exceptions(m);

}
