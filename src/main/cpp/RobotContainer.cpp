#include "RobotContainer.hpp"

#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() { ConfigureBindings(); }

void RobotContainer::ConfigureBindings() {}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return frc2::cmd::Print("No autonomous command configured");
}

void RobotContainer::TeleopInit() {
  driveSubsystem.SetDefaultCommand(frc2::cmd::Run(
      [this] {
        driveSubsystem.Drive(
            driverController.GetLeftX(), driverController.GetLeftY(),
            driverController.GetRightX(), driverController.GetRightY());
      },
      {&driveSubsystem}));
}
