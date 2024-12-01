#include <frc2/command/Commands.h>

#include "RobotContainer.hpp"
void RobotContainer::RobotPeriodic() { driveSubsystem.startOdm(); }
void RobotContainer::TeleopInit() {
  driveSubsystem.SetDefaultCommand(frc2::cmd::Run(
      [this] {
        driveSubsystem.Drive(
            driverController.GetLeftX(), driverController.GetLeftY(),
            driverController.GetRightX(), driverController.GetRightY());
      },
      {&driveSubsystem}));
}
