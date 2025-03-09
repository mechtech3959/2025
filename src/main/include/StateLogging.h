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
  double currentAmperage;
  double CurrentMvoltage;
  double CurrentSvoltage;

};
struct ClawState {
  double axisMotorPose;
  bool coralDetected;
  bool acceptableAngle;
  double currentAngle;
  double lastKnowAngle;
  double targetAngle;
  double encoderPose;
  double encoderABSPose;
  double intakeMotorPose;
};

#endif