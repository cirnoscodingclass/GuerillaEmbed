#include "mbed.h"

// Transfer and recieve data pins on NUCLEO-L476RG 
#define UART_TX PA_2
#define UART_RX PA_3

//Soil sensor SLT5006 registers
//State registers
#define SNSR_CTRL   0x07
#define SNSR_STATE  0x08

//Sensor registers
#define TEMP        0x13 // Temperature
#define TEMP2       0x14
#define EC_BULK     0x15 // Electrical conductivity ions in the water
#define EC_BULK2    0x16
#define VWC         0x19 // Volumetric water content
#define VWC2        0x1A
#define EC_PORE     0x1F // Electrical conductivity of ions in the soil
#define EC_PORE2    0x20

UnbufferedSerial uart(UART_TX, UART_RX);

// Writes a value to a register of the soil sensor by sending the register and value over UART.
void writeRegister(uint8_t reg, uint8_t value) {
    char data[2] = {reg, value};
    uart.write(data, 2);
}

// Reads a value from a register of the soil sensor by sending the register and receiving the data over UART.
uint8_t readRegister(uint8_t reg) {
    uart.write(&reg, 1);
    char data;
    uart.read(&data, 1);
    return data;
}

//  Function reads the measurement data from various registers of the soil sensor and prints them to the console.
void readMeasurementData() {
    uint8_t temp1 = readRegister(TEMP);
    uint8_t temp2 = readRegister(TEMP2);
    uint8_t ec_bulk1 = readRegister(EC_BULK);
    uint8_t ec_bulk2 = readRegister(EC_BULK2);
    uint8_t vwc1 = readRegister(VWC);
    uint8_t vwc2 = readRegister(VWC2);
    uint8_t ec_pore1 = readRegister(EC_PORE);
    uint8_t ec_pore2 = readRegister(EC_PORE2);

    printf("Temp: 0x%02x%02x\n", temp1, temp2);
    printf("EC_BULK: 0x%02x%02x\n", ec_bulk1, ec_bulk2);
    printf("VWC: 0x%02x%02x\n", vwc1, vwc2);
    printf("EC_PORE: 0x%02x%02x\n", ec_pore1, ec_pore2);
}

int main() {
    //  start the measurement by writing the value 0x01 to the SNSR_CTRL register.
    writeRegister(SNSR_CTRL, 0x01);

    //  checks the state of the soil sensor by reading the SNSR_STATE register using the readRegister function.
    while (true) {
        // Check sensor state
        uint8_t state = readRegister(SNSR_STATE);
        if (state == 0x01) {
            readMeasurementData();
        } 
        if (state == 0x00) {
            printf("Still under measuring or not start to measure");
        }

        ThisThread::sleep_for(1000ms);
    }
}
