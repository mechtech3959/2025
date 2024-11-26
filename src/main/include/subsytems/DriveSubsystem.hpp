#pragma once

#include "Constants.hpp"
#include "ctre/phoenix6/swerve/SwerveDrivetrainConstants.hpp"
#include "ctre/phoenix6/swerve/SwerveModuleConstants.hpp"
#include <ctre/phoenix6/swerve/SwerveDrivetrain.hpp>
#include <frc2/command/SubsystemBase.h>

class DriveSubsystem : public frc2::SubsystemBase {
public:
  DriveSubsystem();

private:
  ctre::phoenix6::swerve::SwerveDrivetrain Drivetrain{
      ctre::phoenix6::swerve::SwerveDrivetrainConstants{},
      constants::swerve::frontLeftModule, constants::swerve::frontRightModule,
      constants::swerve::rearLeftModule, constants::swerve::rearRightModule};
};
