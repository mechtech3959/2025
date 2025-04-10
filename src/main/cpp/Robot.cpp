// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>

Robot::Robot() { frc::CameraServer::StartAutomaticCapture().SetFPS(30); }

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
  // m_container.subsystemClaw.clawPeriodic();
  // m_container.ConfigureBindings();
  m_container.ConfigureDashboard();
  frc::SmartDashboard::PutBoolean("coral",
                                  m_container.subsystemClaw.hasCoral());

  /*/ m_container.frontLimeLight.updateTracking();
   m_container.frontLimeLight.poseEst();
   m_container.backLimeLight.updateTracking();
   m_container.backLimeLight.poseEst();*/
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::DisabledExit() {}

void Robot::AutonomousInit() {
  autonT.Start();
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand) {
    m_autonomousCommand.value()->Schedule();
  }
}

void Robot::AutonomousPeriodic() {
  if (autonT.Get() >= 6_s) {
    m_container.subsystemClaw.setAxis(20_deg);
    if (autonT.Get() >= 7_s) {
      m_container.subsystemClaw.percentOut(-0.2);
    }
  };
}

void Robot::AutonomousExit() {}

void Robot::TeleopInit() {
  autonT.Stop();
  if (m_autonomousCommand) {
    m_autonomousCommand.value()->Cancel();
  }
}

void Robot::TeleopPeriodic() { m_container.ConfigureTeli(); }

void Robot::TeleopExit() {}

void Robot::TestInit() { frc2::CommandScheduler::GetInstance().CancelAll(); }

void Robot::TestPeriodic() {}

void Robot::TestExit() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
