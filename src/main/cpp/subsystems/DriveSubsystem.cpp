#include "subsystems/DriveSubsystem.hpp"
#include <ctre/phoenix6/swerve/SwerveModule.hpp>
#include <ctre/phoenix6/swerve/SwerveRequest.hpp>

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
void DriveSubsystem::startOdm() { Drivetrain.GetOdometryThread().Start(); };
// TODO: make a center point for single point pose
void DriveSubsystem::State() {
  double fl[2] = {constants::swerve::frontLeftModule.LocationX(),
                  constants::swerve::frontLeftModule.LocationY()};
  double fr[2] = {constants::swerve::frontRightModule.LocationX(),
                  constants::swerve::frontRightModule.LocationY()};
  double bl[2] = {constants::swerve::rearLeftModule.LocationX(),
                  constants::swerve::rearLeftModule.LocationY()};
  double br[2] = {constants::swerve::rearRightModule.LocationX(),
                  constants::swerve::rearRightModule.LocationY()};
  frc::Rotation3d rot = Drivetrain.GetRotation3d();
};
