#include "PWMSpeedController.h"


PWMSpeedController::PWMSpeedController(ServoHat *hat, uint8_t channel) {
	pwm = new PWM(hat, channel);
	hat->RegisterMotor(this);
}

void PWMSpeedController::Set(double speed) {
	pwm->Set(speed);
}

void PWMSpeedController::StopMotor() {
	Set(0.0);
}