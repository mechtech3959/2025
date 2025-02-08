#include "subsystems/LEDSubsystem.h"

using namespace subsystems;

void LED::Blue() { led.SetLEDs(0, 0, 255); };
void LED::Red() { led.SetLEDs(255, 0, 0); }
void LED::Green() { led.SetLEDs(0, 255, 0); }
void LED::Rainbow() {}