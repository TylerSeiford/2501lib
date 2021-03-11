#include <iostream>

#include <unistd.h>

#include "bcm2835.h"
#include "pca9685.h"

#include "ServoHat.h"


void ServoHat::SetInternal(uint8_t channel, uint16_t value, bool record) {
	hat->Write(channel, value);
	//std::cout << "set " << +channel << "," << +value << "\n";

	if(record)
		values[channel] = value;
}

void ServoHat::SetRaw(uint8_t channel, uint16_t value) {
	if(!enabled)
		return;

	SetInternal(channel, value, true);
}

void ServoHat::RegisterMotor(MotorSafety *motor) {
	motors.insert(motor);
}

ServoHat::ServoHat() {
	if (getuid() != 0) {
		fprintf(stderr, "Program is not started as \'root\' (sudo)\n");
		exit(-1);
	}

	if (bcm2835_init() != 1) {
		fprintf(stderr, "bcm2835_init() failed\n");
		exit(-2);
	}

	hat = new PCA9685();
	hat->SetInvert(false);
	hat->SetOutDriver(true);
	hat->SetFrequency(50);

	values = new uint16_t[MAX_CHANNELS];
	for(uint8_t i = 0; i < MAX_CHANNELS; i++) {
		values[i] = 0U;
	}

	enabled = false;
}

void ServoHat::Enable() {
	if(enabled)
		return;

	enabled = true;
}

void ServoHat::Disable() {
	if(!enabled)
		return;

	for(MotorSafety *motor : motors) {
		motor->StopMotor();
	}
	enabled = false;
}

bool ServoHat::IsEnabled() {
	return enabled;
}
