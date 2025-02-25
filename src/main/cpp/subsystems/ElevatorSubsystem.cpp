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
}
void Elevator::sendData() { // nt::NetworkTableInstance elevatorInst =
  // nt::NetworkTableInstance::GetDefault();
  frc::SmartDashboard::PutNumber("Elevator/MasterPose",
                                 masterM.GetPosition().GetValueAsDouble());
  frc::SmartDashboard::PutNumber("Elevator/SlavePose",
                                 slaveM.GetPosition().GetValueAsDouble());
  frc::SmartDashboard::PutString("Elevator/Master Control Mode",
                                 masterM.GetControlMode().ToString());
  frc::SmartDashboard::PutNumber(
      "Elevator/Encoder Value",
      elevatorEncoder.GetPosition().GetValueAsDouble());
  frc::SmartDashboard::PutNumber(
      "Elevator/Encoder abs val",
      elevatorEncoder.GetAbsolutePosition().GetValueAsDouble());
}
