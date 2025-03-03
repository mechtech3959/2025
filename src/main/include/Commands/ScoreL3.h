#pragma once

#include "Commands/Claw/setClawStandard.h"
#include "Commands/Elevator/setElevatorL3.h"
#include "subsystems/ClawSubsystem.h"
#include "subsystems/ElevatorSubsystem.h"
#include <frc2/command/Command.h>

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>

class ScoreL3
    : public frc2::CommandHelper<frc2::ParallelCommandGroup, ScoreL3> {

public:
   ScoreL3(subsystems::Claw *claw, subsystems::Elevator *elevator);
};
