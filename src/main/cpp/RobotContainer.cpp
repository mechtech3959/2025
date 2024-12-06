#include <frc2/command/Commands.h>
#include <units/angular_velocity.h>
#include <units/velocity.h>

#include "RobotContainer.hpp"
#include "frc2/command/InstantCommand.h"

RobotContainer::RobotContainer() {
  driveSubsystem.StartOdometryThread();
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  driverController.Start().OnTrue(&driveSubsystem.invert);
}

void RobotContainer::Periodic() { driveSubsystem.State(); }

void RobotContainer::TeleopInit() {
  driveSubsystem.SetDefaultCommand(frc2::cmd::Run(
      [this] {
        driveSubsystem.Drive(driverController.GetLeftX() * 1_m / 1_s,
                             driverController.GetLeftY() * 1_m / 1_s,
                             driverController.GetRightX() * 1_rad / 1_s);
      },
      {&driveSubsystem}));
}
