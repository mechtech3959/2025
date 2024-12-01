#include <ctre/phoenix6/swerve/SwerveRequest.hpp>

#include "subsystems/DriveSubsystem.hpp"

void DriveSubsystem::Drive(double x1, double y1, double x2, double y2) {
  Drivetrain.SetControl(ctre::phoenix6::swerve::requests::RobotCentric{}
                            .WithVelocityX(x1 * 1_m / 1_s)
                            .WithVelocityY(y1 * 1_m / 1_s)
                            .WithRotationalRate(x2 * 1_tr / 1_s));
};
void DriveSubsystem::DriveFOC(double x1, double y1, double x2, double y2,
                              frc::Rotation2d operatorAngle) {
  Drivetrain.SetControl(
      ctre::phoenix6::swerve::requests::FieldCentric{}
          .WithVelocityX(x1 * 1_m / 1_s)
          .WithVelocityY(y1 * 1_m / 1_s)
          .WithRotationalRate(x2 * 1_tr / 1_s)
          .WithForwardPerspective(ctre::phoenix6::swerve::requests::
                                      ForwardPerspectiveValue::BlueAlliance));
};
