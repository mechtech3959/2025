#include "LimelightHelpers.h"
#include "networktables/NetworkTable.h"
#include <frc/geometry/Pose2d.h>
#include <frc2/command/SubsystemBase.h>
namespace subsystems{
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

public:
  double drivecmd, turncmd, distance;
  bool LLHasTarget;

  LimeLight(std::string name);
  void updateTracking(std::string name);
  frc::Pose2d poseEst(std::string name);
  void centerApriltag();
};
}