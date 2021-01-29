#pragma once

#include "SpeedController.h"
#include "PWM.h"
#include "DigitalOutput.h"


class L298N : public SpeedController {
 private:
	// PWM object to interact with the ServoHat
	PWM *pwm;
	// Digital outputs to use with the L298N
	DigitalOutput *o1, *o2;

 public:
	/**
	 * @brief Construct a new L298N object
	 * 
	 * @param hat ServoHat object to use
	 * @param pwm_channel PWM channel on the ServoHat to use
	 * @param in1 Channel one on the breakout to use
	 * @param in2 Channel two on the breakout to use
	 */
	L298N(ServoHat *hat, uint8_t pwm_channel, uint8_t in1, uint8_t in2);

	/**
	 * @brief Set the SpeedController to a speed
	 * 
	 * @param speed Speed to set it to
	 */
	void Set(double speed);
};