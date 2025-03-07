#include "Commands/Claw/setClawFeedStart.h"

setClawFeedStart::setClawFeedStart(subsystems::Claw *subsystem)
    : Claw(subsystem) {

  AddRequirements(subsystem);
}

void setClawFeedStart::Initialize() {
  Claw->percentOut(-0.2);
  // Claw->endIntake = true;
}

bool setClawFeedStart::IsFinished() {
  if (Claw->endIntake == true) {
    return true;
  } else {
    return false;
  };
}