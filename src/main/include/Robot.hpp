#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>

#include "RobotContainer.hpp"

class Robot final : public frc::TimedRobot
{
public:
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void TeleopInit() override;
  void TestInit() override;

private:
  RobotContainer container;

  frc2::Command *autonomousCommand;
};
