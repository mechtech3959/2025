#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/TalonFX.hpp>

namespace customLogging {

struct ElevatorState {
  ctre::phoenix6::StatusSignal<units::angle::turn_t> encoderPose;
  ctre::phoenix6::StatusSignal<units::angle::turn_t> encoderABSPose;
  ctre::phoenix6::StatusSignal<units::angle::turn_t> masterPose;
  ctre::phoenix6::StatusSignal<units::angle::turn_t> slavePose;
  units::inch_t elevatorPose;
  units::inch_t targetPose;
};
struct ClawState {
  ctre::phoenix6::StatusSignal<units::angle::turn_t> encoderPose;
  ctre::phoenix6::StatusSignal<units::angle::turn_t> encoderABSPose;
  ctre::phoenix6::StatusSignal<units::angle::turn_t> motorPose;
  units::degree_t currentAngle;
  units::degree_t lastKnowAngle;
  units::degree_t targetAngle;
  bool coralDetected;
};

} // namespace customLogging