#pragma once

#include <frc2/command/Command.h>

#include <frc2/command/CommandHelper.h>

#include "subsystems/ClawSubsystem.h"

class setClawL4 : public frc2::CommandHelper<frc2::Command, setClawL4> {

public:
  explicit setClawL4(subsystems::Claw *subsystem);

  void Initialize() override;

  void Execute() override;

  bool IsFinished() override;

private:
  subsystems::Claw *Claw;
};