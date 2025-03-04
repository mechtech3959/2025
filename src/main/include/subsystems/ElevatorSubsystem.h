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
  ctre::phoenix6::hardware::TalonFX masterM{19};
  ctre::phoenix6::hardware::TalonFX slaveM{20};
  ctre::phoenix6::hardware::CANcoder elevatorEncoder{9};
  ctre::phoenix6::controls::MotionMagicExpoTorqueCurrentFOC elevatorMotion{
      0_tr};
  ctre::phoenix6::configs::Slot0Configs slot =
      ctre::phoenix6::configs::Slot0Configs{}
          .WithGravityType(
              ctre::phoenix6::signals::GravityTypeValue::Elevator_Static)
          .WithKP(0.5)
          .WithKI(2)
          .WithKD(1)
          .WithKS(0.4)
          .WithKG(0.3)
          .WithKV(0.001)
          .WithStaticFeedforwardSign(
              ctre::phoenix6::signals::StaticFeedforwardSignValue::
                  UseClosedLoopSign);
  // set to example values
  // https://v6.docs.ctr-electronics.com/en/2024/docs/api-reference/device-specific/talonfx/motion-magic.html
  ctre::phoenix6::configs::MotionMagicConfigs magicMotionConfigs =
      ctre::phoenix6::configs::MotionMagicConfigs{}
          .WithMotionMagicJerk(2000_tr_per_s_cu)
          .WithMotionMagicCruiseVelocity(40_tps)
          .WithMotionMagicAcceleration(80_tr_per_s_sq);
  ctre::phoenix6::configs::FeedbackConfigs fbConfigs =
      ctre::phoenix6::configs::FeedbackConfigs{}
          .WithRotorToSensorRatio(4)
          .WithSensorToMechanismRatio(1)
          .WithFeedbackRemoteSensorID(9);
  ctre::phoenix6::configs::TalonFXConfiguration elevatorConfigs =
      ctre::phoenix6::configs::TalonFXConfiguration{}
          .WithSlot0(slot)
          .WithMotionMagic(magicMotionConfigs).WithMotorOutput(ctre::phoenix6::configs::MotorOutputConfigs{}
                               .WithInverted(0)
                               .WithNeutralMode(1))
          .WithCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs{}
                                 .WithSupplyCurrentLimit(60_A)
                                 .WithSupplyCurrentLowerLimit(30_A)
                                 .WithSupplyCurrentLowerTime(1_s)
                                 .WithSupplyCurrentLimitEnable(true))
          .WithFeedback(fbConfigs);

  ctre::phoenix6::configs::CANcoderConfiguration encoderConfigs =
      ctre::phoenix6::configs::CANcoderConfiguration{};

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
  ElevatorState elevatorLog;
  Elevator();
  void setHeight(units::turn_t pos);
  bool isAtTarget();
  void sendData();
};
} // namespace subsystems