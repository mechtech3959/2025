#pragma once

#include "ctre/phoenix6/swerve/SwerveDrivetrainConstants.hpp"
#include "ctre/phoenix6/swerve/SwerveModuleConstants.hpp"

namespace constants {
constexpr char canBus[] = "rio";
constexpr int driverControllerPort = 0;

namespace swerve {
constexpr ctre::phoenix6::swerve::SwerveModuleConstants frontLeftModule =
    ctre::phoenix6::swerve::SwerveModuleConstantsFactory{}
        .CreateModuleConstants(7, 8, 12, 77.8_deg, 0_m, 0_m, false, false,
                               false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants frontRightModule =
    ctre::phoenix6::swerve::SwerveModuleConstantsFactory{}
        .CreateModuleConstants(1, 3, 13, -47.9_deg, 19.35_in, 0_m, false, false,
                               false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants rearLeftModule =
    ctre::phoenix6::swerve::SwerveModuleConstantsFactory{}
        .CreateModuleConstants(5, 6, 14, -17.45_deg, 0_m, 24.35_in, false,
                               false, false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants rearRightModule =
    ctre::phoenix6::swerve::SwerveModuleConstantsFactory{}
        .CreateModuleConstants(2, 4, 15, 72.06_deg, 19.35_in, 24.35_in, false,
                               false, false);
constexpr ctre::phoenix6::swerve::SwerveDrivetrainConstants
    drivetrainConstants{};
}; // namespace swerve
}; // namespace constants
