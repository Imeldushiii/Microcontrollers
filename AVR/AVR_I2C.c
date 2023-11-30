#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


#define TWI_FREQ 100000L // I2C frequency in Hz (100 kHz)
#define SLAVE_ADDRESS 0x9 // Example slave address

void I2C_init() {
	TWBR = ((F_CPU / TWI_FREQ) - 16) / 2; // Set bit rate register for the desired frequency
	TWSR = 0; // Prescaler = 1
}

void I2C_start() {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // Start condition
	while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag to be set
}

void I2C_stop() {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); // Stop condition
	_delay_ms(1); // Allow time for the stop condition to complete
}

void I2C_send(uint8_t data) {
	TWDR = data; // Load data into data register
	TWCR = (1 << TWINT) | (1 << TWEN); // Start data transmission
	while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag to be set
}

int main() {
	// Initialize I2C
	I2C_init();

	// Start condition
	

	while (1) {
		I2C_start();

		// Send slave address with write bit
		I2C_send((SLAVE_ADDRESS << 1) | 0); // 0 for write mode

		// Send data to the slave
		uint8_t dataToSend = 15; // Example data to send
		
		I2C_send(dataToSend);

		// End communication with stop condition
		I2C_stop();
	}

	return 0;
}