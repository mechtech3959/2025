#include "Commands/Claw/setClawIntake.h"

setClawIntake::setClawIntake(subsystems::Claw *subsystem) : Claw(subsystem) {

  AddRequirements(subsystem);
}

void setClawIntake::Initialize() {
  Claw->setAxis(0_deg);
  Claw->setIntake();
}
void setClawIntake::End(){
    Claw->setAxis(30_deg);
}
bool setClawIntake::IsFinished() {
  if (Claw->endIntake == true)
    return true;
}