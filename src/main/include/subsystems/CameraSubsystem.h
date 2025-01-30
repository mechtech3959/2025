#include "networktables/NetworkTable.h"
#include <frc/geometry/Pose2d.h>
#include <frc2/command/SubsystemBase.h>
#include <photon/PhotonCamera.h>

namespace subsystems {
class Camera : frc2::SubsystemBase {
private:
  std::shared_ptr<nt::NetworkTable> cam;
  std::string name = "camera";

public:
  photon::PhotonCamera camera(std::string n);

  double tx, ty, ta;
  bool tv;
  void updateTracking();
  Camera(std::string nt);
};

} // namespace subsystems