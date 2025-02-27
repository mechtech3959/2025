#include "commands/setElevatorL4.h"


setElevatorL4::setElevatorL4(subsystems::Elevator* subsystem) : Elevator(subsystem) {

  AddRequirements(subsystem);

}


void setElevatorL4::Execute() {
//wtv the val is 
  Elevator->setHeight(62_tr);

}


bool setElevatorL4::IsFinished() {

  return true;

}