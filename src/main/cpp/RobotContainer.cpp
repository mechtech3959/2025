// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() {
 // ConfigureBindings();
 // ConfigureDashboard();
//  GetStartingPose();
}

void RobotContainer::ConfigureBindings() {
  /* frontLimeLight.updateTracking();
   backLimeLight.updateTracking();
   drivetrain.AddVisionMeasurement(frontLimeLight.poseEst(),
                                   frontLimeLight.timestamp);
   drivetrain.AddVisionMeasurement(backLimeLight.poseEst(),
                                   backLimeLight.timestamp);
   // Note that X is defined as forward according to WPILib convention,
   // and Y is defined as to the left according to WPILib convention.
   drivetrain.SetDefaultCommand(
       // Drivetrain will execute this command periodically
       drivetrain.ApplyRequest([this]() -> auto && {
         return drive
             .WithVelocityX(-joystick.GetLeftY() *
                            MaxSpeed) // Drive forward with negative Y (forward)
             .WithVelocityY(-joystick.GetLeftX() *
                            MaxSpeed) // Drive left with negative X (left)
             .WithRotationalRate(-joystick.GetRightX() *
                                 MaxAngularRate); // Drive counterclockwise with
         // negative X (left)
       }));
   joystick.X().WhileTrue(drivetrain.ApplyRequest([this]() -> auto && {
     if (frontLimeLight.LLHasTarget) {
       return drive //.WithVelocityX(-limelight.turncmd * 1_mps);
           .WithRotationalRate(-frontLimeLight.turncmd * 0.3_tps);
     } else {
       return drive.WithRotationalRate(-joystick.GetRightX() * MaxAngularRate);
     }
   }));

   joystick.A().WhileTrue(
       drivetrain.ApplyRequest([this]() -> auto && { return brake; }));
   joystick.B().WhileTrue(drivetrain.ApplyRequest([this]() -> auto && {
     return point.WithModuleDirection(
         frc::Rotation2d{-joystick.GetLeftY(), -joystick.GetLeftX()});
   }));

   // Run SysId routines when holding back/start and X/Y.
   // Note that each routine should be run exactly once in a single log.
   (joystick.Back() && joystick.Y())
       .WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kForward));
   (joystick.Back() && joystick.X())
       .WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kReverse));
   (joystick.Start() && joystick.Y())
       .WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kForward));
   (joystick.Start() && joystick.X())
       .WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kReverse));

   // reset the field-centric heading on left bumper press
   joystick.LeftBumper().OnTrue(
       drivetrain.RunOnce([this] { drivetrain.SeedFieldCentric(); }));
 */
   drivetrain.RegisterTelemetry(
    [this](auto const &state) { logger.Telemeterize(state); });
   logger.subsystemTelemeterize(subsystemClaw.clawLog,
                              subsystemElevator.elevatorLog);

   //joystick.X().WhileTrue(&smartIntake);
   
  /*
  joystick.B().WhileTrue(subsystemClaw.SysIdDynamic(frc2::sysid::kForward));
  joystick.A().WhileTrue(subsystemClaw.SysIdDynamic(frc2::sysid::kReverse));
  joystick.Y().WhileTrue(subsystemClaw.SysIdQuasistatic(frc2::sysid::kForward));
  joystick.X().WhileTrue(subsystemClaw.SysIdQuasistatic(frc2::sysid::kReverse));

  joystick.B().WhileTrue(subsystemElevator.SysIdDynamic(frc2::sysid::kForward));
  joystick.A().WhileTrue(subsystemElevator.SysIdDynamic(frc2::sysid::kReverse));
  joystick.Y().WhileTrue(subsystemElevator.SysIdQuasistatic(frc2::sysid::kForward));
  joystick.X().WhileTrue(subsystemElevator.SysIdQuasistatic(frc2::sysid::kReverse));
  */
 
 // frc2::cmd::Run(smartIntake);
 //joystick.X().WhileTrue(&smartIntake);


}

void RobotContainer::ConfigureDashboard() {
  auto rt = joystick.GetRightTriggerAxis();
  auto lt = joystick.GetLeftTriggerAxis();
  if(rt > 0.1){
    subsystemClaw.percentOut(-rt);
  }else if(lt >0.2){
    subsystemClaw.percentOut(lt);
  }else{subsystemClaw.percentOut(0);}
 if(joystick.Start().Get() == true){ if(subsystemClaw.hasCoral()){
  subsystemClaw.percentOut(0);
  subsystemClaw.setAxis(20_deg);
 }else{
  subsystemClaw.setAxis(0_deg);
  subsystemClaw.percentOut(-0.2);
 }}
  
  if(joystick.POVUp().Get() == true) subsystemClaw.setAxis(90_deg);
    if(joystick.POVLeft().Get() == true) subsystemClaw.setAxis(30_deg);
        if(joystick.POVDown().Get() == true) subsystemClaw.setAxis(0_deg);
        if(joystick.POVRight().Get() == true) subsystemClaw.setAxis(150_deg);

  //   if(joystick.Y().Get() == true) subsystemClaw.setAxis(90_deg);
 //   if(joystick.X().Get() == true) subsystemClaw.setAxis(120_deg);
  if(joystick.A().Get() ==true) subsystemElevator.setHeight(0_tr);// 2.5 tr = l3 at 30 deg  
 if(joystick.B().Get() ==true) subsystemElevator.setHeight(1_tr);// 2.5 tr = l3 at 30 deg  

 if(joystick.X().Get() ==true) subsystemElevator.setHeight(2.3_tr);// 2.5 tr = l3 at 30 deg  
 //4tr? l4 90 deg
 if(joystick.Y().Get() ==true) subsystemElevator.setHeight(4.5_tr);
 if(joystick.RightBumper().Get() == true) subsystemClaw.percentOut(-0.2);
  if(joystick.LeftBumper().Get() == true) subsystemClaw.percentOut(0);

 // frc::SmartDashboard::PutData("autochooser", &paths);
  // frc::SmartDashboard::PutNumberArray("LL pose"
  // [visionEstimate.X().value(),visionEstimate.Y().value()]);
}
/*
void RobotContainer::GetStartingPose() {
  auto pathName = paths.GetSelected();
  const frc::Pose2d pose =
      pathplanner::PathPlannerAuto(pathName->GetName()).getStartingPose();
  return drivetrain.ResetPose(pose);
}

frc2::Command *RobotContainer::GetAutonomousCommand() {
  return paths.GetSelected();
}
*/