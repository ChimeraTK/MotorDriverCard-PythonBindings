#include <MotorDriverCard/StepperMotor.h>
#include <MotorDriverCard/LinearStepperMotor.h>
#include <boost/python.hpp>
#include <boost/noncopyable.hpp>

using namespace mtca4u;
namespace bp = boost::python;

std::string returnMotorStatusAsString(LinearStepperMotorStatusAndError &self);
std::string returnMotorErrorAsString(LinearStepperMotorStatusAndError &self);
int returnMotorStatusID(LinearStepperMotorStatusAndError &self);
int returnMotorErrorID(LinearStepperMotorStatusAndError &self);

std::string returnCalibrartionStatusAsString(StepperMotorCalibrationStatus &self);
int returnCalibrationMotorStatusID(StepperMotorCalibrationStatus &self);

BOOST_PYTHON_MODULE(steppermotor) {
  bp::class_<LinearStepperMotorStatusAndError>("StatusAndError", bp::init<>())
      .def("getStatus", &returnMotorStatusAsString)
      .def("getError", &returnMotorErrorAsString)
      .def("getStatusID", &returnMotorStatusID)
      .def("getErrorID", &returnMotorErrorID);

  bp::class_<StepperMotorCalibrationStatus>("StatusAndError", bp::init<>())
      .def("getStatus", &returnCalibrartionStatusAsString)
      .def("getStatusID", &returnCalibrationMotorStatusID);

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
      .def("calibrateMotor", &LinearStepperMotor::calibrateMotor)
      .def("getNegativeEndSwitchPosition", &LinearStepperMotor::getNegativeEndSwitchPosition)
      .def("getPositiveEndSwitchPosition", &LinearStepperMotor::getPositiveEndSwitchPosition)
      .def("getStatusAndError", &LinearStepperMotor::getStatusAndError)
      .def("setStepperMotorUnitsConverter", &LinearStepperMotor::setStepperMotorUnitsConverter);
}

std::string returnMotorStatusAsString(LinearStepperMotorStatusAndError &self) {
  return self.status.asString();
}

std::string returnMotorErrorAsString(LinearStepperMotorStatusAndError &self) {
  return self.error.asString();
}

int returnMotorStatusID(LinearStepperMotorStatusAndError &self) {
  return self.status.getId();
}

int returnMotorErrorID(LinearStepperMotorStatusAndError &self) {
  return self.error.getId();
}

std::string returnCalibrartionStatusAsString(
    StepperMotorCalibrationStatus &self) {
  return self.asString();
}

int returnCalibrationMotorStatusID(StepperMotorCalibrationStatus &self) {
  return self.getId();
}
