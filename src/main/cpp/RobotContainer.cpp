#include <frc2/command/Commands.h>

#include "RobotContainer.hpp"

void RobotContainer::TeleopInit()
{
  driveSubsystem.SetDefaultCommand(frc2::cmd::Run(
      [this]
      {
        driveSubsystem.Drive(
            driverController.GetLeftX(), driverController.GetLeftY(),
            driverController.GetRightX(), driverController.GetRightY());
      },
      {&driveSubsystem}));
  driveSubsystem.SetDefaultCommand(frc2::cmd::Run(
      [this]
      {
         driveSubsystem.Drive(
          driverController.GetLeftX(), driverController.GetLeftY(),
          driverController.GetRightX(), driverController.GetRightY()); },
      {&driveSubsystem}));
}
