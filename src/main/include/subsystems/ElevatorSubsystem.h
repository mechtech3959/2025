#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>

namespace subsystems {

class Elevator : frc2::SubsystemBase {
private:
  ctre::phoenix6::hardware::TalonFX masterM{12};
  ctre::phoenix6::hardware::TalonFX slaveM{13};

public:
  enum Positions {
    Zero,
    Trough,
    Barge,
    Processor,
    L1,
    L2,
    L3,
    L4

  };
  enum State {
    onTarget,
    Traveling

  };
  void sendData();
};
} // namespace subsystems