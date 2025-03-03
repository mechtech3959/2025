#include "Commands/Claw/setClawStandard.h"

setClawStandard::setClawStandard(subsystems::Claw *subsystem)
    : Claw(subsystem) {

  AddRequirements(subsystem);
}

void setClawStandard::Initialize() { Claw->setAxis(30_deg); }

bool setClawStandard::IsFinished() { return true; }