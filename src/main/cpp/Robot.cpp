#include <frc2/command/CommandScheduler.h>

#include "Robot.hpp"

void Robot::RobotPeriodic() { frc2::CommandScheduler::GetInstance().Run(); }

void Robot::AutonomousInit() {
  autonomousCommand = container.GetAutonomousCommand();
  autonomousCommand->Schedule();
}

void Robot::TeleopInit() {
  autonomousCommand->Cancel();

  container.TeleopInit();
}

void Robot::TestInit() { frc2::CommandScheduler::GetInstance().CancelAll(); }

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
