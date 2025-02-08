#include "subsystems/ClawSubsystem.h"

using namespace subsystems;

void Claw::clawInit() {
  axisMotor.GetConfigurator().Apply(Constants::claw::axisConfigs);
  intakeMotor.GetConfigurator().Apply(Constants::claw::intakeConfigs);
};

void Claw::setAxis(units::degree pos) {
  // TODO: encoder realitive movement
};
void Claw::setIntake() {
  // sensor integration function to stop after EX:0.5 second detection
  //  set ramdom for a static feed
  intakeMotor.Set(0.3);
};