#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>

namespace Constants {

namespace Elevator {
// make believe vals
ctre::phoenix6::configs::Slot0Configs slot0 =
    ctre::phoenix6::configs::Slot0Configs{}
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
        .WithMotionMagicJerk(1100_rpm)
        .WithMotionMagicCruiseVelocity(80_rpm)
        .WithMotionMagicAcceleration(160_rpm);
ctre::phoenix6::configs::TalonFXConfiguration elevatorConfigs =
    ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(slot0)
        .WithMotionMagic(magicMotionConfigs)
        .WithCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs{}
                               .WithStatorCurrentLimit(10_A)
                               .WithStatorCurrentLimitEnable(true));

} // namespace Elevator

} // namespace Constants