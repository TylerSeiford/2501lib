#pragma once

#include <cstdint>

#include "ServoHat.h"
#include "Joystick.h"

/**
 * @brief Handler for CTRL+C (SIGKILL & SIGTERM)
 */
static void ctrl_c_handler(int signum);

/**
 * @brief Register the CTRL+C (SIGKILL & SIGTERM) handler
 * 
 */
static void setup_handlers();

/**
 * @brief Base class for all robots.
 * 
 * Extend this class to implement your robot code
 */
class RobotBase {
 private:
	// Boolean to track if we have had a CTRL+C yet
	static volatile bool running;

	uint8_t START_BUTTON, SELECT_BUTTON;

	// Boolean to track if we are enabled or not
	bool enabled = false;
		// TODO: This should become a uint8_t for the state being between disabled, auto, and teleop
	// Period of a loop in microseconds
	uint32_t period;

 protected:
	// ServoHat to use
	ServoHat *hat;
	// Joystick to use
	Joystick *stick;

 public:
	/**
	 * @brief Set the status of the program
	 * 
	 * @param running Setting this false will terminate the program safely
	 */
	static void SetRunning(bool running) {
		RobotBase::running = running;
	}

	/**
	 * @brief Construct a new Robot Base object
	 * 
	 * @param stick Joystick to use
	 * @param hat ServoHat to use
	 * @param START_BUTTON button ID for the start button
	 * @param SELECT_BUTTON button ID for the select button
	 * Uses a period of 20,000 microseconds, or 50 times a second
	 */
	RobotBase(Joystick *stick, ServoHat *hat, const uint8_t START_BUTTON, const uint8_t SELECT_BUTTON);

	/**
	 * @brief Construct a new Robot Base object
	 * 
	 * @param stick Joystick to use
	 * @param hat ServoHat to use
	 * @param START_BUTTON button ID for the start button
	 * @param SELECT_BUTTON button ID for the select button
	 * @param period Period of a loop in microseconds
	 */
	RobotBase(Joystick *stick, ServoHat *hat, const uint8_t START_BUTTON, const uint8_t SELECT_BUTTON, uint32_t period);

	/**
	 * @brief Run the robot program
	 */
	void Run();

	/**
	 * @brief This function is called when the program is terminated.
	 * 
	 * Place any destruction code here
	 */
	virtual void Shutdown() = 0;

	/**
	 * @brief This function is called briefly after robot creation
	 * 
	 * Place any initization code here
	 */
	virtual void RobotInit() = 0;

	/**
	 * @brief This function is called every loop
	 */
	virtual void RobotPeriodic() = 0;

	/**
	 * @brief This function is called when the robot enters Teleop mode
	 */
	virtual void TeleopInit() = 0;

	/**
	 * @brief This function is called every loop when the robot is in Teleop mode
	 */
	virtual void TeleopPeriodic() = 0;

	/**
	 * @brief This function is called when the robot enters Disabled mode
	 */
	virtual void DisabledInit() = 0;

	/**
	 * @brief This function is called every loop when the robot is in Disabled mode
	 */
	virtual void DisabledPeriodic() = 0;
};
