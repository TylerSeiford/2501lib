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

void PWMSpeedController::SetMaxUs(uint16_t max_us) {
	pwm->SetMaxUs(max_us);
}

void PWMSpeedController::SetCenterUs(uint16_t center_us) {
	pwm->SetMaxUs(center_us);
}

void PWMSpeedController::SetMinUs(uint16_t min_us) {
	pwm->SetMaxUs(min_us);
}