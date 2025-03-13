// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() {
  ConfigureBindings();
  // ConfigureDashboard();
  // GetStartingPose();
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

  driverJoystick.A().WhileTrue(
      drivetrain.ApplyRequest([this]() -> auto && { return brake; }));
  driverJoystick.B().WhileTrue(drivetrain.ApplyRequest([this]() -> auto && {
    return point.WithModuleDirection(frc::Rotation2d{
        -driverJoystick.GetLeftY(), -driverJoystick.GetLeftX()});
  }));

  // Run SysId routines when holding back/start and X/Y.
  // Note that each routine should be run exactly once in a single log.
 (driverJoystick.Back() && driverJoystick.Y())
     .WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kForward));
  (driverJoystick.Back() && driverJoystick.X())
   .WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kReverse));
  (driverJoystick.Start() && driverJoystick.Y())
   .WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kForward));
(driverJoystick.Start() && driverJoystick.X())
   .WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kReverse));

  // reset the field-centric heading on left bumper press
  driverJoystick.LeftBumper().OnTrue(
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
void RobotContainer::ConfigureDashboard(){
 // logger.subsystemTelemeterize(subsystemClaw.clawLog,
  //                       subsystemElevator.elevatorLog);
  frc::SmartDashboard::PutData("autochooser", &paths);

}
void RobotContainer::ConfigureTeli() {
  //if (con .Y ().Get() ) {
//    if (algea == false){
  //    algea = true;}
  // else if (algea == true){
   //   algea = false;}
//  }
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
  if (systemJoystick.Start().Get() == true) {
    if (subsystemClaw.hasCoral()) {
      subsystemClaw.percentOut(0);
      subsystemClaw.setAxis(20_deg);
    } else {
      subsystemClaw.setAxis(0_deg);
      subsystemClaw.percentOut(-0.2);
    }
  }

  if (systemJoystick.POVUp().Get() == true)
    subsystemClaw.setAxis(40_deg);
  if (systemJoystick.POVLeft().Get() == true)
    subsystemClaw.setAxis(20_deg);
  if (systemJoystick.POVDown().Get() == true)
    subsystemClaw.setAxis(0_deg);
  if (systemJoystick.POVRight().Get() == true)
    subsystemClaw.setAxis(150_deg);

  //   if(driverJoystick.Y().Get() == true) subsystemClaw.setAxis(90_deg);
  //   if(driverJoystick.X().Get() == true) subsystemClaw.setAxis(120_deg);
  if (systemJoystick.A().Get() == true) {
    subsystemClaw.setAxis(20_deg);
    // if(subsystemClaw.getAngle() == 20_deg)subsystemElevator.setHeight(0_tr);
    if (subsystemClaw.acceptableAngle() == true)
      subsystemElevator.setHeight(0_tr);
  } // 2.5 tr = l3 at 30 deg
  if (systemJoystick.B().Get() == true) {
    subsystemClaw.setAxis(20_deg);
    if (subsystemClaw.acceptableAngle() == true)
      subsystemElevator.setHeight(1_tr);
  } // 2.5 tr = l3 at 30 deg

  if (systemJoystick.X().Get() == true) {
    subsystemClaw.setAxis(20_deg);
    if (subsystemClaw.acceptableAngle() == true)
      subsystemElevator.setHeight(2.3_tr);
  }
  // 2.5 tr = l3 at 30 deg
  // 4tr? l4 90 deg
  if (systemJoystick.Y().Get() == true) {
    subsystemClaw.setAxis(20_deg);

    if (subsystemClaw.acceptableAngle() == true)
      subsystemElevator.setHeight(4.3_tr);
  }
  if (systemJoystick.RightBumper().Get() == true)
    subsystemClaw.percentOut(-0.2);
  if (systemJoystick.LeftBumper().Get() == true)
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
