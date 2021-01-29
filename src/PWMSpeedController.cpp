#include "PWMSpeedController.h"


PWMSpeedController::PWMSpeedController(ServoHat *hat, uint8_t channel) {
	pwm = new PWM(hat, channel);
}

void PWMSpeedController::Set(double speed) {
	pwm->Set(speed);
}