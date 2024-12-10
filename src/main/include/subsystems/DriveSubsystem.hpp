#pragma once

#include <ctre/phoenix6/swerve/SwerveDrivetrain.hpp>
#include <frc/XboxController.h>
#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SubsystemBase.h>
#include <units/angular_velocity.h>
#include <units/velocity.h>

#include "Constants.hpp"

class DriveSubsystem : public frc2::SubsystemBase {
public:
  DriveSubsystem();
  void Drive(units::meters_per_second_t velocityX,
             units::meters_per_second_t velocityY,
             units::radians_per_second_t rotationalRate);

  frc2::InstantCommand invert{[this] { isFieldCentric = !isFieldCentric; }, {}};

private:
  bool isFieldCentric = false;

  ctre::phoenix6::swerve::SwerveDrivetrain drivetrain{
      constants::swerve::drivetrainConstants,
      constants::swerve::frontLeftModule, constants::swerve::frontRightModule,
      constants::swerve::rearLeftModule, constants::swerve::rearRightModule};
};
