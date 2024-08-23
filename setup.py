from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup
import glob
import os
import subprocess
import sys

__version__ = "0.0.0"

def get_pkg_config_paths(package):
    """Get the include and library paths using pkg-config."""
    try:
        include_dirs = subprocess.check_output(
            ["pkg-config", "--cflags", package]
        ).decode().strip().split()
        include_dirs = [d[2:] for d in include_dirs if d.startswith('-I')]

        library_dirs = subprocess.check_output(
            ["pkg-config", "--libs", package]
        ).decode().strip().split()
        library_dirs = [d[2:] for d in library_dirs if d.startswith('-L')]

        return include_dirs, library_dirs
    except subprocess.CalledProcessError:
        return [], []

# Get paths for libcurl and Poco
if sys.platform == "win32":
    # On Windows, use environment variables or provide default paths
    curl_include_dir = os.getenv('CURL_INCLUDE_DIR', 'C:\\curl\\include')
    curl_lib_dir = os.getenv('CURL_LIB_DIR', 'C:\\curl\\lib')
    poco_include_dir = os.getenv('POCO_INCLUDE_DIR', 'C:\\poco\\include')
    poco_lib_dir = os.getenv('POCO_LIB_DIR', 'C:\\poco\\lib')
    curl_include_dirs = [curl_include_dir]
    curl_library_dirs = [curl_lib_dir]
    poco_include_dirs = [poco_include_dir]
    poco_library_dirs = [poco_lib_dir]
else:
    # On Unix-like systems, use pkg-config to find paths
    curl_include_dirs, curl_library_dirs = get_pkg_config_paths('libcurl')
    poco_include_dirs, poco_library_dirs = get_pkg_config_paths('poco')

    # Add default paths in case pkg-config is not available
    if not curl_include_dirs or not curl_library_dirs:
        curl_include_dirs = ["/opt/homebrew/opt/curl/include", "include/reqboost/"]
        curl_library_dirs = ["/opt/homebrew/opt/curl/lib"]
    if not poco_include_dirs or not poco_library_dirs:
        poco_include_dirs = ["/opt/homebrew/opt/poco/include"]
        poco_library_dirs = ["/opt/homebrew/opt/poco/lib"]

ext_modules = [
    Pybind11Extension(
        "reqboost",
        sorted(glob.glob("src/*.cpp")),
        include_dirs=curl_include_dirs + poco_include_dirs,
        libraries=["curl"] + ["PocoFoundation", "PocoNet"],  # Adjust library names as needed
        library_dirs=curl_library_dirs + poco_library_dirs,
        define_macros=[("VERSION_INFO", __version__)],
        extra_compile_args=["-std=c++14"],  # Adjust as necessary
    ),
]

setup(
    name="reqboost",
    version=__version__,
    author="Khushiyant",
    author_email="khushiyant2002@gmail.com",
    url="https://github.com/Khushiyant/reqboost",
    description="Python package for HTTP requests based on C++ libcurl and Poco",
    long_description="",
    license="Apache-2.0",
    classifiers=[
        "Programming Language :: Python :: 3",
        "Programming Language :: C++",
        "Topic :: Internet :: WWW/HTTP",
        "License :: OSI Approved :: MIT License",
    ],
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.10",
)
