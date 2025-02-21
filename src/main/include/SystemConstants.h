#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>

namespace Constants {

namespace Elevator {
// 1 rot on axel = 12.4 inchs 1/12 = 0.0806 rot per inch
const units::inch_t maxHeight = 62_in;
// measure
const units::inch_t minHeight = 0_in;

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
        .WithMotionMagicCruiseVelocity(20_tps)
        .WithMotionMagicAcceleration(20_tr_per_s_sq);
constexpr ctre::phoenix6::configs::FeedbackConfigs fbConfigs =
    ctre::phoenix6::configs::FeedbackConfigs{}
        .WithFeedbackSensorSource(
            ctre::phoenix6::signals::FeedbackSensorSourceValue::FusedCANcoder)
        .WithRotorToSensorRatio(8)
        .WithSensorToMechanismRatio(0.08) // was 1 ? converted to rot per in
        .WithFeedbackRemoteSensorID(14);
constexpr ctre::phoenix6::configs::TalonFXConfiguration elevatorConfigs =
    ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(slot)
        .WithMotionMagic(magicMotionConfigs)
        .WithCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs{}
                               .WithStatorCurrentLimit(20_A)
                               .WithStatorCurrentLimitEnable(true))
        .WithFeedback(fbConfigs);

constexpr ctre::phoenix6::configs::CANcoderConfiguration encoderConfigs =
    ctre::phoenix6::configs::CANcoderConfiguration{};

} // namespace Elevator
namespace claw {
constexpr ctre::phoenix6::configs::Slot1Configs intakeSlot =
    ctre::phoenix6::configs::Slot1Configs{};
constexpr ctre::phoenix6::configs::MotionMagicConfigs axisMM =
    ctre::phoenix6::configs::MotionMagicConfigs{}
        .WithMotionMagicJerk(40_tr_per_s_cu)
        .WithMotionMagicAcceleration(20_tr_per_s_sq)
        .WithMotionMagicCruiseVelocity(20_tps);
constexpr ctre::phoenix6::configs::TalonFXConfiguration intakeConfigs =
    ctre::phoenix6::configs::TalonFXConfiguration{}.WithCurrentLimits(
        ctre::phoenix6::configs::CurrentLimitsConfigs{}
            .WithStatorCurrentLimit(5_A)
            .WithStatorCurrentLimitEnable(true));
constexpr ctre::phoenix6::configs::TalonFXConfiguration axisConfigs =
    ctre::phoenix6::configs::TalonFXConfiguration{}.WithCurrentLimits(
        ctre::phoenix6::configs::CurrentLimitsConfigs{}
            .WithStatorCurrentLimit(10_A)
            .WithStatorCurrentLimitEnable(true));

} // namespace claw
} // namespace Constants