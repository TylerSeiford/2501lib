#include "RobotBase.h"

#include "Version.h"

#include <iostream>
#include <chrono>
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

RobotBase::RobotBase(Joystick *stick, ServoHat *hat, const uint8_t START_BUTTON, const uint8_t SELECT_BUTTON) {
	period = 20000U;
	RobotBase::stick = stick;
	RobotBase::hat = hat;
	RobotBase::START_BUTTON = START_BUTTON;
	RobotBase::SELECT_BUTTON = SELECT_BUTTON;
}

RobotBase::RobotBase(Joystick *stick, ServoHat *hat, const uint8_t START_BUTTON, const uint8_t SELECT_BUTTON, uint32_t period) {
	RobotBase::period = period;
	RobotBase::stick = stick;
	RobotBase::hat = hat;
	RobotBase::START_BUTTON = START_BUTTON;
	RobotBase::SELECT_BUTTON = SELECT_BUTTON;
}

void RobotBase::Run() {
	running = true;
	setup_handlers();

	std::cout << "[2501]\tBooting with version\t" << lib_2501::VERSION << "\n";
	RobotInit();


	while(running) {
		auto start = std::chrono::high_resolution_clock::now();

		// Update joystick values
		stick->Update();

		// Deal with start button for enable/disable teleop
		if(stick->HasButtonChanged(START_BUTTON) && stick->GetButton(START_BUTTON)) {
			if(state == DISABLED) {
				state = TELEOP;
				hat->Enable();
				TeleopInit();
			}
			else {
				state = DISABLED;
				hat->Disable();
				DisabledInit();
			}
		}
		else if(stick->HasButtonChanged(SELECT_BUTTON) && stick->GetButton(SELECT_BUTTON)) {
			if(state == DISABLED) {
				state = AUTONOMOUS;
				hat->Enable();
				AutonomousInit();
			}
			else {
				state = DISABLED;
				hat->Disable();
				DisabledInit();
			}
		}

		if(state == TELEOP) {
			TeleopPeriodic();
		}
		else if(state == AUTONOMOUS) {
			AutonomousPeriodic();
		}
		else {
			DisabledPeriodic();
		}

		RobotPeriodic();

		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		uint64_t microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
		if(microseconds > period) {
			std::cout << "[2501]\t" << "Loop overrun!\n";
		}
		else {
			usleep(period - microseconds);
		}
	}

	// Cleanup
	if(state) {
		state = DISABLED;
		hat->Disable();
		DisabledInit();
	}

	Shutdown();
}