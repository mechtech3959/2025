#pragma once

#include <frc/TimedRobot.h>

#include "RobotContainer.hpp"

class Robot : public frc::TimedRobot {
public:
  void RobotPeriodic() override;
  void TestInit() override;

private:
  RobotContainer container;
};
