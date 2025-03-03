#include "Commands/ScoreL3.h"

ScoreL3::ScoreL3(setClawStandard *claw, setElevatorL3 *elevator) {
  AddCommands(setClawStandard(*claw), setElevatorL3(*elevator));
}
