#include "subsystems/ElevatorSubsystem.h"

using namespace subsystems;

void Elevator::elevatorInit() {
  masterM.GetConfigurator().Apply(Constants::Elevator::elevatorConfigs);
  slaveM.GetConfigurator().Apply(Constants::Elevator::elevatorConfigs);
  slaveM.SetControl(
      ctre::phoenix6::controls::Follower{masterM.GetDeviceID(), false});
}
ctre::phoenix6::controls::DynamicMotionMagicTorqueCurrentFOC heightR =
    ctre::phoenix6::controls::DynamicMotionMagicTorqueCurrentFOC{
        0_tr, 2_tps, 4_tr_per_s_sq, 40_tr_per_s_cu};
// hypothetical 1 rotation = 6inches?
void Elevator::setHeight(Positions...) {
  masterM.SetControl(heightR.WithPosition(8_t));
}