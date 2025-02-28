#include "commands/Claw/setClawL4.h"

setClawL4::setClawL4(subsystems::Claw *subsystem) : Claw(subsystem) {

  AddRequirements(subsystem);
}

void setClawL4::Initialize() { Claw->setAxis(90_deg); }

bool setClawL4::IsFinished() { return true; }