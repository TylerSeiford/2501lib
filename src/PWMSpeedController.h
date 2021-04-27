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
	
	/**
	 * @brief Set the Max PWM microseconds
	 * 
	 * @param max_us Maximum output period in microseconds
	 */
	void SetMaxUs(uint16_t max_us);
	
	/**
	 * @brief Set the Center PWM microseconds
	 * 
	 * @param max_us Center output period in microseconds
	 */
	void SetCenterUs(uint16_t center_us);
	
	/**
	 * @brief Set the Min PWM microseconds
	 * 
	 * @param max_us Minimum output period in microseconds
	 */
	void SetMinUs(uint16_t max_us);
};