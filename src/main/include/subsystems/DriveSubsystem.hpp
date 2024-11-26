#pragma once

#include "Constants.hpp"
#include "ctre/phoenix6/swerve/SwerveDrivetrainConstants.hpp"
#include "ctre/phoenix6/swerve/SwerveModuleConstants.hpp"
#include <ctre/phoenix6/swerve/SwerveDrivetrain.hpp>
#include <frc2/command/SubsystemBase.h>

class DriveSubsystem : public frc2::SubsystemBase {
public:
  void Drive(double x1, double y1, double x2, double y2);

private:
  ctre::phoenix6::swerve::SwerveDrivetrain Drivetrain{
      constants::swerve::drivetrainConstants,
      constants::swerve::frontLeftModule, constants::swerve::frontRightModule,
      constants::swerve::rearLeftModule, constants::swerve::rearRightModule};
};
