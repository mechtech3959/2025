#include "subsystems/ClawSubsystem.h"

using namespace subsystems;

Claw::Claw() {
  axisMotor.GetConfigurator().Apply(Constants::claw::axisConfig);
  intakeMotor.GetConfigurator().Apply(Constants::claw::intakeConfigs);
};

void Claw::setAxis(units::degree pos) {

};
void Claw::setIntake() {
  // sensor integration function to stop after EX:0.5 second detection
  //  set ramdom for a static feed
  intakeMotor.Set(0.3);
};