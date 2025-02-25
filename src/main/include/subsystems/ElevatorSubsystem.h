#pragma once 

#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

#include "SystemConstants.h"
namespace subsystems {

class Elevator : public frc2::SubsystemBase {
private:
  ctre::phoenix6::hardware::TalonFX masterM{22};
  ctre::phoenix6::hardware::TalonFX slaveM{23};
  ctre::phoenix6::hardware::CANcoder elevatorEncoder{23};
  ctre::phoenix6::controls::MotionMagicExpoTorqueCurrentFOC elevatorMotion{
      0_tr};

public:
  // inches, measurements are relative to the floor
 
  units::inch_t Zero = 0_in;
  units::inch_t Barge = 62_in;     // 101
  units::inch_t Processor = 15_in; // top =27 bottom is 7 ,
  units::inch_t L1 = 18_in;
  units::inch_t L2 = 31_in; // 31.875,
  units::inch_t L3 = 48_in; // 47.625
  units::inch_t L4 = 62_in; // 72
 

  enum State {
    Traveling,
    onTarget

  };
  Elevator();
  void setHeight(units::turn_t pos);
  void sendData();
};
} // namespace subsystems