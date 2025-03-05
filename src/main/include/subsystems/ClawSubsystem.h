#pragma once

#include "SystemConstants.h"
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>

namespace subsystems {

class Claw : public frc2::SubsystemBase {
private:
  rev::spark::SparkMax feedMotor;
  ctre::phoenix6::hardware::TalonFX axisMotor;
  ctre::phoenix6::hardware::CANcoder axisEncoder;
  ctre::phoenix6::controls::MotionMagicVoltage axisMotion;
  ctre::phoenix6::configs::Slot0Configs axisSlot =
      ctre::phoenix6::configs::Slot0Configs{}
          .WithKS(0.3)
          .WithKA(0)
          .WithKG(0)
          .WithKI(0)
          .WithKD(0)
          .WithKV(0.001)
          .WithKP(10)
          .WithGravityType(
              ctre::phoenix6::signals::GravityTypeValue::Arm_Cosine)
          .WithStaticFeedforwardSign(
              ctre::phoenix6::signals::StaticFeedforwardSignValue::
                  UseClosedLoopSign);

  ctre::phoenix6::configs::FeedbackConfigs axisFeedback =
      ctre::phoenix6::configs::FeedbackConfigs{}
          .WithFeedbackRemoteSensorID(15)
          .WithFeedbackSensorSource(
              ctre::phoenix6::signals::FeedbackSensorSourceValue::FusedCANcoder)
          .WithRotorToSensorRatio(16.0)
          .WithSensorToMechanismRatio(1.0);
  ctre::phoenix6::configs::TalonFXConfiguration axisConfig =
      ctre::phoenix6::configs::TalonFXConfiguration{}
          .WithSlot0(axisSlot)
          .WithFeedback(axisFeedback)
          .WithSoftwareLimitSwitch(
              ctre::phoenix6::configs::SoftwareLimitSwitchConfigs{}
                  .WithForwardSoftLimitThreshold(180_deg)
                  .WithForwardSoftLimitEnable(true)
                  .WithReverseSoftLimitThreshold(0_deg)
                  .WithReverseSoftLimitEnable(true))
          .WithMotorOutput(ctre::phoenix6::configs::MotorOutputConfigs{}
                               .WithInverted(0)
                               .WithNeutralMode(1))
          .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
                               .WithMotionMagicCruiseVelocity(50_tps)
                               .WithMotionMagicAcceleration(50_tr_per_s_sq)
                               .WithMotionMagicJerk(1600_tr_per_s_cu))
          .WithCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs{}
                                 .WithSupplyCurrentLimit(10_A)
                                 .WithSupplyCurrentLimitEnable(true));
  ctre::phoenix6::configs::CANcoderConfiguration encoderConfigs =
      ctre::phoenix6::configs::CANcoderConfiguration{}.WithMagnetSensor(
          ctre::phoenix6::configs::MagnetSensorConfigs{}
              .WithSensorDirection(0)
              .WithAbsoluteSensorDiscontinuityPoint(0.5_tr));

public:
  const units::degree_t L123 = 0_deg;
  const units::degree_t L4 = 90_deg;
  const units::degree_t algea = 180_deg;
  const units::degree_t trough = 0_deg;
  units::degree_t lastKnownAngle;
  enum states { traveling, onTarget };
  states state;
  ClawState clawLog;
  bool endIntake = false;

  Claw();
  void clawPeriodic();
  void setFeedStop();
  void setIntake();
  void setOutake();
  void setStaticIntake();
  void setStaticOuttake();
  void setAxis(units::degree_t angle);
  void sendData();
  bool hasCoral();
};

} // namespace subsystems
