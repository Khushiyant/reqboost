from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup
import glob

__version__ = "0.0.0"

ext_modules = [
    Pybind11Extension(
        "reqboost",
        sorted(glob.glob("src/*.cpp")),  # Automatically include all .cpp files
        include_dirs=["include/reqboost/"],
        define_macros=[("VERSION_INFO", __version__)],
    ),
]

setup(
    name="reqboost",
    version=__version__,
    author="Khushiyant",
    author_email="khushiyant2002@gmail.com",
    url="https://github.com/Khushiyant/reqboost",
    description="Python package for HTTP requests based on C++ libcurl",
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
