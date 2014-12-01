#include <MotorDriverCard/StepperMotor.h>
#include <boost/python.hpp>
#include <boost/noncopyable.hpp>

using namespace mtca4u;
using namespace boost::python;

BOOST_PYTHON_MODULE(mtca4u_MotorDriverCardPython)
{
//  class_<mtca4u::StepperMotorUnitsConverter>("StepperMotorUnitsConverter")
//    .def("stepsToUnits", &StepperMotorUnitsConverter::stepsToUnits)
//    .def("unitsToSteps", &World::unitsToSteps)
//    ;
  

  class_<StepperMotorStatusAndError>("StepperMotorStatusAndError")
    ;

  class_<StepperMotor, boost::noncopyable>("StepperMotor",
		       init<std::string, unsigned int, std::string, std::string>())
    .def("moveToPosition",&StepperMotor::moveToPosition)
    .def("setTargetPosition",&StepperMotor::setTargetPosition)
    .def("getTargetPosition",&StepperMotor::setTargetPosition)
    .def("getCurrentPosition",&StepperMotor::getCurrentPosition)
    .def("setCurrentPositionAs",&StepperMotor::setCurrentPositionAs)
    .def("start",&StepperMotor::start)
    .def("stop",&StepperMotor::stop)
    .def("setEnabled",&StepperMotor::setEnabled)
    .def("getEnabled",&StepperMotor::getEnabled)
    ;
}
