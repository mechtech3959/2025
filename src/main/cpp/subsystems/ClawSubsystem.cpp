#include "subsystems/ClawSubsystem.h"

using namespace subsystems;

Claw::Claw()
    : feedMotor{30, rev::spark::SparkMax::MotorType::kBrushless}, axisMotor{14,"CanBus"},
      axisEncoder{15,"CanBus"},axisMotion{0_deg} {
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
  if (crl == true) {
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
void Claw::percentOut(double s){
  feedMotor.Set(s);
}
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
  clawLog.coralDetected = hasCoral();
};
bool Claw::hasCoral() {
  bool val;
   if(feedMotor.GetAnalog().GetVoltage() >= 2.9){val = true;}
   else{val = false;};
   crl = val;
   return val;
};
void Claw::clawPeriodic() { 
  hasCoral();
  frc::SmartDashboard::PutBoolean("in", crl);
  frc::SmartDashboard::PutNumber("sensorV",feedMotor.GetAnalog().GetVoltage());
frc::SmartDashboard::PutNumber("c",feedMotor.GetBusVoltage());

 };
