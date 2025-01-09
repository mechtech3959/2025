#pragma once

#include <ctre/phoenix6/configs/Configs.hpp>
#include <ctre/phoenix6/swerve/SwerveDrivetrain.hpp>
#include <frc/geometry/Translation2d.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SubsystemBase.h>

#include "Constants.hpp"
#include "ctre/phoenix6/CANcoder.hpp"
#include "ctre/phoenix6/TalonFX.hpp"
#include "ctre/phoenix6/swerve/SwerveModule.hpp"

class DriveSubsystem : public frc2::SubsystemBase {
public:
  DriveSubsystem();

  // function to dynamically change current limits
  void
  SetCurrentLimits(ctre::phoenix6::configs::CurrentLimitsConfigs driveLimit,
                   ctre::phoenix6::configs::CurrentLimitsConfigs turnLimit) {
    for (const std::unique_ptr<ctre::phoenix6::swerve::SwerveModule<
             ctre::phoenix6::hardware::TalonFX,
             ctre::phoenix6::hardware::TalonFX,
             ctre::phoenix6::hardware::CANcoder>> &module :
         drivetrain.GetModules()) {
      module->GetDriveMotor().GetConfigurator().Apply(driveLimit);
      module->GetSteerMotor().GetConfigurator().Apply(turnLimit);
    }
  };
  bool isOdomValid() { return (drivetrain.IsOdometryValid()); }

  // robot position
  frc::Pose2d GetPose() { return (drivetrain.GetState().Pose); };
  // individual swerve module positions
  std::vector<frc::Translation2d> SwerveModulePose() {
    return (drivetrain.GetModuleLocations());
  };

  // function to swap drive modes
  bool isFieldCentric = false;

  frc2::InstantCommand invert{[this] { isFieldCentric = !isFieldCentric; }, {}};

  // creates drivetrain constructor
  ctre::phoenix6::swerve::SwerveDrivetrain<ctre::phoenix6::hardware::TalonFX,
                                           ctre::phoenix6::hardware::TalonFX,
                                           ctre::phoenix6::hardware::CANcoder>
      drivetrain{constants::swerve::drivetrainConstants,
                 constants::swerve::frontLeftModule,
                 constants::swerve::frontRightModule,
                 constants::swerve::rearLeftModule,
                 constants::swerve::rearRightModule};
};
