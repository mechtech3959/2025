#pragma once

#include <frc2/command/button/CommandXboxController.h>

#include "Constants.hpp"
#include "subsystems/DriveSubsystem.hpp"

class RobotContainer {
public:
  RobotContainer();
  void ConfigureButtonBindings();
  void Periodic();
  void TeleopInit();

private:
  frc2::CommandXboxController driverController{constants::driverControllerPort};
  DriveSubsystem driveSubsystem;
};
