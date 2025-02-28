#pragma once

#include <frc2/command/Command.h>

#include <frc2/command/CommandHelper.h>

#include "subsystems/ClawSubsystem.h"

class setClawFeedStart : public frc2::CommandHelper<frc2::Command, setClawFeedStart> {

public:
  explicit setClawFeedStart(subsystems::Claw *subsystem);

  void Initialize() override;

  void Execute() override;

  bool IsFinished() override;

private:
  subsystems::Claw *Claw;
};