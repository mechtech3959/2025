#pragma once

#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/Command.h>
#include <frc2/command/button/CommandXboxController.h>
#include <pathplanner/lib/auto/AutoBuilder.h>

#include "Constants.hpp"
#include "subsystems/DriveSubsystem.hpp"

class RobotContainer final {
public:
  RobotContainer();
  void ConfigureButtonBindings();
  void TeleopInit();
  frc2::Command *GetAutonomousCommand();

private:
  frc2::CommandXboxController driverController{constants::driverControllerPort};
  DriveSubsystem driveSubsystem;

  frc::SendableChooser<frc2::Command *> autoChooser =
      pathplanner::AutoBuilder::buildAutoChooser();
};
