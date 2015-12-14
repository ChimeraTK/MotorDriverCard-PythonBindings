#include <MotorDriverCard/StepperMotor.h>
#include <MotorDriverCard/LinearStepperMotor.h>
#include <boost/python.hpp>
#include <boost/noncopyable.hpp>

using namespace mtca4u;
namespace bp = boost::python;

std::string returnStatusAsString(LinearStepperMotorStatusAndError &self);
std::string returnErrorAsString(LinearStepperMotorStatusAndError &self);
int returnStatusID(LinearStepperMotorStatusAndError &self);
int returnErrorID(LinearStepperMotorStatusAndError &self);

BOOST_PYTHON_MODULE(steppermotor) {
  bp::class_<LinearStepperMotorStatusAndError>("StatusAndError", bp::init<>())
      .def("getStatus", &returnStatusAsString)
      .def("getError", &returnErrorAsString)
      .def("getStatusID", &returnStatusID)
      .def("getErrorID", &returnErrorID);

  bp::class_<LinearStepperMotor, boost::noncopyable>(
      "LinearStepperMotor", bp::init<std::string const &, std::string const &,
                                     unsigned int, std::string>())
      .def("emergencyStop", &LinearStepperMotor::emergencyStop)
      .def("moveToPosition", &LinearStepperMotor::moveToPosition)
      .def("setTargetPosition", &LinearStepperMotor::setTargetPosition)
      .def("getTargetPosition", &LinearStepperMotor::getTargetPosition)
      .def("getCurrentPosition", &LinearStepperMotor::getCurrentPosition)
      .def("setCurrentPositionAs", &LinearStepperMotor::setCurrentPositionAs)
      .def("start", &LinearStepperMotor::start)
      .def("getAutostart", &LinearStepperMotor::getAutostart)
      .def("setAutoStart", &LinearStepperMotor::setAutostart)
      .def("stop", &LinearStepperMotor::stop)
      .def("setEnabled", &LinearStepperMotor::setEnabled)
      .def("getEnabled", &LinearStepperMotor::getEnabled)
      .def("getNegativeEndSwitchPosition", &LinearStepperMotor::getNegativeEndSwitchPosition)
      .def("getPositiveEndSwitchPosition", &LinearStepperMotor::getPositiveEndSwitchPosition)
      .def("getStatusAndError", &LinearStepperMotor::getStatusAndError)
      .def("setStepperMotorUnitsConverter", &LinearStepperMotor::setStepperMotorUnitsConverter);
}

std::string returnStatusAsString(LinearStepperMotorStatusAndError &self) {
  return self.status.asString();
}

std::string returnErrorAsString(LinearStepperMotorStatusAndError &self) {
  return self.error.asString();
}

int returnStatusID(LinearStepperMotorStatusAndError &self) {
  return self.status.getId();
}

int returnErrorID(LinearStepperMotorStatusAndError &self) {
  return self.error.getId();
}
