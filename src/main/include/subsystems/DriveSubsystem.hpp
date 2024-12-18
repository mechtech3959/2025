#pragma once

#include <ctre/phoenix6/swerve/SwerveDrivetrain.hpp>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SubsystemBase.h>

#include "Constants.hpp"
#include "ctre/phoenix6/configs/Configs.hpp"

class DriveSubsystem : public frc2::SubsystemBase {
public:
  DriveSubsystem();

  void SetControl(ctre::phoenix6::swerve::requests::SwerveRequest &&request) {
    drivetrain.SetControl(request);
  };
  // function to dynamically change current limits TODO: fix this
  void
  setCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs driveLimit,
                   ctre::phoenix6::configs::CurrentLimitsConfigs turnLimit) {
    for (int i = 0; i < 4; ++i) {
      drivetrain.GetModule(i).GetDriveMotor().GetConfigurator().Apply(
          driveLimit);
      drivetrain.GetModule(i).GetSteerMotor().GetConfigurator().Apply(
          turnLimit);
    }
  };
  // prepares requests for drive control mode switch

  bool isFieldCentric = false;

  frc2::InstantCommand invert{[this] { isFieldCentric = !isFieldCentric; }, {}};

private:
  // creates drivetrain constructor
  ctre::phoenix6::swerve::SwerveDrivetrain drivetrain{
      constants::swerve::drivetrainConstants,
      constants::swerve::frontLeftModule, constants::swerve::frontRightModule,
      constants::swerve::rearLeftModule, constants::swerve::rearRightModule};
};
