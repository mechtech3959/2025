#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>

class Elevator : frc2::SubsystemBase {
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