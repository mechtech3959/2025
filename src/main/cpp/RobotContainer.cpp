// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() {
  pathplanner::NamedCommands::registerCommand(
      "coralangle",
      frc2::cmd::RunOnce([this] { subsystemClaw.setAxis(20_deg); }));
      pathplanner::NamedCommands::registerCommand(
      "zeroangle",
      frc2::cmd::RunOnce([this] { subsystemClaw.setAxis(0_deg); }));
       pathplanner::NamedCommands::registerCommand(
      "coralout",
      frc2::cmd::RunOnce([this] { subsystemClaw.percentOut(0.2); }));
  pathplanner::NamedCommands::registerCommand(
      "feedstop",
      frc2::cmd::RunOnce([this] { subsystemClaw.percentOut(0.0); }));
  pathplanner::NamedCommands::registerCommand(
      "intake", frc2::cmd::RunOnce([this] {
        if (subsystemClaw.hasCoral()) {
          subsystemClaw.percentOut(0);
          subsystemClaw.setAxis(20_deg);
        } else {
          subsystemClaw.setAxis(0_deg);
          subsystemClaw.percentOut(-0.2);
        }
      }));
      

  ConfigureBindings();
  // ConfigureDashboard();
  GetStartingPose();
}

void RobotContainer::ConfigureBindings() {
  // frontLimeLight.updateTracking();
  // backLimeLight.updateTracking();
  // drivetrain.AddVisionMeasurement(frontLimeLight.poseEst(),
  //                                 frontLimeLight.timestamp);
  // drivetrain.AddVisionMeasurement(backLimeLight.poseEst(),
  //                                 backLimeLight.timestamp);
  // Note that X is defined as forward according to WPILib convention,
  // and Y is defined as to the left according to WPILib convention.
  drivetrain.SetDefaultCommand(
      // Drivetrain will execute this command periodically
      drivetrain.ApplyRequest([this]() -> auto && {
        return drive
            .WithVelocityX(-driverJoystick.GetLeftY() *
                           MaxSpeed) // Drive forward with negative Y (forward)
            .WithVelocityY(-driverJoystick.GetLeftX() *
                           MaxSpeed) // Drive left with negative X (left)
            .WithRotationalRate(-driverJoystick.GetRightX() *
                                MaxAngularRate); // Drive counterclockwise with
        // negative X (left)
      }));
  /** driverJoystick.X().WhileTrue(drivetrain.ApplyRequest([this]() -> auto && {
     if (frontLimeLight.LLHasTarget) {
       return drive //.WithVelocityX(-limelight.turncmd * 1_mps);
           .WithRotationalRate(-frontLimeLight.turncmd * 0.3_tps);
     } else {
       return drive.WithRotationalRate(-driverJoystick.GetRightX() *
   MaxAngularRate);
     }
   }));*/

  driverJoystick.LeftBumper().WhileTrue(
      drivetrain.ApplyRequest([this]() -> auto && { return brake; }));
  driverJoystick.B().WhileTrue(drivetrain.ApplyRequest([this]() -> auto && {
    return point.WithModuleDirection(frc::Rotation2d{
        -driverJoystick.GetLeftY(), -driverJoystick.GetLeftX()});
  }));

  // Run SysId routines when holding back/start and X/Y.
  // Note that each routine should be run exactly once in a single log.
  /*
 (driverJoystick.Back() && driverJoystick.Y())
     .WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kForward));
  (driverJoystick.Back() && driverJoystick.X())
   .WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kReverse));
  (driverJoystick.Start() && driverJoystick.Y())
   .WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kForward));
(driverJoystick.Start() && driverJoystick.X())
   .WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kReverse));
*/
  // reset the field-centric heading on left bumper press
  driverJoystick.Start().OnTrue(
      drivetrain.RunOnce([this] { drivetrain.SeedFieldCentric(); }));

  drivetrain.RegisterTelemetry(
      [this](auto const &state) { logger.Telemeterize(state); });

  // driverJoystick.X().WhileTrue(&smartIntake);

  /*
  driverJoystick.B().WhileTrue(subsystemClaw.SysIdDynamic(frc2::sysid::kForward));
  driverJoystick.A().WhileTrue(subsystemClaw.SysIdDynamic(frc2::sysid::kReverse));
  driverJoystick.Y().WhileTrue(subsystemClaw.SysIdQuasistatic(frc2::sysid::kForward));
  driverJoystick.X().WhileTrue(subsystemClaw.SysIdQuasistatic(frc2::sysid::kReverse));

  driverJoystick.B().WhileTrue(subsystemElevator.SysIdDynamic(frc2::sysid::kForward));
  driverJoystick.A().WhileTrue(subsystemElevator.SysIdDynamic(frc2::sysid::kReverse));
  driverJoystick.Y().WhileTrue(subsystemElevator.SysIdQuasistatic(frc2::sysid::kForward));
  driverJoystick.X().WhileTrue(subsystemElevator.SysIdQuasistatic(frc2::sysid::kReverse));
  */

  // frc2::cmd::Run(smartIntake);
  // driverJoystick.X().WhileTrue(&smartIntake);
}
void RobotContainer::ConfigureDashboard() {
  logger.subsystemTelemeterize(subsystemClaw.clawLog,
                               subsystemElevator.elevatorLog);
  frc::SmartDashboard::PutData("autochooser", &paths);
}
void RobotContainer::ConfigureTeli() {
  if (systemJoystick.GetBackButtonPressed()) {
    if (algea == false) {

      algea = true;
    } else if (algea == true) {
      algea = false;
    }
  }
  frc::SmartDashboard::PutBoolean("alg", algea);
  if (driverJoystick.RightTrigger().Get()) {
    MaxSpeed = 0.5_mps;
    MaxAngularRate = 0.3_tps;
  } else {
    MaxSpeed = 4.91_mps;
    MaxAngularRate = 1.0_tps;
  };

  auto rt = systemJoystick.GetRightTriggerAxis();
  auto lt = systemJoystick.GetLeftTriggerAxis();
  if (rt > 0.1) {
    subsystemClaw.percentOut(-rt);
  } else if (lt > 0.2) {
    subsystemClaw.percentOut(lt);
  } else {
    subsystemClaw.percentOut(0);
  }
  if (systemJoystick.GetStartButton()) {
    if (subsystemClaw.hasCoral()) {
      subsystemClaw.percentOut(0);
      subsystemClaw.setAxis(20_deg);
    } else {
      subsystemClaw.setAxis(0_deg);
      subsystemClaw.percentOut(-0.2);
    }
  }
  // up 0
  // right 90
  // down 180 ?
  // left 270
  if (systemJoystick.GetPOV() == 0)
    subsystemClaw.setAxis(40_deg);
  if (systemJoystick.GetPOV() == 90)
    subsystemClaw.setAxis(20_deg);
  if (systemJoystick.GetPOV() == 180)
    subsystemClaw.setAxis(0_deg);
  if (systemJoystick.GetPOV() == 270)
    subsystemClaw.setAxis(150_deg);

  //   if(driverJoystick.Y().Get() == true) subsystemClaw.setAxis(90_deg);
  //   if(driverJoystick.X().Get() == true) subsystemClaw.setAxis(120_deg);
  if (systemJoystick.GetAButtonPressed() == true) {
    if (algea) {
      subsystemClaw.setAxis(150_deg); // CHECKK!!! might be weird........ set
                                      // diff just in case ELE slam
      if (subsystemClaw.acceptableAngle() == true)
        subsystemElevator.setHeight(0_tr); // CHECK
    } else if (!algea) {
      subsystemClaw.setAxis(20_deg);
      // if(subsystemClaw.getAngle() ==
      // 20_deg)subsystemElevator.setHeight(0_tr);
      if (subsystemClaw.acceptableAngle() == true)
        subsystemElevator.setHeight(0_tr);
    }
  } // 2.5 tr = l3 at 30 deg
  if (systemJoystick.GetBButtonPressed() == true) {
    if (algea) {
      subsystemClaw.setAxis(180_deg); // CHECKK!!!
      if (subsystemClaw.acceptableAngle() == true)
        subsystemElevator.setHeight(1.65_tr); // CHECK
    } else if (!algea) {
      subsystemClaw.setAxis(20_deg);
      if (subsystemClaw.acceptableAngle() == true)
        subsystemElevator.setHeight(1_tr);
    }
  }
  // 2.5 tr = l3 at 30 deg

  if (systemJoystick.GetXButtonPressed() == true) {
    if (algea) {
      subsystemClaw.setAxis(180_deg); // CHECKK!!!
      if (subsystemClaw.acceptableAngle() == true)
        subsystemElevator.setHeight(3.8_tr); // CHECK
    } else if (!algea) {
      subsystemClaw.setAxis(20_deg);
      if (subsystemClaw.acceptableAngle() == true)
        subsystemElevator.setHeight(2.3_tr);
    }
  }
  // 2.5 tr = l3 at 30 deg
  // 4tr? l4 90 deg
  if (systemJoystick.GetYButtonPressed() == true) {
    if (algea) {
      subsystemClaw.setAxis(90_deg); // CHECKK!!!???
      if (subsystemClaw.acceptableAngle() == true)
        subsystemElevator.setHeight(5_tr); // CHECK
    } else if (!algea) {
      subsystemClaw.setAxis(20_deg);

      if (subsystemClaw.acceptableAngle() == true)
        subsystemElevator.setHeight(4.35_tr);
    }
  }
  if (systemJoystick.GetLeftBumperButton() == true)
    subsystemClaw.percentOut(-0.2);
  if (systemJoystick.GetRightBumperButton() == true)
    subsystemClaw.percentOut(0);

  // frc::SmartDashboard::PutNumberArray("LL pose"
  // [visionEstimate.X().value(),visionEstimate.Y().value()]);
}

void RobotContainer::GetStartingPose() {
  auto pathName = paths.GetSelected();
  const frc::Pose2d pose =
      pathplanner::PathPlannerAuto(pathName->GetName()).getStartingPose();
  drivetrain.ResetPose(pose);
}

frc2::Command *RobotContainer::GetAutonomousCommand() {
  return paths.GetSelected();
}
