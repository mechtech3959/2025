#pragma once

#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include <pathplanner/lib/auto/AutoBuilder.h>

#include "Constants.hpp"
#include "subsystems/DriveSubsystem.hpp"

class RobotContainer {
public:
  RobotContainer();
  void ConfigureButtonBindings();
  void TeleopInit();

private:
  frc2::CommandXboxController driverController{constants::driverControllerPort};
  DriveSubsystem driveSubsystem;

  frc::SendableChooser<frc2::Command *> autoChooser =
      pathplanner::AutoBuilder::buildAutoChooser();
};
