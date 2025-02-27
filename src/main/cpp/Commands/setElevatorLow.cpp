#include "commands/Elevator/setElevatorLow.h"


setElevatorLow::setElevatorLow(subsystems::Elevator* subsystem) : Elevator(subsystem) {

  AddRequirements(subsystem);

}


void setElevatorLow::Execute() {

  Elevator->setHeight(0_tr);

}


bool setElevatorLow::IsFinished() {

  return true;

}