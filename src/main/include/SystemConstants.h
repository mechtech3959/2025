#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <frc/AnalogInput.h>
#include <frc/DigitalInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <rev/SparkMax.h>


#include "StateLogging.h"
namespace Constants {

namespace Elevator {
// make believe vals
constexpr ctre::phoenix6::configs::Slot0Configs slot =
    ctre::phoenix6::configs::Slot0Configs{}
        .WithGravityType(
            ctre::phoenix6::signals::GravityTypeValue::Elevator_Static)
        .WithKP(5)
        .WithKI(2)
        .WithKD(1)
        .WithStaticFeedforwardSign(
            ctre::phoenix6::signals::StaticFeedforwardSignValue::
                UseClosedLoopSign);
// set to example values
// https://v6.docs.ctr-electronics.com/en/2024/docs/api-reference/device-specific/talonfx/motion-magic.html
constexpr ctre::phoenix6::configs::MotionMagicConfigs magicMotionConfigs =
    ctre::phoenix6::configs::MotionMagicConfigs{}
        .WithMotionMagicJerk(500_tr_per_s_cu)
        .WithMotionMagicCruiseVelocity(40_tps)
        .WithMotionMagicAcceleration(60_tr_per_s_sq);
constexpr ctre::phoenix6::configs::FeedbackConfigs fbConfigs =
    ctre::phoenix6::configs::FeedbackConfigs{}
        .WithRotorToSensorRatio(4)
        .WithSensorToMechanismRatio(1)
        .WithFeedbackRemoteSensorID(14);
constexpr ctre::phoenix6::configs::TalonFXConfiguration elevatorConfigs =
    ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(slot)
        .WithMotionMagic(magicMotionConfigs)
        .WithCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs{}
                               .WithStatorCurrentLimit(10_A)
                               .WithStatorCurrentLimitEnable(true))
        .WithFeedback(fbConfigs);

constexpr ctre::phoenix6::configs::CANcoderConfiguration encoderConfigs =
    ctre::phoenix6::configs::CANcoderConfiguration{};

} // namespace Elevator
namespace claw {
constexpr ctre::phoenix6::configs::Slot0Configs axisSlot =
    ctre::phoenix6::configs::Slot0Configs{}
        .WithKS(0.3)
        .WithKA(0)
        .WithKD(0.50)
        .WithKG(0)
        .WithKI(0)
        .WithKV(0.0)
        .WithKP(10)
        .WithGravityType(ctre::phoenix6::signals::GravityTypeValue::Arm_Cosine)
        .WithStaticFeedforwardSign(
            ctre::phoenix6::signals::StaticFeedforwardSignValue::
                UseClosedLoopSign);

constexpr ctre::phoenix6::configs::FeedbackConfigs axisFeedback =
    ctre::phoenix6::configs::FeedbackConfigs{}
        .WithFeedbackRemoteSensorID(17)
        .WithFeedbackSensorSource(
            ctre::phoenix6::signals::FeedbackSensorSourceValue::FusedCANcoder)
        .WithRotorToSensorRatio(16.0)
        .WithSensorToMechanismRatio(1.0);
constexpr ctre::phoenix6::configs::TalonFXConfiguration axisConfig =
    ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(axisSlot)
        .WithFeedback(axisFeedback)
        .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
                             .WithMotionMagicCruiseVelocity(1_tps)
                             .WithMotionMagicAcceleration(1_tr_per_s_sq)
                             .WithMotionMagicJerk(1600_tr_per_s_cu))
        .WithCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs{}
                               .WithStatorCurrentLimit(10_A)
                               .WithStatorCurrentLimitEnable(true));

constexpr ctre::phoenix6::configs::TalonFXConfiguration intakeConfigs =
    ctre::phoenix6::configs::TalonFXConfiguration{}.WithCurrentLimits(
        ctre::phoenix6::configs::CurrentLimitsConfigs{}
            .WithStatorCurrentLimit(5_A)
            .WithStatorCurrentLimitEnable(true));

} // namespace claw
} // namespace Constants