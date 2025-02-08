#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>

#include "SystemConstants.h"
namespace subsystems {

class Elevator : frc2::SubsystemBase {
private:
  ctre::phoenix6::hardware::TalonFX masterM{12};
  ctre::phoenix6::hardware::TalonFX slaveM{13};
  ctre::phoenix6::hardware::CANcoder encoder{14};

public:
  // inches, measurements are relative to the floor 
  enum Positions {
    Zero = 0,
    Barge = 101,
    Processor = 15, // top =27 bottom is 7 ,
    L1 = 18,
    L2 = 31, // 31.875,
    L3 = 48, // 47.625
    L4 = 72

  };
  enum State {
    onTarget,
    Traveling

  };
  void elevatorInit();
  void setHeight(Positions pos);
  void sendData();
};
} // namespace subsystems