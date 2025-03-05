#include "subsystems/ElevatorSubsystem.h"

using namespace subsystems;

Elevator::Elevator() {
  masterM.GetConfigurator().Apply(elevatorConfigs);
  slaveM.GetConfigurator().Apply(elevatorConfigs);
  slaveM.SetControl(
      ctre::phoenix6::controls::Follower{masterM.GetDeviceID(), false});
}

// hypothetical 1 rotation = 6inches? 8:1 ratio
void Elevator::setHeight(units::turn_t pos) {
  masterM.SetControl(elevatorMotion.WithPosition(pos));
  target = pos;
}
bool Elevator::isAtTarget() {
  auto m = units::inch_t{elevatorEncoder.GetPosition().GetValueAsDouble()*12};
  if (masterM.GetPosition().GetValue() == target) {
    return true;
  } else {
    return false;
  };
}
void Elevator::sendData() {
  elevatorLog.masterPose = masterM.GetPosition().GetValueAsDouble();
  elevatorLog.slavePose = slaveM.GetPosition().GetValueAsDouble();
  elevatorLog.elevatorPose = elevatorEncoder.GetPosition().GetValueAsDouble();
  elevatorLog.encoderABSPose =
      elevatorEncoder.GetAbsolutePosition().GetValueAsDouble();
  frc::SmartDashboard::PutString("Elevator/Master Control Mode",
                                 masterM.GetControlMode().ToString());
}
