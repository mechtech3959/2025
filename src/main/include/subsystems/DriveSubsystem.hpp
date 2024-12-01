#pragma once

#include <ctre/phoenix6/swerve/SwerveDrivetrain.hpp>
#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>

#include "Constants.hpp"

class DriveSubsystem : public frc2::SubsystemBase
{
public:
  void Drive(double x1, double y1, double x2, double y2);
  void DriveFOC(double x1, double y1, double x2, double y2, frc::Rotation2d operatorAngle);
  void DriveControlSelector(frc::XboxController controller);

private:
  ctre::phoenix6::swerve::SwerveDrivetrain Drivetrain{
      constants::swerve::drivetrainConstants,
      constants::swerve::frontLeftModule, constants::swerve::frontRightModule,
      constants::swerve::rearLeftModule, constants::swerve::rearRightModule};
};
