#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Commands.h>
#include <frc2/command/InstantCommand.h>
#include <pathplanner/lib/auto/AutoBuilder.h>
#include <units/angular_velocity.h>
#include <units/velocity.h>

#include "RobotContainer.hpp"

RobotContainer::RobotContainer() {
  ConfigureButtonBindings();

  frc::SmartDashboard::PutData("Auto Chooser", &autoChooser);
}

void RobotContainer::ConfigureButtonBindings() {
  driverController.Start().OnTrue(&driveSubsystem.invert);
}

void RobotContainer::TeleopInit() {
  driveSubsystem.SetDefaultCommand(frc2::cmd::Run(
      [this] {
        driveSubsystem.Drive(driverController.GetLeftX() * 1_m / 1_s,
                             driverController.GetLeftY() * 1_m / 1_s,
                             driverController.GetRightX() * 1_rad / 1_s);
      },
      {&driveSubsystem}));
}
