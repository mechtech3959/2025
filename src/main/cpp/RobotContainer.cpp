#include <frc2/command/Commands.h>

#include "RobotContainer.hpp"

RobotContainer::RobotContainer() { driveSubsystem.StartOdometryThread(); }

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
