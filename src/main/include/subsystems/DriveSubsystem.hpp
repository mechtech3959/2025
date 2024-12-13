#pragma once

#include <ctre/phoenix6/swerve/SwerveDrivetrain.hpp>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SubsystemBase.h>

#include "Constants.hpp"

class DriveSubsystem : public frc2::SubsystemBase {
public:
  DriveSubsystem();

  void SetControl(ctre::phoenix6::swerve::requests::SwerveRequest &&request) {
    drivetrain.SetControl(request);
  };

  bool isFieldCentric = false;

  frc2::InstantCommand invert{[this] { isFieldCentric = !isFieldCentric; }, {}};

private:
  ctre::phoenix6::swerve::SwerveDrivetrain drivetrain{
      constants::swerve::drivetrainConstants,
      constants::swerve::frontLeftModule, constants::swerve::frontRightModule,
      constants::swerve::rearLeftModule, constants::swerve::rearRightModule};
};
