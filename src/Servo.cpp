#include "Servo.h"


Servo::Servo(ServoHat *hat, uint8_t channel) {
	pwm = new PWM(hat, channel);
	hat->RegisterMotor(this);
}

void Servo::SetAngle(uint8_t angle) {
	Servo::angle = angle;
	pwm->SetAngle(angle);
}

uint8_t Servo::GetAngle() {
	return angle;
}

void Servo::StopMotor() {
	pwm->SetAngle(90);
}