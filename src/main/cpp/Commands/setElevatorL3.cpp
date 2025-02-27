#include "commands/setElevatorL3.h"


setElevatorL3::setElevatorL3(subsystems::Elevator* subsystem) : Elevator(subsystem) {

  AddRequirements(subsystem);

}


void setElevatorL3::Execute() {
//wtv the val is 
  Elevator->setHeight(48_tr);

}


bool setElevatorL3::IsFinished() {

  return true;

}