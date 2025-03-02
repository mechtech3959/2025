#include "subsystems/ClawSubsystem.h"

using namespace subsystems;

Claw::Claw()
    : feedMotor{30, rev::spark::SparkMax::MotorType::kBrushless}, axisMotor{14},
      axisEncoder{15}, coralSensor{1}, axisMotion{0_deg} {
  axisMotor.SetPosition(0_deg);
  axisEncoder.SetPosition(0_deg);
  axisEncoder.GetConfigurator().Apply(encoderConfigs);
  axisMotor.GetConfigurator().Apply(axisConfig);
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
  if (hasCoral(coralSensor) == true) {
    frc::Wait(1_s);
    feedMotor.Set(0);
  } else {
    feedMotor.Set(0.1);
  };
};
void Claw::setOutake() {
  (hasCoral(coralSensor) == true) ? feedMotor.Set(0.1) : feedMotor.Set(0);
};
void Claw::setStaticIntake() { feedMotor.Set(0.1); };
// FOR ALGEA
void Claw::setStaticOuttake() { feedMotor.Set(-0.5); };
void Claw::sendData() {
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
