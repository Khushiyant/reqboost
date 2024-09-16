#include "Certs.h"

#include <pybind11/embed.h> // for embedded Python interpreter

namespace py = pybind11;

// Define the function
namespace Reqboost{
    namespace Certs{
        std::string get_default_ca_bundle_path()
        {
            // Initialize the Python interpreter
            py::scoped_interpreter guard{};

            // Import the certifi module and call the 'where()' function
            py::object certifi = py::module::import("certifi");
            py::object ca_path = certifi.attr("where")();

            // Convert the result to a C++ string and return
            return ca_path.cast<std::string>();
        }
    }
}
