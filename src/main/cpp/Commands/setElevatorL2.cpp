#include "commands/setElevatorL2.h"


setElevatorL2::setElevatorL2(subsystems::Elevator* subsystem) : Elevator(subsystem) {

  AddRequirements(subsystem);

}


void setElevatorL2::Execute() {
//wtv the val is 
  Elevator->setHeight(32_tr);

}


bool setElevatorL2::IsFinished() {

  return true;

}