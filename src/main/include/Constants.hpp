#pragma once

#include "ctre/phoenix6/swerve/SwerveDrivetrain.hpp"
#include "units/base.h"
#include "units/moment_of_inertia.h"
#include <ctre/phoenix6/Pigeon2.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <ctre/phoenix6/sim/CANcoderSimState.hpp>
#include <ctre/phoenix6/sim/ChassisReference.hpp>
#include <ctre/phoenix6/sim/Pigeon2SimState.hpp>
#include <ctre/phoenix6/sim/TalonFXSimState.hpp>
#include <ctre/phoenix6/swerve/SimSwerveDrivetrain.hpp>
#include <ctre/phoenix6/swerve/SwerveDrivetrainConstants.hpp>
#include <ctre/phoenix6/swerve/SwerveModuleConstants.hpp>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <units/acceleration.h>
#include <units/current.h>
#include <units/voltage.h>

namespace constants {
// can bus types  "rio" TODO: check name of CANivore "can"
constexpr char canBus[] = "rio";
constexpr int driverControllerPort = 0;
constexpr int pigeonID = 9;

namespace swerve {
constexpr double translationGain = 5.0;
constexpr double rotationGain = 1.5;

// puts a limit on the current draw to avoid brownout
constexpr ctre::phoenix6::configs::CurrentLimitsConfigs driveCurrentLimit =
    ctre::phoenix6::configs::CurrentLimitsConfigs{}.WithSupplyCurrentLimit(
        units::current::ampere_t(40));
constexpr ctre::phoenix6::configs::CurrentLimitsConfigs turnCurrentLimit =
    ctre::phoenix6::configs::CurrentLimitsConfigs{}.WithSupplyCurrentLimit(
        units::current::ampere_t(20));

constexpr ctre::phoenix6::configs::TalonFXConfiguration driveMotorConfig =
    ctre::phoenix6::configs::TalonFXConfiguration{}.WithCurrentLimits(
        driveCurrentLimit);
constexpr ctre::phoenix6::configs::TalonFXConfiguration turnMotorConfig =
    ctre::phoenix6::configs::TalonFXConfiguration{}.WithCurrentLimits(
        turnCurrentLimit);

// configures constants for the drivetrain
constexpr ctre::phoenix6::swerve::SwerveModuleConstantsFactory moduleCreator =
    ctre::phoenix6::swerve::SwerveModuleConstantsFactory{}
        .WithDriveMotorGearRatio(6.75)
        .WithSteerMotorGearRatio(12.8)
        .WithWheelRadius(1.97_in)
        .WithDriveMotorGains(ctre::phoenix6::configs::Slot0Configs{})
        .WithSteerMotorGains(ctre::phoenix6::configs::Slot0Configs{})
        .WithDriveMotorInitialConfigs(driveMotorConfig)
        .WithSteerMotorInitialConfigs(turnMotorConfig);

// MK4 L2 swerve modules have a max free speed of 16.5 fps without FOC
// FOC = 15.7 fps
// TODO: configure encoder offsets properly
// TODO: measure wheel to wheel/ wheel to center for most accurate results
// Robot dimensions are 32x27 last time i checked. That would make the center
// point 16x13.5 inches METERS: 0.8128x0.6858  0.4064x0.3429 0.4064x0.3429 is
// considered th origin (0,0)
constexpr ctre::phoenix6::swerve::SwerveModuleConstants frontLeftModule =
    moduleCreator.CreateModuleConstants(7, 8, 12, 77.8_deg, -0.6064_m, 0.3429_m,
                                        false, false, false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants frontRightModule =
    moduleCreator.CreateModuleConstants(1, 3, 13, -47.9_deg, 0.6064_m, 0.3429_m,
                                        false, false, false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants rearLeftModule =
    moduleCreator.CreateModuleConstants(5, 6, 14, -17.45_deg, -0.6064_m,
                                        -0.3429_m, false, false, false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants rearRightModule =
    moduleCreator.CreateModuleConstants(2, 4, 15, 72.06_deg, 0.6064_m,
                                        -0.3429_m, false, false, false);
constexpr ctre::phoenix6::swerve::SwerveDrivetrainConstants
    drivetrainConstants =
        ctre::phoenix6::swerve::SwerveDrivetrainConstants{}.WithPigeon2Id(
            pigeonID);
//! set to max constraints of swerve modules!
constexpr double maxDriveSpeedMPS = 5.01;
constexpr double maxFOCDriveSpeedMPS = 4.78;
}; // namespace swerve
namespace sim {
// TODO figure out the correct values/stupid suffixes

constexpr units::scalar_t driveGearing = 6.75;
// test var
constexpr units::kilogram_square_meter_t driveInertia =
    units::kilogram_square_meter_t(2);
constexpr units::volt_t driveFrictionVoltage = 12_V;
constexpr bool driveMotorInverted = false;
constexpr units::scalar_t steerGearing = 12.8;
// TEST var
constexpr units::kilogram_square_meter_t steerInertia =
    units::kilogram_square_meter_t(2);
constexpr units::volt_t steerFrictionVoltage = 12_V;
constexpr bool steerMotorInverted = false;
constexpr bool cancoderInverted = false;
}; // namespace sim

// namespace odometry {
// ctre::phoenix6::hardware::Pigeon2 gyro{constants::kPigeonID};

// frc::SwerveDriveKinematics<4> m_kinematics;
// }; // namespace odometry
}; // namespace constants
