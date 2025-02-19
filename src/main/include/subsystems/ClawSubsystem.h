#include "SystemConstants.h"
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>

namespace subsystems {

class Claw : frc2::SubsystemBase {
private:
  ctre::phoenix6::hardware::TalonFX intakeMotor{15};
  ctre::phoenix6::hardware::TalonFX axisMotor{16};
  ctre::phoenix6::hardware::CANcoder axisEncoder{17};

  // TODO: determine sensor
public:
  const units::degree_t L123 = 0_deg;
  const units::degree_t L4 = 90_deg;
  const units::degree_t algea = 180_deg;
  const units::degree_t trough = 0_deg;

  enum states { traveling, onTarget };
  Claw();
  void clawInit();
  void setIntake();
  void setAxis(units::deg position);
  void sendData();
  bool hasCoral();
};

} // namespace subsystems
