#include "commands/Claw/setClawFeedStop.h"

setClawFeedStop::setClawFeedStop(subsystems::Claw *subsystem)
    : Claw(subsystem) {

  AddRequirements(subsystem);
}

void setClawFeedStop::Initialize() { Claw->setFeedStop(); }

bool setClawFeedStop::IsFinished() { return true; }