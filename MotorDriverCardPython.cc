#include <MotorDriverCard/StepperMotor.h>
#include <boost/python.hpp>
#include <boost/noncopyable.hpp>

using namespace mtca4u;
namespace bp = boost::python;

BOOST_PYTHON_MODULE(motor) {
  //  class_<mtca4u::StepperMotorUnitsConverter>("StepperMotorUnitsConverter")
  //    .def("stepsToUnits", &StepperMotorUnitsConverter::stepsToUnits)
  //    .def("unitsToSteps", &World::unitsToSteps)
  //    ;

  bp::class_<StepperMotorStatusAndError>("StepperMotorStatusAndError");

  bp::class_<StepperMotor, boost::noncopyable>(
      "StepperMotor", bp::init<std::string const &, std::string const &,
                               unsigned int, std::string>())
      .def("moveToPosition", &StepperMotor::moveToPosition)
      .def("setTargetPosition", &StepperMotor::setTargetPosition)
      .def("getTargetPosition", &StepperMotor::setTargetPosition)
      .def("getCurrentPosition", &StepperMotor::getCurrentPosition)
      .def("setCurrentPositionAs", &StepperMotor::setCurrentPositionAs)
      .def("start", &StepperMotor::start)
      .def("stop", &StepperMotor::stop)
      .def("setEnabled", &StepperMotor::setEnabled)
      .def("getEnabled", &StepperMotor::getEnabled);
}
