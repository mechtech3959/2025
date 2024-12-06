#include <frc2/command/Commands.h>

#include "RobotContainer.hpp"

RobotContainer::RobotContainer() { driveSubsystem.StartOdometryThread(); }

void RobotContainer::Periodic() { driveSubsystem.State(); }

void RobotContainer::TeleopInit() {
  driveSubsystem.SetDefaultCommand(frc2::cmd::Run(
      [this] {
        driveSubsystem.Drive(
            driverController.GetLeftX(), driverController.GetLeftY(),
            driverController.GetRightX(), driverController.GetRightY());
      },
      {&driveSubsystem}));
}
