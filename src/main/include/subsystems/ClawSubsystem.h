#include "SystemConstants.h"
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>

namespace subsystems {

class Claw : public frc2::SubsystemBase {
private:
  rev::spark::SparkMax intakeMotor{19,
                                   rev::spark::SparkMax::MotorType::kBrushless};
  ctre::phoenix6::hardware::TalonFX axisMotor{20};
  ctre::phoenix6::hardware::CANcoder axisEncoder{21};
  frc::DigitalInput coralSensor{1};
  ctre::phoenix6::controls::MotionMagicVoltage axisMotion{0_deg};
  // TODO: determine sensor
public:
  const units::degree_t L123 = 0_deg;
  const units::degree_t L4 = 90_deg;
  const units::degree_t algea = 180_deg;
  const units::degree_t trough = 0_deg;
  units::degree_t lastKnownAngle;
  enum states { traveling, onTarget };
  states state;
  customLogging::ClawState clawLog;

  Claw();
  void clawPeriodic();
  void setIntake();
  void setOutake();
  void setStaticIntake();
  void setStaticOuttake();
  void setAxis(units::degree_t angle);
  void sendData();
  bool hasCoral(frc::DigitalInput &input);
};

} // namespace subsystems
