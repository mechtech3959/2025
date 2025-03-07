#include "Commands/Claw/setClawIntake.h"

setClawIntake::setClawIntake(subsystems::Claw *subsystem) : Claw(subsystem) {

  AddRequirements(subsystem);
}

void setClawIntake::Initialize() {
  Claw->setAxis(0_deg);
  Claw->percentOut(-0.2);
 
}
void setClawIntake::Execute(){ 
   Claw->clawPeriodic();


}
void setClawIntake::End() { 
  Claw ->percentOut(0);
  Claw->setAxis(30_deg); }
bool setClawIntake::IsFinished() {
return Claw->hasCoral();
}