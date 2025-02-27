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

class setElevatorL3 : public frc2::CommandHelper<frc2::Command, setElevatorL3> {

 public:

  explicit setElevatorL3( subsystems::Elevator* subsystem);


  void Execute() override;


  bool IsFinished() override;


 private:

    subsystems::Elevator* Elevator;


};