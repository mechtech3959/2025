#include "Commands/ScoreL3.h"

ScoreL3::ScoreL3(subsystems::Claw *claw, subsystems::Elevator *elevator) {
  AddCommands(setClawStandard(claw), setElevatorL3(elevator));
}
