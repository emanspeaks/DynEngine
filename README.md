# DynEngine

Dynamics engine with unit conversions and relativity

This project aims to create a simulation environment for dynamics simulations
including astrodynamics and aerodynamics.
The underlying paradigm is to create a new "strongly-typed" scripting language,
except that the quantities must be "typed" with a dimension instead of
classical datatypes.
Quantities are always stored in their original units to maximize precision
instead of converting to some common system for storage.
While the project will natively have SI units built-in, the framework will allow
for other base systems as long as they are "well defined."

The language syntax and class relationships are still being determined, but will
likely draw influences from C++, Python, Julia, and Fortran.
The underlying code will be in Fortran and C most likely.  This will provide
maximum performance for complex simulations.
My goal is to use this project to learn how to make various existing
physics-related libraries work together, like SPICE and SOFA.
