#pragma once

#include <ctre/phoenix6/configs/Configs.hpp>
#include <ctre/phoenix6/swerve/SwerveDrivetrain.hpp>
#include <frc/geometry/Translation2d.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SubsystemBase.h>

#include "Constants.hpp"

class DriveSubsystem : public frc2::SubsystemBase {
public:
  DriveSubsystem();

  void SetControl(ctre::phoenix6::swerve::requests::SwerveRequest &&request) {
    drivetrain.SetControl(request);
  };

  // function to dynamically change current limits
  void
  setCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs driveLimit,
                   ctre::phoenix6::configs::CurrentLimitsConfigs turnLimit) {
    for (const std::unique_ptr<ctre::phoenix6::swerve::SwerveModule> &module :
         drivetrain.GetModules()) {
      module->GetDriveMotor().GetConfigurator().Apply(driveLimit);
      module->GetSteerMotor().GetConfigurator().Apply(turnLimit);
    }
  };

  frc::Pose2d getPose() { return (drivetrain.GetState().Pose); };
  std::vector<frc::Translation2d> swerveModPose() {
    return (drivetrain.GetModuleLocations());
  };
  bool isFieldCentric = false;

  frc2::InstantCommand invert{[this] { isFieldCentric = !isFieldCentric; }, {}};

private:
  // creates drivetrain constructor
  ctre::phoenix6::swerve::SwerveDrivetrain drivetrain{
      constants::swerve::drivetrainConstants,
      constants::swerve::frontLeftModule, constants::swerve::frontRightModule,
      constants::swerve::rearLeftModule, constants::swerve::rearRightModule};
};
