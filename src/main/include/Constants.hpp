#pragma once

#include "ctre/phoenix6/swerve/SwerveModuleConstants.hpp"
namespace constants {
constexpr char CANBus[] = "rio";

namespace swerve {
ctre::phoenix6::swerve::SwerveModuleConstants frontLeftModule =
    ctre::phoenix6::swerve::SwerveModuleConstantsFactory{}
        .CreateModuleConstants(7, 8, 12, 0_tr, 0_m, 0_m, false, false, false);
ctre::phoenix6::swerve::SwerveModuleConstants frontRightModule =
    ctre::phoenix6::swerve::SwerveModuleConstantsFactory{}
        .CreateModuleConstants(1, 3, 13, 0_tr, 0_m, 0_m, false, false, false);
ctre::phoenix6::swerve::SwerveModuleConstants rearLeftModule =
    ctre::phoenix6::swerve::SwerveModuleConstantsFactory{}
        .CreateModuleConstants(5, 6, 14, 0_tr, 0_m, 0_m, false, false, false);
ctre::phoenix6::swerve::SwerveModuleConstants rearRightModule =
    ctre::phoenix6::swerve::SwerveModuleConstantsFactory{}
        .CreateModuleConstants(2, 4, 15, 0_tr, 0_m, 0_m, false, false, false);
}; // namespace swerve
}; // namespace constants
