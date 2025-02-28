#include "commands/Elevator/setElevatorL1.h"


setElevatorL1::setElevatorL1(subsystems::Elevator* subsystem) : Elevator(subsystem) {

  AddRequirements(subsystem);

}


void setElevatorL1::Initialize() {

  Elevator->setHeight(0_tr);

}


bool setElevatorL1::IsFinished() {

  return true;

}