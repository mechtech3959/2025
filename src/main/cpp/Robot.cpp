#include <frc2/command/CommandScheduler.h>

#include "Robot.hpp"

void Robot::RobotPeriodic() { frc2::CommandScheduler::GetInstance().Run(); }

void Robot::TeleopInit() { container.TeleopInit(); }

void Robot::TestInit() { frc2::CommandScheduler::GetInstance().CancelAll(); }

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
