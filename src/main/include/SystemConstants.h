#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>

namespace Constants {

namespace Elevator {
// make believe vals
ctre::phoenix6::configs::Slot0Configs slot0 =
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
ctre::phoenix6::configs::MotionMagicConfigs magicMotionConfigs =
    ctre::phoenix6::configs::MotionMagicConfigs{}
        .WithMotionMagicJerk(500_rpm)
        .WithMotionMagicCruiseVelocity(40_rpm)
        .WithMotionMagicAcceleration(60_rpm);
ctre::phoenix6::configs::TalonFXConfiguration elevatorConfigs =
    ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(slot0)
        .WithMotionMagic(magicMotionConfigs)
        .WithCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs{}
                               .WithStatorCurrentLimit(10_A)
                               .WithStatorCurrentLimitEnable(true));

ctre::phoenix6::configs::CANcoderConfiguration encoderConfigs =
    ctre::phoenix6::configs::CANcoderConfiguration{};
} // namespace Elevator

} // namespace Constants