#pragma once

<<<<<<< HEAD
=======
#include <frc/smartdashboard/Field2d.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
>>>>>>> a469510 (headers, pid consts,field init)
#include <frc2/command/Command.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include <pathplanner/lib/auto/AutoBuilder.h>

#include "Constants.hpp"
#include "subsystems/DriveSubsystem.hpp"

class RobotContainer final {
public:
  RobotContainer();

  void TeleopInit();

  frc2::Command *GetAutonomousCommand() { return autoChooser.GetSelected(); };

  frc2::CommandPtr StartCommands();

  frc::Field2d field;

private:
  DriveSubsystem driveSubsystem;

  frc2::CommandXboxController driverController{constants::driverControllerPort};

  frc::SendableChooser<frc2::Command *> autoChooser =
      pathplanner::AutoBuilder::buildAutoChooser();
};
