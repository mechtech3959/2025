// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Telemetry.h"
#include "subsystems/CommandSwerveDrivetrain.h"
#include <frc/smartdashboard/Field2d.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include <pathplanner/lib/auto/AutoBuilder.h>
#include <pathplanner/lib/commands/PathPlannerAuto.h>
#include <pathplanner/lib/path/PathPlannerPath.h>

class RobotContainer {
private:
  units::meters_per_second_t MaxSpeed =
      TunerConstants::kSpeedAt12Volts; // kSpeedAt12Volts desired top speed
  units::radians_per_second_t MaxAngularRate =
      0.75_tps; // 3/4 of a rotation per second max angular velocity

  /* Setting up bindings for necessary control of the swerve drive platform */
  swerve::requests::FieldCentric drive =
      swerve::requests::FieldCentric{}
          .WithDeadband(MaxSpeed * 0.1)
          .WithRotationalDeadband(MaxAngularRate * 0.1) // Add a 10% deadband
          .WithDriveRequestType(
              swerve::DriveRequestType::
                  OpenLoopVoltage); // Use open-loop control for drive motors
  swerve::requests::SwerveDriveBrake brake{};
  swerve::requests::PointWheelsAt point{};
  swerve::requests::RobotCentric rDrive =
      swerve::requests::RobotCentric{}
          .WithDeadband(MaxSpeed * 0.1)
          .WithRotationalDeadband(MaxAngularRate * 0.1)
          .WithDriveRequestType(swerve::DriveRequestType::OpenLoopVoltage);
  /* Note: This must be constructed before the drivetrain, otherwise we need
   * to define a destructor to un-register the telemetry from the drivetrain
   */
  Telemetry logger{MaxSpeed};

  frc2::CommandXboxController joystick{0};

public:
  subsystems::CommandSwerveDrivetrain drivetrain{
      TunerConstants::CreateDrivetrain()};
  std::shared_ptr<pathplanner::PathPlannerPath> SetAutonomousPath();
  std::unique_ptr<frc2::Command> exampleAuto;

  frc::SendableChooser<frc2::Command *> paths =
      pathplanner::AutoBuilder::buildAutoChooser("defauto");
      std::string autopose;

  RobotContainer();

  frc2::Command* GetAutonomousCommand();
  void GetStartingPose();

  void ConfigureBindings();
  void ConfigureDashboard();
};
