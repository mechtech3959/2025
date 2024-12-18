#include <ctre/phoenix6/swerve/SwerveRequest.hpp>
#include <frc/DriverStation.h>
#include <pathplanner/lib/auto/AutoBuilder.h>
#include <pathplanner/lib/controllers/PPHolonomicDriveController.h>

#include "subsystems/DriveSubsystem.hpp"

DriveSubsystem::DriveSubsystem() {
  // starts position logging of robot
  drivetrain.GetOdometryThread().Start();
  // retrieves configs like height, weight, length, and width from path planner
  // graphical interface
  pathplanner::RobotConfig config = pathplanner::RobotConfig::fromGUISettings();
  // gathers all information about the drivetrain positioning, velocity, and
  // force constraints to move it
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
          // TODO: set PID values correctly
          pathplanner::PIDConstants(0, 0, 0),
          pathplanner::PIDConstants(0, 0, 0)),
      config,
      []() {
        return frc::DriverStation::GetAlliance().value() ==
               frc::DriverStation::Alliance::kRed;
      },
      this);
}
