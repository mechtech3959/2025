#pragma once

#include "ctre/phoenix6/core/CoreCANcoder.hpp"
#include <ctre/phoenix6/Pigeon2.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
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
static constexpr units::scalar_t coupleRatio = 3.5714285714285716;
static constexpr units::turn_t FrontLeftEncoderOffset = 0.2080078125_tr;
static constexpr units::turn_t FrontRightEncoderOffset = -0.138916015625_tr;
static constexpr units::turn_t BackLeftEncoderOffset = -0.048583984375_tr;
static constexpr units::turn_t BackRightEncoderOffset = 0.2001953125_tr;

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
// The closed-loop output type to use for the steer motors;
// This affects the PID/FF gains for the steer motors
static constexpr ctre::phoenix6::swerve::ClosedLoopOutputType
    steerClosedLoopOutput =
        ctre::phoenix6::swerve::ClosedLoopOutputType::Voltage;
// The closed-loop output type to use for the drive motors;
// This affects the PID/FF gains for the drive motors
static constexpr ctre::phoenix6::swerve::ClosedLoopOutputType
    driveClosedLoopOutput =
        ctre::phoenix6::swerve::ClosedLoopOutputType::Voltage;

constexpr ctre::phoenix6::configs::CANcoderConfiguration encoderConfig =
    ctre::phoenix6::configs::CANcoderConfiguration{};

// configures constants for the drivetrain
constexpr ctre::phoenix6::swerve::SwerveModuleConstantsFactory moduleCreator =
    ctre::phoenix6::swerve::SwerveModuleConstantsFactory<
        ctre::phoenix6::configs::TalonFXConfiguration,
        ctre::phoenix6::configs::TalonFXConfiguration,
        ctre::phoenix6::configs::CANcoderConfiguration>{}
        .WithDriveMotorGearRatio(6.14)
        .WithSteerMotorGearRatio(12.8)
        .WithCouplingGearRatio(coupleRatio)
        .WithWheelRadius(4_in)
        .WithDriveMotorGains(ctre::phoenix6::configs::Slot0Configs{}
                                 .WithKP(0.1)
                                 .WithKI(0)
                                 .WithKD(0)
                                 .WithKS(0)
                                 .WithKV(0.124))
        .WithSteerMotorGains(
            ctre::phoenix6::configs::Slot0Configs{}
                .WithKP(7)
                .WithKI(0)
                .WithKD(0.5)
                .WithKS(0.1)
                .WithKV(1.91)
                .WithKA(0)
                .WithStaticFeedforwardSign(
                    ctre::phoenix6::signals::StaticFeedforwardSignValue::
                        UseClosedLoopSign))
        .WithDriveMotorClosedLoopOutput(driveClosedLoopOutput)
        .WithSteerMotorClosedLoopOutput(steerClosedLoopOutput)
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
    moduleCreator.CreateModuleConstants(7, 8, 12, FrontLeftEncoderOffset,
                                        -0.6064_m, 0.3429_m, false, false,
                                        false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants frontRightModule =
    moduleCreator.CreateModuleConstants(1, 3, 13, FrontRightEncoderOffset,
                                        0.6064_m, 0.3429_m, true, false, false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants rearLeftModule =
    moduleCreator.CreateModuleConstants(5, 6, 14, BackLeftEncoderOffset,
                                        -0.6064_m, -0.3429_m, false, false,
                                        false);
constexpr ctre::phoenix6::swerve::SwerveModuleConstants rearRightModule =
    moduleCreator.CreateModuleConstants(2, 4, 15, BackRightEncoderOffset,
                                        0.6064_m, -0.3429_m, true, false,
                                        false);
constexpr ctre::phoenix6::swerve::SwerveDrivetrainConstants
    drivetrainConstants =
        ctre::phoenix6::swerve::SwerveDrivetrainConstants{}.WithPigeon2Id(
            pigeonID);
//! set to max constraints of swerve modules!
constexpr units::meters_per_second_t maxDriveSpeedMPS = 5.01_mps;
constexpr units::meters_per_second_t maxFOCDriveSpeedMPS = 4.78_mps;
}; // namespace swerve

// namespace odometry {
// ctre::phoenix6::hardware::Pigeon2 gyro{constants::kPigeonID};

// frc::SwerveDriveKinematics<4> m_kinematics;
// }; // namespace odometry
}; // namespace constants
