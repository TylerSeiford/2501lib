#include "RobotBase.h"

#include "Version.h"

#include <iostream>
#include <unistd.h>
#include <signal.h>


static void ctrl_c_handler(int signum) {
	(void) (signum);
	RobotBase::SetRunning(false);
}

static void setup_handlers() {
	static struct sigaction sa;
	sa.sa_handler = ctrl_c_handler;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}

volatile bool RobotBase::running;

RobotBase::RobotBase(Joystick *stick, ServoHat *hat) {
	period = 20000U;
	RobotBase::stick = stick;
	RobotBase::hat = hat;
}

RobotBase::RobotBase(Joystick *stick, ServoHat *hat, uint32_t period) {
	RobotBase::period = period;
	RobotBase::stick = stick;
	RobotBase::hat = hat;
}

void RobotBase::Run() {
	running = true;
	setup_handlers();

	std::cout << "[2501]\tBooting with version\t" << lib_2501::VERSION << "\n";
	RobotInit();


	while(running) {
		// Sleep for period
		usleep(period);

		// Update joystick values
		stick->Update();

		// Deal with start button for enable/disable
		if(stick->HasButtonChanged(GAMEPAD::BUTTONS::START) && stick->GetButton(GAMEPAD::BUTTONS::START)) {
			if(!enabled) {
				enabled = true;
				hat->Enable();
				TeleopInit();
			}
			else {
				enabled = false;
				hat->Disable();
				DisabledInit();
			}
		}

		if(enabled) {
			TeleopPeriodic();
		}
		else {
			DisabledPeriodic();
		}

		RobotPeriodic();
	}

	// Cleanup
	if(enabled) {
		enabled = false;
		hat->Disable();
		DisabledInit();
	}

	Shutdown();
}