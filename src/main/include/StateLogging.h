#ifndef StateLogging_H
#define StateLogging_H
#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/TalonFX.hpp>

struct ElevatorState {

  double encoderPose;
  double encoderABSPose;
  double masterPose;
  double slavePose;
  double elevatorPose;
  double targetPose;
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