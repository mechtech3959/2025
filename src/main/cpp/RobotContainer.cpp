#include <frc/geometry/Pose2d.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "RobotContainer.hpp"

void RobotContainer::TeleopInit() {
  // Swaps control modes
  driverController.Start().OnTrue(&driveSubsystem.invert);
  // controller values multiplied into velocity
  units::meters_per_second_t velocityX =
      driverController.GetLeftX() * 1_m / 1_s;
  units::meters_per_second_t velocityY =
      driverController.GetLeftY() * 1_m / 1_s;
  units::radians_per_second_t rotationalRate =
      driverController.GetRightX() * 1_rad / 1_s;
  // drive command with if statements to switch modes
  driveSubsystem.SetDefaultCommand(frc2::cmd::Run(
      [this, velocityX, velocityY, rotationalRate] {
        driveSubsystem.isFieldCentric
            ? driveSubsystem.SetControl(
                  ctre::phoenix6::swerve::requests::FieldCentric{}
                      .WithVelocityX(velocityX)
                      .WithVelocityY(velocityY)
                      .WithRotationalRate(rotationalRate))
            : driveSubsystem.SetControl(
                  ctre::phoenix6::swerve::requests::RobotCentric{}
                      .WithVelocityX(velocityX)
                      .WithVelocityY(velocityY)
                      .WithRotationalRate(rotationalRate));
      },
      {&driveSubsystem}));
}
// Runs every 20 ms
void RobotContainer::RobotPeriodic() {
  // updates field robot pose as the pose of the drive position
  field.SetRobotPose(driveSubsystem.GetPose());
}

frc2::CommandPtr RobotContainer::StartCommands() {
  return (frc2::cmd::Run([this] {
    frc::Pose2d pose = driveSubsystem.GetPose();
    std::vector<frc::Translation2d> modPoses =
        driveSubsystem.SwerveModulePose();
    // Robot Pose
    frc::SmartDashboard::PutNumber("Pose X", pose.X().value());
    frc::SmartDashboard::PutNumber("Pose Y", pose.Y().value());
    // position of each individual module
    //  TODO: Check module order FL FR BL BR
    frc::SmartDashboard::PutNumberArray("Pose FL", modPoses[0].ToVector());
    frc::SmartDashboard::PutNumberArray("Pose FR", modPoses[1].ToVector());
    frc::SmartDashboard::PutNumberArray("Pose BL", modPoses[2].ToVector());
    frc::SmartDashboard::PutNumberArray("Pose BR", modPoses[3].ToVector());
    // posts field on dashboard
    frc::SmartDashboard::PutData("Robot field translation ", &field);
  }));
}
