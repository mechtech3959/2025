#pragma once


#include <frc2/command/Command.h>

#include <frc2/command/CommandHelper.h>


#include "subsystems/ElevatorSubsystem.h"


/**

 * A simple command that grabs a hatch with the HatchSubsystem.  Written

 * explicitly for pedagogical purposes.  Actual code should inline a command

 * this simple with InstantCommand.

 *

 * @see InstantCommand

 */

class setElevatorL1 : public frc2::CommandHelper<frc2::Command, setElevatorL1> {

 public:

  explicit setElevatorL1( subsystems::Elevator* subsystem);

  void Initialize() override;
  
  void Execute() override;


  bool IsFinished() override;


 private:

    subsystems::Elevator* Elevator;


};