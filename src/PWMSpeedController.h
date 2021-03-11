#pragma once

#include "SpeedController.h"
#include "PWM.h"


class PWMSpeedController : public SpeedController, public MotorSafety {
 private:
	PWM *pwm;

 public:
	/**
	 * @brief Construct a new PWMSpeedController object
	 * 
	 * @param hat ServoHat to use
	 * @param channel PWM channel on the ServoHat to use
	 */
	PWMSpeedController(ServoHat *hat, uint8_t channel);

	/**
	 * @brief Set the SpeedController to a speed
	 * 
	 * @param speed Speed to set it to
	 */
	void Set(double speed);

	/**
	 * @brief Function to stop the motor
	 */
	void StopMotor();
};