#include "subsystems/LimeLightSubsystem.h"

using namespace subsystems;

LimeLight::LimeLight(std::string name) {
  limelight = nt::NetworkTableInstance::GetDefault().GetTable(name);
};
void LimeLight::updateTracking(std::string name) {
  tx = LimelightHelpers::getTX(name);
  ty = LimelightHelpers::getTY(name);
  ta = LimelightHelpers::getTA(name);
  tv = LimelightHelpers::getTV(name);
  if (tv < 1.0) {
    drivecmd = 0.0;
    turncmd = 0.0;
    distance = 0.0;
    LLHasTarget = false;
  } else {
    LLHasTarget = true;
    // limt output val to avoid aggressive movement
    turncmd = clamp(tx, -0.5, 0.5);
    drivecmd = clamp(ta, -0.5, 0.5);
  }
};
frc::Pose2d LimeLight::poseEst(std ::string name) {
  if (LLHasTarget && (tx < 0.1 || tx > -0.1)) {
    std::optional<LimelightHelpers::PoseEstimate> posEst =
        LimelightHelpers::getBotPoseEstimate_wpiBlue_MegaTag2(name);
    frc::Pose2d p = (posEst.has_value()) ? frc::Pose2d{posEst->pose}
                                         : frc::Pose2d{0_m, 0_m, 0_deg};
    return p;
  }
};