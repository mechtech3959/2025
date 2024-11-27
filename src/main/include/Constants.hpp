#pragma once

#include <ctre/phoenix6/swerve/SwerveDrivetrainConstants.hpp>
#include <ctre/phoenix6/swerve/SwerveModuleConstants.hpp>
#include <ctre/phoenix6/swerve/utility/Geometry.hpp>
#include <ctre/phoenix6/swerve/utility/Kinematics.hpp>
#include <ctre/phoenix6/Pigeon2.hpp>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry3d.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Pose3d.h>
 

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
namespace odometry{
    ctre::phoenix6::hardware::Pigeon2 m_gyro{9};
    frc::SwerveDriveKinematics<4> m_kinematics;
    


}; // namespace odemetry
}; // namespace constants
