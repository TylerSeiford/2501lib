#pragma once

#include <cstdint>

#include "ServoHat.h"
#include "Joystick.h"

static void ctrl_c_handler(int signum);
static void setup_handlers();

class RobotBase {
 private:
	static volatile bool running;

	bool enabled = false;
	uint32_t period; // In microseconds

 protected:
	ServoHat *hat;
	Joystick *stick;

 public:
	static void SetRunning(bool running) {
		RobotBase::running = running;
	}

	RobotBase(Joystick *stick, ServoHat *hat);

	RobotBase(Joystick *stick, ServoHat *hat, uint32_t period);

	void Run();

	virtual void Shutdown() = 0;

	virtual void RobotInit() = 0;
	virtual void RobotPeriodic() = 0;

	virtual void TeleopInit() = 0;
	virtual void TeleopPeriodic() = 0;

	virtual void DisabledInit() = 0;
	virtual void DisabledPeriodic() = 0;
};
