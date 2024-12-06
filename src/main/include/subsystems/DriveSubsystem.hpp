#pragma once

#include <ctre/phoenix6/swerve/SwerveDrivetrain.hpp>
#include <frc/XboxController.h>
#include <frc2/command/SubsystemBase.h>
#include <units/angular_velocity.h>
#include <units/velocity.h>

#include "Constants.hpp"

class DriveSubsystem : public frc2::SubsystemBase {
public:
  void Drive(units::meters_per_second_t velocityX,
             units::meters_per_second_t velocityY,
             units::radians_per_second_t rotationalRate);
  void DriveControlSelector(frc::XboxController controller);
  void StartOdometryThread();
  void State();

  bool isFieldCentric = false;

private:
  ctre::phoenix6::swerve::SwerveDrivetrain drivetrain{
      constants::swerve::drivetrainConstants,
      constants::swerve::frontLeftModule, constants::swerve::frontRightModule,
      constants::swerve::rearLeftModule, constants::swerve::rearRightModule};
};
