#include "subsystems/CameraSubsystem.h"

using namespace subsystems;

Camera::Camera(std::string nt) {
  cam = nt::NetworkTableInstance::GetDefault().GetTable(nt);
  name = nt;
  // photon::PhotonCamera c(nt);
}

void Camera::updateTracking() {}
