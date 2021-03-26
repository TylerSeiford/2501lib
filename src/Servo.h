#pragma once

#include "PWM.h"
#include "MotorSafety.h"


class Servo : public MotorSafety {
 private:
	PWM *pwm;
	uint8_t angle;

 public:
	/**
	 * @brief Construct a new Servo Object
	 * 
	 */
	Servo(ServoHat *hat, uint8_t channel);

	/**
	 * @brief Set the Servo to an angle
	 * 
	 * @param angle Angle to set it to
	 */
	void SetAngle(uint8_t angle);

	/**
	 * @brief Get the angle of the Servo
	 * 
	 * @return uint8_t angle the Servo is at
	 */
	uint8_t GetAngle();

	/**
	 * @brief Function to stop the servo
	 */
	void StopMotor();
};