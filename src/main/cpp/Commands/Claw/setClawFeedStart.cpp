#include "Commands/Claw/setClawFeedStart.h"

setClawFeedStart::setClawFeedStart(subsystems::Claw *subsystem)
    : Claw(subsystem) {

  AddRequirements(subsystem);
}

void setClawFeedStart::Initialize() { Claw->setIntake(); }

bool setClawFeedStart::IsFinished() { return true; }