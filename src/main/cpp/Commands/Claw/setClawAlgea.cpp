#include "commands/Claw/setClawAlgea.h"

setClawAlgea::setClawAlgea(subsystems::Claw *subsystem) : Claw(subsystem) {

  AddRequirements(subsystem);
}

void setClawAlgea::Initialize() { Claw->setAxis(180_deg); }

bool setClawAlgea::IsFinished() { return true; }