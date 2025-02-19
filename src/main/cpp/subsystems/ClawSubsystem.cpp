#include "subsystems/ClawSubsystem.h"

using namespace subsystems;

Claw::Claw() {
  axisMotor.GetConfigurator().Apply(Constants::claw::axisConfig);
  intakeMotor.GetConfigurator().Apply(Constants::claw::intakeConfigs);
};

void Claw::setAxis(units::degree_t angle) {
axisMotor.SetControl(axisMotion.WithPosition(angle));
lastKnownAngle  = angle;
};
void Claw::setIntake() {
  // sensor integration function to stop after EX:0.5 second detection
  //  set ramdom for a static feed
  intakeMotor.Set(0.3);

};
void Claw::sendData(){
  frc::SmartDashboard::PutNumber("axisEncoder pos",axisEncoder.GetPosition().GetValueAsDouble());
  frc::SmartDashboard::PutNumber("axisEncoder ABSpose",axisEncoder.GetAbsolutePosition().GetValueAsDouble());
  frc::SmartDashboard::PutNumber("axisMotor",axisMotor.GetPosition().GetValueAsDouble());
  frc::SmartDashboard::PutNumber("axisAngle", double(lastKnownAngle));
  

};