#pragma once

#include <ctre/phoenix6/SignalLogger.hpp>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>
#include <frc2/command/sysid/SysIdRoutine.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

#include "SystemConstants.h"
namespace subsystems {

class Elevator : public frc2::SubsystemBase {
private:
  ctre::phoenix6::hardware::TalonFX masterM;
  ctre::phoenix6::hardware::TalonFX slaveM;
  ctre::phoenix6::hardware::CANcoder elevatorEncoder;
  ctre::phoenix6::controls::MotionMagicVoltage elevatorMotion;

  // ctre::phoenix6::controls::DynamicMotionMagicVoltage ele{0_tr};
  ctre::phoenix6::controls::MotionMagicVoltage ele{0_tr};
  ctre::phoenix6::controls::VoltageOut sysReq{0_V};

  ctre::phoenix6::configs::Slot0Configs slot =
      ctre::phoenix6::configs::Slot0Configs{}
          .WithGravityType(
              ctre::phoenix6::signals::GravityTypeValue::Elevator_Static)
          .WithKP(7)//3.5 5
          .WithKI(0.8)//1 
          .WithKD(0.1)
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
          .WithMotionMagicCruiseVelocity(20_tps)//10 11
          .WithMotionMagicAcceleration(20_tr_per_s_sq)//10 11
          .WithMotionMagicExpo_kA(
              ctre::unit::volts_per_turn_per_second_squared_t{0.3});

  ctre::phoenix6::configs::FeedbackConfigs fbConfigs =
      ctre::phoenix6::configs::FeedbackConfigs{}
          .WithRotorToSensorRatio(1)
          .WithSensorToMechanismRatio(18)
          .WithFeedbackRemoteSensorID(9);
  ctre::phoenix6::configs::TalonFXConfiguration elevatorConfigs =
      ctre::phoenix6::configs::TalonFXConfiguration{}
          .WithSlot0(slot)
          .WithMotionMagic(magicMotionConfigs)
          .WithMotorOutput(ctre::phoenix6::configs::MotorOutputConfigs{}
                               .WithInverted(0)
                               .WithNeutralMode(1))
          .WithCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs{}
                                 .WithSupplyCurrentLimit(60_A)
                                 .WithSupplyCurrentLowerLimit(30_A)
                                 .WithSupplyCurrentLowerTime(1_s)
                                 .WithSupplyCurrentLimitEnable(false))
          .WithFeedback(fbConfigs);
  ctre::phoenix6::configs::CANcoderConfiguration encoderConfigs =
      ctre::phoenix6::configs::CANcoderConfiguration{};

public:
  units::angle::turn_t target = 0_tr;
  // inches, measurements are relative to the floor

  units::inch_t Zero = 0_in;
  units::inch_t Barge = 62_in;     // 101 / 5.166666666666667 tr
  units::inch_t Processor = 15_in; // top =27 bottom is 7 ,1.25tr
  units::inch_t L1 = 18_in;        // 1.5 tr
  units::inch_t L2 = 32_in;        // 31.875, / 2.666666666666667 tr
  units::inch_t L3 = 48_in;        // 47.625 / 4 tr
  units::inch_t L4 = 62_in;        // 72 / 5.166666666666667 tr

  enum State {
    Traveling,
    onTarget

  };
  ElevatorState elevatorLog;
  frc2::sysid::SysIdRoutine m_sysIdRoutine_Elevator{
      frc2::sysid::Config{
          std::nullopt, // Use default ramp rate (1 V/s)
          4_V, // Reduce dynamic step voltage to 4 V to prevent brownout
          std::nullopt, // Use default timeout (10 s)
          // Log state with SignalLogger class
          [](frc::sysid::State state) {
            ctre::phoenix6::SignalLogger::WriteString(
                "SysIdCLaw_State",
                frc::sysid::SysIdRoutineLog::StateEnumToString(state));
          }},
      frc2::sysid::Mechanism{
          [this](units::volt_t output) {
            masterM.SetControl(sysReq.WithOutput(output)
                                   .WithLimitForwardMotion(true)
                                   .WithLimitReverseMotion(true));
            slaveM.SetControl(sysReq.WithOutput(output)
                                  .WithLimitForwardMotion(true)
                                  .WithLimitReverseMotion(true));
          },
          {},
          this}};
  frc2::CommandPtr SysIdQuasistatic(frc2::sysid::Direction direction) {
    return m_sysIdRoutine_Elevator.Quasistatic(direction);
  }
  frc2::CommandPtr SysIdDynamic(frc2::sysid::Direction direction) {
    return m_sysIdRoutine_Elevator.Dynamic(direction);
  }

  Elevator();
  void setHeight(units::turn_t pos);
  void coastOut();
  bool isAtTarget();
  void sendData();
  void Periodic() override;
};
} // namespace subsystems