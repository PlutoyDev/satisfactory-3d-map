#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "SatisfactorySave/GameTypes/UE/Misc/Guid.h"
#include "SatisfactorySave/GameTypes/UE/Misc/Hash.h"

namespace py = pybind11;
namespace s = SatisfactorySave;

void init_GameTypes_UE_Misc(py::module_& m) {
    py::class_<s::FGuid>(m, "FGuid")
        .def("isZero", &s::FGuid::isZero)
        .def("toString", &s::FGuid::toString);

    py::class_<s::FMD5Hash>(m, "FMD5Hash")
        .def("toString", &s::FMD5Hash::toString);

    py::class_<s::FSHAHash>(m, "FSHAHash");
}
