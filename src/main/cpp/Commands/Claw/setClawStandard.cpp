#include "commands/Claw/setClawStandard.h"


setClawStandard::setClawStandard(subsystems::Claw* subsystem) : Claw(subsystem) {

  AddRequirements(subsystem);

}


void setClawStandard::Initialize() {

  Claw->setAxis(0_deg);

}


bool setClawStandard::IsFinished() {

  return true;

}