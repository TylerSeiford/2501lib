#pragma once

#include <cstdint>


class DigitalInput {
 private:
	// Pin for the DigitalInput to be on
	uint8_t pin;

 public:
	/**
	 * @brief Construct a new Digital Input object
	 * 
	 * @param pin Pin for the Digital Input
	 */
	DigitalInput(uint8_t pin);

	/**
	 * @brief Get the current status of the Digital Input
	 * 
	 * @return true Input is HIGH
	 * @return false Input is LOW
	 */
	bool Get();

	/**
	 * @brief Set the input to pull up
	 */
	void SetPullUp();

	/**
	 * @brief Set the input to no pull
	 */
	void SetPullOff();

	/**
	 * @brief Set the input to pull down
	 */
	void SetPullDown();
};
