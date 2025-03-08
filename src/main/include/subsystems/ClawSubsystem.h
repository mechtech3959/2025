#pragma once

#include "SystemConstants.h"
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <ctre/phoenix6/SignalLogger.hpp>
#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>
#include <frc2/command/sysid/SysIdRoutine.h>

namespace subsystems {

class Claw : public frc2::SubsystemBase {
private:
  rev::spark::SparkMax feedMotor;
  ctre::phoenix6::hardware::TalonFX axisMotor;
  ctre::phoenix6::hardware::CANcoder axisEncoder;
  ctre::phoenix6::controls::MotionMagicVoltage axisMotion;
  ctre::phoenix6::controls::VoltageOut sysReq{0_V};
  ctre::phoenix6::configs::Slot0Configs axisSlot =
      ctre::phoenix6::configs::Slot0Configs{}
          .WithKS(0.3)
          .WithKA(0)
          .WithKG(0)
          .WithKI(0.2)
          .WithKD(0.1)
          .WithKV(0.001)
          .WithKP(8)
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
                  .WithForwardSoftLimitEnable(false)
                  .WithReverseSoftLimitThreshold(0_deg)
                  .WithReverseSoftLimitEnable(false))
          .WithMotorOutput(ctre::phoenix6::configs::MotorOutputConfigs{}
                               .WithInverted(1)
                               .WithNeutralMode(1))
          .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
                               .WithMotionMagicCruiseVelocity(80_tps)
                               .WithMotionMagicAcceleration(80_tr_per_s_sq)
                               .WithMotionMagicJerk(1600_tr_per_s_cu))
          .WithCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs{}
                                 .WithSupplyCurrentLimit(15_A)
                                 .WithSupplyCurrentLimitEnable(true));
  ctre::phoenix6::configs::CANcoderConfiguration encoderConfigs =
      ctre::phoenix6::configs::CANcoderConfiguration{}.WithMagnetSensor(
          ctre::phoenix6::configs::MagnetSensorConfigs{}
              .WithSensorDirection(1)
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
  bool crl;
frc2::sysid::SysIdRoutine m_sysIdRoutine_Claw{
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
         axisMotor.SetControl(sysReq.WithOutput(output).WithLimitForwardMotion(true).WithLimitReverseMotion(true));
          },
          {},
          this}};   
frc2::CommandPtr SysIdQuasistatic(frc2::sysid::Direction direction)
{
   return m_sysIdRoutine_Claw.Quasistatic(direction);
}
frc2::CommandPtr SysIdDynamic(frc2::sysid::Direction direction)
{
   return m_sysIdRoutine_Claw.Dynamic(direction);
}
  Claw();
  void Periodic() override;
  void setFeedStop();
  void setIntake();
  void setOutake();
  void setStaticIntake();
  void setStaticOuttake();
  void percentOut(double s);
  void setAxis(units::degree_t angle);
  void sendData();
  bool hasCoral();
};

} // namespace subsystems
