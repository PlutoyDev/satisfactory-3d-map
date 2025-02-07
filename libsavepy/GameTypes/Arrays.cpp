#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "SatisfactorySave/GameTypes/Arrays/Base/Array.h"
#include "SatisfactorySave/GameTypes/Arrays/Base/ArrayAll.h"

namespace py = pybind11;
namespace s = SatisfactorySave;

void init_GameTypes_Arrays(py::module_& m) {
    py::class_<s::Array>(m, "Array");

    py::class_<s::BoolArray, s::Array>(m, "BoolArray")
        .def_readwrite("Values", &s::BoolArray::Values);

    py::class_<s::ByteArray, s::Array>(m, "ByteArray")
        .def_readwrite("Values", &s::ByteArray::Values);

    py::class_<s::EnumArray, s::Array>(m, "EnumArray")
        .def_readwrite("Values", &s::EnumArray::Values);

    py::class_<s::FloatArray, s::Array>(m, "FloatArray")
        .def_readwrite("Values", &s::FloatArray::Values);

    py::class_<s::Int64Array, s::Array>(m, "Int64Array")
        .def_readwrite("Values", &s::Int64Array::Values);

    py::class_<s::IntArray, s::Array>(m, "IntArray")
        .def_readwrite("Values", &s::IntArray::Values);

    py::class_<s::InterfaceArray, s::Array>(m, "InterfaceArray")
        .def_readwrite("Values", &s::InterfaceArray::Values);

    py::class_<s::NameArray, s::Array>(m, "NameArray")
        .def_readwrite("Values", &s::NameArray::Values);

    py::class_<s::ObjectArray, s::Array>(m, "ObjectArray")
        .def_readwrite("Values", &s::ObjectArray::Values);

    py::class_<s::SoftObjectArray, s::Array>(m, "SoftObjectArray")
        .def_readwrite("Values", &s::SoftObjectArray::Values);

    py::class_<s::StrArray, s::Array>(m, "StrArray")
        .def_readwrite("Values", &s::StrArray::Values);

    py::class_<s::StructArray, s::Array>(m, "StructArray")
        //.def_readwrite("Values", &s::StructArray::Values) // TODO
        .def("name", &s::StructArray::name)
        .def("structName", &s::StructArray::structName)
        .def("structGuid", &s::StructArray::structGuid);
}
