#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/TalonFX.hpp>

namespace customLogging {

struct ElevatorState {
  units::angle::turn_t encoderPose;
  units::angle::turn_t encoderABSPose;
  units::angle::turn_t masterPose;
  units::angle::turn_t slavePose;
  units::inch_t elevatorPose;
  units::inch_t targetPose;
};
struct ClawState {
  units::angle::turn_t encoderPose;
  units::angle::turn_t encoderABSPose;
  units::angle::turn_t motorPose;
  units::degree_t currentAngle;
  units::degree_t lastKnowAngle;
  units::degree_t targetAngle;
  bool coralDetected;
};

} // namespace customLogging