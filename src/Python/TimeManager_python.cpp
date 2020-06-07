#include <FDCore/Binding/Python/TimeManager_python.h>

namespace py = pybind11;

void FDCore::Python::bind_timemanager(pybind11::module &m)
{
    py::class_<FDCore::TimeManager<>>(m, "TimeManager")
      .def(py::init())
      .def_property_readonly("beginTime", &FDCore::TimeManager<>::getBeginTime<>)
      .def_property_readonly("lastTime", &FDCore::TimeManager<>::getLastTime<>)
      .def_property_readonly("currentTime", &FDCore::TimeManager<>::getCurrentTime<>)
      .def_property_readonly("elapsedTime", &FDCore::TimeManager<>::getElapsedTime<>)
      .def_property_readonly("deltaTime", &FDCore::TimeManager<>::getDeltaTime<>)
      .def_property_readonly("hasBeginTime", &FDCore::TimeManager<>::hasBeginTime)
      .def_property_readonly("hasLastTime", &FDCore::TimeManager<>::hasLastTime)
      .def("start", &FDCore::TimeManager<>::start)
      .def("restart", &FDCore::TimeManager<>::restart)
      .def("recordTime", &FDCore::TimeManager<>::recordTime)
      .def_static("getTime", &FDCore::TimeManager<>::getTime<>);
}
