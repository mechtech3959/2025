// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Telemetry.h"
#include "subsystems/ClawSubsystem.h"
#include "subsystems/CommandSwerveDrivetrain.h"
#include "subsystems/ElevatorSubsystem.h"
#include "subsystems/LimeLightSubsystem.h"
#include <frc/smartdashboard/Field2d.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Command.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include <pathplanner/lib/auto/AutoBuilder.h>
#include <pathplanner/lib/commands/PathPlannerAuto.h>
#include <pathplanner/lib/path/PathPlannerPath.h>

#include <frc/XboxController.h>
#include <frc2/command/InstantCommand.h>
#include <pathplanner/lib/auto/NamedCommands.h>

class RobotContainer {
private:
  units::meters_per_second_t MaxSpeed =
      TunerConstants::kSpeedAt12Volts; // kSpeedAt12Volts desired top speed
  units::radians_per_second_t MaxAngularRate = 1.5_tps;
  //  0.75_tps;  3/4 of a rotation per second max angular velocity

  /* Setting up bindings for necessary control of the swerve drive platform */
  swerve::requests::FieldCentric drive =
      swerve::requests::FieldCentric{}
          .WithDeadband(MaxSpeed * 0.05) // 0.1
          .WithRotationalDeadband(MaxAngularRate *
                                  0.05) // 0.1 Add a 10% deadband
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
  frc2::CommandXboxController driverJoystick{0};
  frc::XboxController systemJoystick{1};

public:
  subsystems::Claw subsystemClaw;
  subsystems::Elevator subsystemElevator;
  subsystems::CommandSwerveDrivetrain drivetrain{
      TunerConstants::CreateDrivetrain()};

  // subsystems::LimeLight frontLimeLight{"limelight-front"};
  // subsystems::LimeLight backLimeLight{"limelight-back"};
  frc::Pose2d visionEstimate;

  std::shared_ptr<pathplanner::PathPlannerPath> SetAutonomousPath();
  std::unique_ptr<frc2::Command> exampleAuto;
  frc::SendableChooser<frc2::Command *> paths =
      pathplanner::AutoBuilder::buildAutoChooser("Def");
  std::string autopose;
  bool algea = false;
  frc2::InstantCommand outtakeCoral{[this] { subsystemClaw.percentOut(-0.2); },
                                    {}};
  // frc2::InstantCommand feedStop{[this]{subsystemClaw.percentOut(0);},{}};
  frc2::InstantCommand setANgle{[this] { subsystemClaw.setAxis(20_deg); }, {}};

  RobotContainer();
  frc2::CommandPtr seta();
  frc2::CommandPtr feed();
  frc2::CommandPtr feedStop();
  frc2::Command *GetAutonomousCommand();
  void GetStartingPose();

  void ConfigureTeli();
  void ConfigureBindings();
  void ConfigureDashboard();
  void RobotPeriodic();
};
