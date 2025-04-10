#include "LimelightHelpers.h"
#include "networktables/NetworkTable.h"
#include <frc/geometry/Pose2d.h>
#include <frc2/command/Subsystem.h>
#include <frc2/command/SubsystemBase.h>
namespace subsystems {
class LimeLight : frc2::SubsystemBase {
private:
  std::shared_ptr<nt::NetworkTable> limelight;
  double clamp(double in, double minval, double maxval) {
    if (in > maxval)
      return maxval;
    if (in < minval)
      return minval;
    return in;
  };
  double tx, ty, ta, tv;
  std::string name;

public:
  double drivecmd, turncmd, distance;
  units::time::second_t timestamp;
  bool LLHasTarget;
  LimeLight(std::string NTname);
  void updateTracking();
  frc::Pose2d poseEst();
  void centerApriltag();
  void Periodic() override;
};
} // namespace subsystems