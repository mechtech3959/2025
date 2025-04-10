#include "subsystems/ElevatorSubsystem.h"

using namespace subsystems;

Elevator::Elevator()
    : masterM{19, "CanBus"}, slaveM{20, "CanBus"}, elevatorEncoder{9, "CanBus"},
      elevatorMotion{0_tr} {
  masterM.SetPosition(0_tr);
  slaveM.SetPosition(0_tr);
  elevatorEncoder.SetPosition(0_tr);
  masterM.GetConfigurator().Apply(elevatorConfigs);
  slaveM.GetConfigurator().Apply(elevatorConfigs);
  slaveM.SetControl(
      ctre::phoenix6::controls::StrictFollower{masterM.GetDeviceID()});
}

// hypothetical 1 rotation = 6inches? 8:1 ratio
void Elevator::setHeight(units::turn_t pos) {

  masterM.SetControl(elevatorMotion.WithPosition(pos)
                         .WithUseTimesync(true)
                         .WithEnableFOC(true)
                         .WithOverrideBrakeDurNeutral(true));
  target = pos;
}
void Elevator::coastOut() {
  masterM.SetControl(ctre::phoenix6::controls::CoastOut{});
  target = 0_tr;
}
bool Elevator::isAtTarget() {
  auto m = units::inch_t{elevatorEncoder.GetPosition().GetValueAsDouble() * 12};
  if (masterM.GetPosition().GetValue() == target) {
    return true;
  } else {
    return false;
  };
}
void Elevator::sendData() {
  isAtTarget();
  elevatorLog.masterPose = masterM.GetPosition().GetValueAsDouble();
  elevatorLog.slavePose = slaveM.GetPosition().GetValueAsDouble();
  elevatorLog.elevatorPose = elevatorEncoder.GetPosition().GetValueAsDouble();
  elevatorLog.encoderABSPose =
      elevatorEncoder.GetAbsolutePosition().GetValueAsDouble();
  frc::SmartDashboard::PutString("Elevator/Master Control Mode",
                                 masterM.GetControlMode().ToString());
  frc::SmartDashboard::PutNumber("Elevator pose",
                                 masterM.GetPosition().GetValueAsDouble());
  frc::SmartDashboard::PutNumber(
      "Elevator Encoder pose",
      elevatorEncoder.GetPosition().GetValueAsDouble());
  frc::SmartDashboard::PutBoolean("Elevator at Target?", isAtTarget());
}
void Elevator::Periodic() { sendData(); }