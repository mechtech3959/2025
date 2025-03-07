#include "Commands/Claw/setClawIntake.h"

setClawIntake::setClawIntake(subsystems::Claw *subsystem) : Claw(subsystem) {

  AddRequirements(subsystem);
}

void setClawIntake::Initialize() {
  Claw->setAxis(0_deg);
 
}
void setClawIntake::Execute(){ 
   Claw->clawPeriodic();

 if (Claw->hasCoral() != true) {
    Claw->percentOut(-0.2);
  } else {
    Claw->percentOut(0);
    Claw->endIntake = true;
  };
}
void setClawIntake::End() { Claw->setAxis(30_deg); }
bool setClawIntake::IsFinished() {
  if (Claw->endIntake == true)
    return true;
}