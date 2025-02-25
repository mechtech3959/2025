#ifndef StateLogging_H
#define StateLogging_H
#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/TalonFX.hpp>


 struct ElevatorState {

  units::angle::turn_t encoderPose;
  units::angle::turn_t encoderABSPose;
  units::angle::turn_t masterPose;
  units::angle::turn_t slavePose;
  units::inch_t elevatorPose;
  units::inch_t targetPose;
};
struct ClawState {
  double axisMotorPose;
  bool coralDetected;

  double currentAngle;
  double lastKnowAngle;
  double targetAngle;
  double encoderPose;
  double encoderABSPose;
  double intakeMotorPose;
};

#endif