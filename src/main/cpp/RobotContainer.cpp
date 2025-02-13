// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() {
  ConfigureBindings();
  ConfigureDashboard();
  GetStartingPose();
}

void RobotContainer::ConfigureBindings() {
  // limelight.updateTracking();
  visionEstimate = limelight.poseEst();

  // Note that X is defined as forward according to WPILib convention,
  // and Y is defined as to the left according to WPILib convention.
  drivetrain.SetDefaultCommand(
      // Drivetrain will execute this command periodically
      drivetrain.ApplyRequest([this]() -> auto && {
        return drive
            .WithVelocityX(-joystick.GetLeftX() * MaxSpeed)
            // Drive left with negative X (left)
            .WithVelocityY(-joystick.GetLeftY() * MaxSpeed)
            .WithRotationalRate(-joystick.GetRightX() *
                                MaxAngularRate); // Drive counterclockwise with
                                                 // negative X (left)
      }));
  joystick.X().WhileTrue(drivetrain.ApplyRequest([this]() -> auto && {
    if (limelight.LLHasTarget) {
      return drive.WithVelocityX(-limelight.turncmd * 4_mps);
      // .WithRotationalRate(-limelight.turncmd * 0.5_tps);
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

  drivetrain.RegisterTelemetry(
      [this](auto const &state) { logger.Telemeterize(state); });
  /*   double dx = joystick.GetRightX();
    double dy = joystick.GetRightY();
    frc::Rotation2d dd = 0_deg;
    if (sqrt(dx * dx + dy * dy) > 0.9) {dd = frc::Rotation2d(dx,
    dy).Degrees();}; return aDrive .WithVelocityX(-joystick.GetLeftY() *
                       MaxSpeed) // Drive forward with negative Y (forward)
        .WithVelocityY(-joystick.GetLeftX() * MaxSpeed)
        .WithTargetDirection(dd); */
}
void RobotContainer::ConfigureDashboard() {
  frc::SmartDashboard::PutData("autochooser", &paths);
  // frc::SmartDashboard::PutNumberArray("LL pose",
  // [visionEstimate.X().value(),visionEstimate.Y().value()]);
}
void RobotContainer::GetStartingPose() {
  auto pathName = paths.GetSelected();
  const frc::Pose2d pose =
      pathplanner::PathPlannerAuto(pathName->GetName()).getStartingPose();
  return drivetrain.ResetPose(pose);
}

frc2::Command *RobotContainer::GetAutonomousCommand() {
  return paths.GetSelected();
}
