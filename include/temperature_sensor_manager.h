#pragma once

#include "sensor_config.h"
#include "sensesp_onewire/onewire_temperature.h"

namespace BoatEngine {

/**
 * @brief Manages temperature sensor initialization and configuration
 * 
 * This class follows the Single Responsibility Principle by handling
 * only temperature sensor setup. It also demonstrates the Open/Closed
 * Principle - you can extend sensor types without modifying this class.
 */
class TemperatureSensorManager {
public:
    /**
     * @brief Initialize the temperature sensor manager
     * @param onewire_pin GPIO pin for the OneWire bus
     * @param read_delay_ms Read interval in milliseconds
     */
    TemperatureSensorManager(uint8_t onewire_pin, unsigned int read_delay_ms);
    
    /**
     * @brief Set up all configured temperature sensors
     * 
     * This method iterates through all defined temperature sensors
     * and initializes them using the helper function.
     */
    void setupSensors();
    
    /**
     * @brief Add a single temperature sensor
     * @param config Sensor configuration definition
     */
    void addSensor(const BoatSensorConfig::TemperatureSensorDef& config);
    
    /**
     * @brief Get the Dallas Temperature Sensors instance
     * @return Pointer to DTS instance (for testing/debugging)
     */
    sensesp::onewire::DallasTemperatureSensors* getDTS() const { return dts_; }

private:
    sensesp::onewire::DallasTemperatureSensors* dts_;
    unsigned int read_delay_ms_;
};

} // namespace BoatEngine
