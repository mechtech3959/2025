#pragma once

#include <ctre/phoenix6/Pigeon2.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <ctre/phoenix6/swerve/SwerveDrivetrainConstants.hpp>
#include <ctre/phoenix6/swerve/SwerveModuleConstants.hpp>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <units/acceleration.h>

namespace constants {
constexpr char canBus[] = "rio";
constexpr int driverControllerPort = 0;
constexpr int kPigeonID = 9;

namespace swerve {
constexpr double translationGain = 5.0;
constexpr double rotationGain = 1.5;

constexpr ctre::phoenix6::swerve::SwerveModuleConstantsFactory moduleCreator =
    ctre::phoenix6::swerve::SwerveModuleConstantsFactory{}
        .WithDriveMotorGearRatio(6.75)
        .WithSteerMotorGearRatio(12.8)
        .WithWheelRadius(1.97_in)
        .WithDriveMotorGains(ctre::phoenix6::configs::Slot0Configs{})
        .WithSteerMotorGains(ctre::phoenix6::configs::Slot0Configs{});

// MK4 L2 swerve modules have a max free speed of 16.5 fps without FOC
// FOC = 15.7 fps
constexpr ctre::phoenix6::swerve::SwerveModuleConstants frontLeftModule =
    moduleCreator.CreateModuleConstants(7, 8, 12, 77.8_deg, 0_m, 0_m, false,
                                        false, false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants frontRightModule =
    moduleCreator.CreateModuleConstants(1, 3, 13, -47.9_deg, 19.35_in, 0_m,
                                        false, false, false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants rearLeftModule =
    moduleCreator.CreateModuleConstants(5, 6, 14, -17.45_deg, 0_m, 24.35_in,
                                        false, false, false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants rearRightModule =
    moduleCreator.CreateModuleConstants(2, 4, 15, 72.06_deg, 19.35_in, 24.35_in,
                                        false, false, false);
constexpr ctre::phoenix6::swerve::SwerveDrivetrainConstants
    drivetrainConstants =
        ctre::phoenix6::swerve::SwerveDrivetrainConstants{}.WithPigeon2Id(
            kPigeonID);
//! set to max constraints of swerve modules!
constexpr double maxDriveSpeedMPS = 5.01;
constexpr double maxFOCDriveSpeedMPS = 4.78;
}; // namespace swerve

// namespace odometry {
// ctre::phoenix6::hardware::Pigeon2 gyro{constants::kPigeonID};

// frc::SwerveDriveKinematics<4> m_kinematics;
// }; // namespace odometry
}; // namespace constants
