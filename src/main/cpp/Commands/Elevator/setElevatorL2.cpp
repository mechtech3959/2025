#include "commands/Elevator/setElevatorL2.h"

setElevatorL2::setElevatorL2(subsystems::Elevator *subsystem)
    : Elevator(subsystem) {

  AddRequirements(subsystem);
}

void setElevatorL2::Initialize() {
  // wtv the val is
  Elevator->setHeight(32_tr);
}

bool setElevatorL2::IsFinished() { return true; }