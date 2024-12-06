#include <array>
#include <ctre/phoenix6/swerve/SwerveModule.hpp>
#include <ctre/phoenix6/swerve/SwerveRequest.hpp>
#include <units/angular_velocity.h>
#include <units/velocity.h>

#include "subsystems/DriveSubsystem.hpp"

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
};

void DriveSubsystem::StartOdometryThread() {
  drivetrain.GetOdometryThread().Start();
};

void DriveSubsystem::State() {
  frc::Rotation3d rotation = drivetrain.GetRotation3d();
  frc::Pose2d pose = drivetrain.GetState().Pose;
  frc::ChassisSpeeds speed = drivetrain.GetState().Speeds;
};
