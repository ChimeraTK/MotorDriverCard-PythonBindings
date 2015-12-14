#include <MotorDriverCard/StepperMotor.h>
#include <MotorDriverCard/LinearStepperMotor.h>
#include <boost/python.hpp>
#include <boost/noncopyable.hpp>

using namespace mtca4u;
namespace bp = boost::python;

const std::string returnStatusAsString(LinearStepperMotorStatusAndError self);
const std::string returnErrorAsString(LinearStepperMotorStatusAndError self);

std::string global = "Status";
BOOST_PYTHON_MODULE(motor) {
  //  class_<mtca4u::StepperMotorUnitsConverter>("StepperMotorUnitsConverter")
  //    .def("stepsToUnits", &StepperMotorUnitsConverter::stepsToUnits)
  //    .def("unitsToSteps", &World::unitsToSteps)
  //    ;

  bp::class_<LinearStepperMotorStatusAndError>("StatusAndError", bp::init<>())
      .def("getStatus", &returnStatusAsString)
      .def("getError", &returnErrorAsString);

  bp::class_<LinearStepperMotor, boost::noncopyable>(
      "LinearStepperMotor", bp::init<std::string const &, std::string const &,
                                     unsigned int, std::string>())
      .def("emergencyStop", &LinearStepperMotor::emergencyStop)
      .def("moveToPosition", &LinearStepperMotor::moveToPosition)
      .def("setTargetPosition", &LinearStepperMotor::setTargetPosition)
      .def("getTargetPosition", &LinearStepperMotor::setTargetPosition)
      .def("getCurrentPosition", &LinearStepperMotor::getCurrentPosition)
      .def("setCurrentPositionAs", &LinearStepperMotor::setCurrentPositionAs)
      .def("start", &LinearStepperMotor::start)
      .def("getAutostart", &LinearStepperMotor::getAutostart)
      .def("setAutoStart", &LinearStepperMotor::setAutostart)
      .def("stop", &LinearStepperMotor::stop)
      .def("setEnabled", &LinearStepperMotor::setEnabled)
      .def("getEnabled", &LinearStepperMotor::getEnabled)
      .def("getNegativeEndSwitchPosition",
           &LinearStepperMotor::getNegativeEndSwitchPosition)
      .def("getPositiveEndSwitchPosition",
           &LinearStepperMotor::getPositiveEndSwitchPosition)
      .def("getStatusAndError", &LinearStepperMotor::getStatusAndError)
      .def("setStepperMotorUnitsConverter",
           &LinearStepperMotor::setStepperMotorUnitsConverter);
}

const std::string returnStatusAsString(LinearStepperMotorStatusAndError self) {
  return self.status.asString();
}

const std::string returnErrorAsString(LinearStepperMotorStatusAndError self) {
  return self.error.asString();
}
