#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>

#include "Constants.hpp"
#include "subsystems/DriveSubsystem.hpp"

class RobotContainer {
public:
  RobotContainer();

  frc2::CommandPtr GetAutonomousCommand();

  void TeleopInit();

private:
  void ConfigureBindings();

  frc2::CommandXboxController driverController{constants::driverControllerPort};
  DriveSubsystem driveSubsystem;
};
