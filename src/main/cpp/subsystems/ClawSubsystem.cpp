#include "subsystems/ClawSubsystem.h"

using namespace subsystems;

Claw::Claw()
    : feedMotor{30, rev::spark::SparkMax::MotorType::kBrushless},
      axisMotor{14, "CanBus"}, axisEncoder{15, "CanBus"}, axisMotion{0_deg} {
  axisMotor.SetPosition(0_deg);
  axisEncoder.SetPosition(0_deg);
  axisEncoder.GetConfigurator().Apply(encoderConfigs);
  axisMotor.GetConfigurator().Apply(axisConfig);
};
units::angle::degree_t Claw::getAngle() {
  return (axisEncoder.GetPosition().GetValue());
};
void Claw::setAxis(units::degree_t angle) {
  axisMotor.SetControl(axisMotion.WithPosition(angle));
  lastKnownAngle = angle;
  // status signal for motor output
  (axisMotor.GetMotorOutputStatus().GetValue() == 2) ? state = onTarget
                                                     : state = traveling;
};
void Claw::setFeedStop() { feedMotor.Set(0); };
void Claw::setIntake() {
  if (hasCoral() == true) {
    // frc::Wait(0.3_s);
    feedMotor.Set(0);
    endIntake = true;
  } else {
    feedMotor.Set(-0.2);
  };
};
void Claw::setOutake() {
  (hasCoral() == 1) ? feedMotor.Set(0.1) : feedMotor.Set(0);
  endIntake = false;
};
void Claw::percentOut(double s) { feedMotor.Set(s); }
void Claw::setStaticIntake() { feedMotor.Set(0.1); };
// FOR ALGEA
void Claw::setStaticOuttake() { feedMotor.Set(-0.5); };
void Claw::sendData() {
  clawLog.axisMotorPose = axisMotor.GetPosition().GetValueAsDouble();
  clawLog.encoderPose = axisEncoder.GetPosition().GetValueAsDouble();
  clawLog.encoderABSPose = axisEncoder.GetAbsolutePosition().GetValueAsDouble();
  clawLog.currentAngle = double{getAngle()};
  clawLog.acceptableAngle = acceptableAngle();    
  clawLog.coralDetected = hasCoral();
};
bool Claw::hasCoral() {
  bool val;
  if (feedMotor.GetAnalog().GetVoltage() >= 2.9) {
    val = true;
  } else {
    val = false;
  };
  return val;
};
bool Claw::acceptableAngle() {
  if ((getAngle() == lastKnownAngle) ||
      ((getAngle() >= lastKnownAngle - 5_deg) &&
       (getAngle() <= lastKnownAngle + 5_deg))) {
    return true;
  } else {
    return false;
  }
};
void Claw::Periodic() {
  acceptableAngle();
  hasCoral();
  sendData();
  getAngle();
  frc::SmartDashboard::PutNumber("axis Angle", double{getAngle()});
  frc::SmartDashboard::PutNumber("sensorV", feedMotor.GetAnalog().GetVoltage());
  frc::SmartDashboard::PutNumber("c", feedMotor.GetBusVoltage());
};
