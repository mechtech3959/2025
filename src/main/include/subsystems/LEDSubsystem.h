#include <ctre/Phoenix.h>
#include <ctre/phoenix/led/RainbowAnimation.h>
#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>

namespace subsystems {
class LED : frc2::SubsystemBase {
  ctre::phoenix::led::CANdle led{20};

public:
  void Blue();
  void Red();
  void Green();
  void Rainbow();
};

}; // namespace subsystems
