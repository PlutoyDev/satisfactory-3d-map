#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "SatisfactorySave/GameTypes/MapTypes/Base/MapTypeList.h"
#include "SatisfactorySave/GameTypes/MapTypes/Base/MapTypeListAll.h"

namespace py = pybind11;
namespace s = SatisfactorySave;

void init_GameTypes_MapTypes(py::module_& m) {
    py::class_<s::MapTypeList>(m, "MapTypeList");

    py::class_<s::ByteMapTypeList, s::MapTypeList>(m, "ByteMapTypeList")
        .def_readwrite("List", &s::ByteMapTypeList::List);

    py::class_<s::EnumMapTypeList, s::MapTypeList>(m, "EnumMapTypeList")
        .def_readwrite("List", &s::EnumMapTypeList::List);

    py::class_<s::FloatMapTypeList, s::MapTypeList>(m, "FloatMapTypeList")
        .def_readwrite("List", &s::FloatMapTypeList::List);

    py::class_<s::IntMapTypeList, s::MapTypeList>(m, "IntMapTypeList")
        .def_readwrite("List", &s::IntMapTypeList::List);

    py::class_<s::NameMapTypeList, s::MapTypeList>(m, "NameMapTypeList")
        .def_readwrite("List", &s::NameMapTypeList::List);

    py::class_<s::ObjectMapTypeList, s::MapTypeList>(m, "ObjectMapTypeList")
        .def_readwrite("List", &s::ObjectMapTypeList::List);

    py::class_<s::StructMapTypeList, s::MapTypeList>(m, "StructMapTypeList")
        //.def_readwrite("List", &s::StructMapTypeList::List) // TODO
        ;
}
