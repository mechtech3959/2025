#include "subsystems/ElevatorSubsystem.h"

using namespace subsystems;

Elevator::Elevator() {
  masterM.GetConfigurator().Apply(Constants::Elevator::elevatorConfigs);
  slaveM.GetConfigurator().Apply(Constants::Elevator::elevatorConfigs);
  slaveM.SetControl(
      ctre::phoenix6::controls::Follower{masterM.GetDeviceID(), false});
}

// hypothetical 1 rotation = 6inches? 8:1 ratio
void Elevator::setHeight(Positions pos) {
  ctre::phoenix6::controls::DynamicMotionMagicTorqueCurrentFOC heightR =
      ctre::phoenix6::controls::DynamicMotionMagicTorqueCurrentFOC{
          0_tr, 2_tps, 4_tr_per_s_sq, 40_tr_per_s_cu};
  // TODO: figure out conversion calc / consts for rotary to inches
  masterM.SetControl(heightR.WithPosition(2_tr));
}
void Elevator::sendData() {
  // nt::NetworkTableInstance elevatorInst =
  // nt::NetworkTableInstance::GetDefault();
  frc::SmartDashboard::PutNumber("Elevator/MasterPose",
                                 masterM.GetPosition().GetValueAsDouble());
  frc::SmartDashboard::PutNumber("Elevator/SlavePose",
                                 slaveM.GetPosition().GetValueAsDouble());
  frc::SmartDashboard::PutString("Elevator/Master Control Mode",
                                 masterM.GetControlMode().ToString());
  frc::SmartDashboard::PutNumber("Elevator/Encoder Value",
                                 encoder.GetPosition().GetValueAsDouble());
  frc::SmartDashboard::PutNumber(
      "Elevator/Encoder abs val",
      encoder.GetAbsolutePosition().GetValueAsDouble());
}
