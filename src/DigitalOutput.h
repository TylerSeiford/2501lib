#pragma once

#include <cstdint>


class DigitalOutput {
 private:
	// Pin for the DigitalInput to be on
	uint8_t pin;

 public:
	/**
	 * @brief Construct a new Digital Output object
	 * 
	 * @param pin Pin for the Digital Output
	 */
	DigitalOutput(uint8_t pin);

	/**
	 * @brief Set the state of the digital output
	 * 
	 * @param value true for HIGH, false for LOW
	 */
	void Set(bool value);
};
