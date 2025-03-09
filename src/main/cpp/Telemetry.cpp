#include "Telemetry.h"
#include <frc/smartdashboard/SmartDashboard.h>

using namespace ctre::phoenix6;

void Telemetry::subsystemTelemeterize(ClawState const &clawState,
                                      ElevatorState const &elevatorState) {
  // elevator
  elevatorMasterPose.Set(elevatorState.masterPose);
  elevatorSlavePose.Set(elevatorState.slavePose);
  elevatorPose.Set(elevatorState.elevatorPose);
  elevatorABSEncoderPose.Set(elevatorState.encoderABSPose);
    SignalLogger::WriteDouble("ElevatorState/MasterPose",elevatorState.masterPose);
    SignalLogger::WriteDouble("ElevatorState/SlavePose",elevatorState.slavePose);
    SignalLogger::WriteDouble("ElevatorState/ElevatorPose",elevatorState.elevatorPose);

  // elevatorTargetpose.Set()
  // claw
  clawAbsoluteEncoderPose.Set(clawState.encoderABSPose);
  clawAxisPosition.Set(clawState.encoderPose);
  clawCurrentAxisAngle.Set(clawState.currentAngle);
  // clawTargetAxisAngle.Set();
  // clawLastAxisAngle.Set();
  // clawEncoderTurnCount.Set();

  clawHasCoral.Set(clawState.coralDetected);
  clawAtAcceptableAngle.Set(clawState.acceptableAngle);
  SignalLogger::WriteDouble("ClawState/ClawAxis",clawState.currentAngle);
  //SignalLogger::WriteDouble("ClawState/TargetAngle",clawState.currentAngle);
  SignalLogger::WriteBoolean("ClawState/ClawAcceptableAngle",clawState.acceptableAngle);


};
void Telemetry::Telemeterize(
    subsystems::CommandSwerveDrivetrain::SwerveDriveState const &state) {

  /* Telemeterize the swerve drive state */
  drivePose.Set(state.Pose);
  driveSpeeds.Set(state.Speeds);
  driveModuleStates.Set(state.ModuleStates);
  driveModuleTargets.Set(state.ModuleTargets);
  driveModulePositions.Set(state.ModulePositions);
  driveTimestamp.Set(state.Timestamp.value());
  driveOdometryFrequency.Set(1.0 / state.OdometryPeriod.value());

  /* Also write to log file */
  std::array<double, 8> moduleStatesArray{};
  std::array<double, 8> moduleTargetsArray{};
  for (int i = 0; i < 4; ++i) {
    moduleStatesArray[i * 2 + 0] =
        state.ModuleStates[i].angle.Radians().value();
    moduleStatesArray[i * 2 + 1] = state.ModuleStates[i].speed.value();
    moduleTargetsArray[i * 2 + 0] =
        state.ModuleTargets[i].angle.Radians().value();
    moduleTargetsArray[i * 2 + 1] = state.ModuleTargets[i].speed.value();
  }
  SignalLogger::WriteDoubleArray(
      "DriveState/Pose", {state.Pose.X().value(), state.Pose.Y().value(),
                          state.Pose.Rotation().Degrees().value()});
  SignalLogger::WriteDoubleArray("DriveState/ModuleStates", moduleStatesArray);
  SignalLogger::WriteDoubleArray("DriveState/ModuleTargets",
                                 moduleTargetsArray);
  SignalLogger::WriteValue("DriveState/OdometryPeriod", state.OdometryPeriod);

  /* Telemeterize the pose to a Field2d */
  fieldTypePub.Set("Field2d");
  fieldPub.Set(std::array{state.Pose.X().value(), state.Pose.Y().value(),
                          state.Pose.Rotation().Degrees().value()});

  /* Telemeterize the module states to a Mechanism2d */
  for (size_t i = 0; i < m_moduleSpeeds.size(); ++i) {
    m_moduleDirections[i]->SetAngle(state.ModuleStates[i].angle.Degrees());
    m_moduleSpeeds[i]->SetAngle(state.ModuleStates[i].angle.Degrees());
    m_moduleSpeeds[i]->SetLength(state.ModuleStates[i].speed / (2 * MaxSpeed));

    frc::SmartDashboard::PutData("Module " + std::to_string(i),
                                 &m_moduleMechanisms[i]);
  }

  // drivers station
  frc::DataLogManager::Start();
  // Record both DS control and joystick data
  frc::DriverStation::StartDataLog(frc::DataLogManager::GetLog());
}
