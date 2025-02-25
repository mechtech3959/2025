#include "subsystems/ClawSubsystem.h"

using namespace subsystems;

Claw::Claw() {
  axisMotor.GetConfigurator().Apply(Constants::claw::axisConfig);

};

void Claw::setAxis(units::degree_t angle) {
  axisMotor.SetControl(axisMotion.WithPosition(angle));
  lastKnownAngle = angle;
  // status signal for motor output
  (axisMotor.GetMotorOutputStatus().GetValue() == 2) ? state = onTarget
                                                     : state = traveling;
};
void Claw::setIntake() {
  if (hasCoral(coralSensor) == true) {
    frc::Wait(1_s);
    intakeMotor.Set(0);
  } else {
    intakeMotor.Set(0.1);
  };
};
void Claw::setOutake() {
  (hasCoral(coralSensor) == true) ? intakeMotor.Set(0.1) : intakeMotor.Set(0);
};
void Claw::setStaticIntake() { intakeMotor.Set(0.1); };
// FOR ALGEA
void Claw::setStaticOuttake() { intakeMotor.Set(-0.5); };
void Claw::sendData() {
  /* frc::SmartDashboard::PutNumber("axisEncoder pos",
                                  axisEncoder.GetPosition().GetValueAsDouble());
   frc::SmartDashboard::PutNumber(
       "axisEncoder ABSpos",
       axisEncoder.GetAbsolutePosition().GetValueAsDouble());
   frc::SmartDashboard::PutNumber("axisMotor",
                                  axisMotor.GetPosition().GetValueAsDouble());
   frc::SmartDashboard::PutNumber("axisAngle", double(lastKnownAngle));
   frc::SmartDashboard::PutBoolean("AxisState", state);
   frc::SmartDashboard::PutBoolean("has coral?", coralSensor.Get());*/
  clawLog.axisMotorPose = axisMotor.GetPosition().GetValueAsDouble();
  clawLog.encoderPose = axisEncoder.GetPosition().GetValueAsDouble();
  clawLog.encoderABSPose = axisEncoder.GetAbsolutePosition().GetValueAsDouble();
  // CHECK
  clawLog.currentAngle =
      axisEncoder.GetAbsolutePosition().GetValueAsDouble() * 360;
  clawLog.coralDetected = hasCoral(coralSensor);
};
bool Claw::hasCoral(frc::DigitalInput &input) {
  return ((input.Get() == 1) ? false : true);
};
void Claw::clawPeriodic() { hasCoral(coralSensor); };
