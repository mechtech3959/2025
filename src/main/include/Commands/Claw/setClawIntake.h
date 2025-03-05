#pragma once

#include <frc2/command/Command.h>

#include <frc2/command/CommandHelper.h>

#include "subsystems/ClawSubsystem.h"

class setClawIntake
    : public frc2::CommandHelper<frc2::Command, setClawIntake> {

public:
  explicit setClawIntake(subsystems::Claw *subsystem);

  void Initialize() override;

  // void Execute() override;

  void End();

  bool IsFinished() override;

private:
  subsystems::Claw *Claw;
};