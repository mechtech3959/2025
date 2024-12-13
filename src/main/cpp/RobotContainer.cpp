#include <frc/smartdashboard/SmartDashboard.h>
#include <pathplanner/lib/auto/AutoBuilder.h>

#include "RobotContainer.hpp"

RobotContainer::RobotContainer() {
  driverController.Start().OnTrue(&driveSubsystem.invert);

  frc::SmartDashboard::PutData("Auto Chooser", &autoChooser);
}

void RobotContainer::TeleopInit() {
  units::meters_per_second_t velocityX =
      driverController.GetLeftX() * 1_m / 1_s;
  units::meters_per_second_t velocityY =
      driverController.GetLeftY() * 1_m / 1_s;
  units::radians_per_second_t rotationalRate =
      driverController.GetRightX() * 1_rad / 1_s;

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
