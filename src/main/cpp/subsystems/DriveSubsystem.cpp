#include <ctre/phoenix6/swerve/SwerveRequest.hpp>
#include <frc/DriverStation.h>
#include <pathplanner/lib/auto/AutoBuilder.h>
#include <pathplanner/lib/controllers/PPHolonomicDriveController.h>

#include "subsystems/DriveSubsystem.hpp"

DriveSubsystem::DriveSubsystem() {
  drivetrain.GetOdometryThread().Start();

  pathplanner::RobotConfig config = pathplanner::RobotConfig::fromGUISettings();

  pathplanner::AutoBuilder::configure(
      [this]() { return drivetrain.GetState().Pose; },
      [this](frc::Pose2d pose) { return drivetrain.ResetPose(pose); },
      [this]() { return drivetrain.GetState().Speeds; },
      [this](frc::ChassisSpeeds speeds, pathplanner::DriveFeedforwards feeds) {
        drivetrain.SetControl(
            ctre::phoenix6::swerve::requests::ApplyRobotSpeeds{}
                .WithSpeeds(speeds)
                .WithWheelForceFeedforwardsX(feeds.robotRelativeForcesX)
                .WithWheelForceFeedforwardsY(feeds.robotRelativeForcesY));
      },
      std::make_shared<pathplanner::PPHolonomicDriveController>(
          pathplanner::PIDConstants(0, 0, 0),
          pathplanner::PIDConstants(0, 0, 0)),
      config,
      []() {
        return frc::DriverStation::GetAlliance().value() ==
               frc::DriverStation::Alliance::kRed;
      },
      this);
}

void DriveSubsystem::Drive(units::meters_per_second_t velocityX,
                           units::meters_per_second_t velocityY,
                           units::radians_per_second_t rotationalRate) {
  isFieldCentric
      ? drivetrain.SetControl(ctre::phoenix6::swerve::requests::FieldCentric{}
                                  .WithVelocityX(velocityX)
                                  .WithVelocityY(velocityY)
                                  .WithRotationalRate(rotationalRate))
      : drivetrain.SetControl(ctre::phoenix6::swerve::requests::RobotCentric{}
                                  .WithVelocityX(velocityX)
                                  .WithVelocityY(velocityY)
                                  .WithRotationalRate(rotationalRate));
}
