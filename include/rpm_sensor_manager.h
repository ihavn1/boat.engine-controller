#pragma once

#include "sensor_config.h"
#include "sensesp/sensors/digital_input.h"
#include "sensesp/transforms/frequency.h"
#include "sensesp/signalk/signalk_output.h"

namespace BoatEngine {

/**
 * @brief Manages RPM sensor initialization and configuration
 * 
 * This class encapsulates all RPM sensor logic, following the Single
 * Responsibility Principle. It makes RPM sensor configuration independent
 * from other sensors.
 */
class RPMSensorManager {
public:
    /**
     * @brief Initialize the RPM sensor manager
     * @param pin GPIO pin for RPM input
     * @param read_delay_ms Read interval in milliseconds
     * @param multiplier Frequency to RPM multiplier
     */
    RPMSensorManager(uint8_t pin, unsigned int read_delay_ms, float multiplier);
    
    /**
     * @brief Set up the RPM sensor and its data pipeline
     * 
     * Creates the sensor, frequency converter, and SignalK output,
     * then connects them together.
     */
    void setupSensor();
    
    /**
     * @brief Get the digital input counter (for testing/debugging)
     */
    sensesp::DigitalInputCounter* getCounter() const { return counter_; }
    
    /**
     * @brief Get the frequency transform (for testing/debugging)
     */
    sensesp::Frequency* getFrequency() const { return frequency_; }
    
    /**
     * @brief Get the SignalK output (for testing/debugging)
     */
    sensesp::SKOutputFloat* getSKOutput() const { return sk_output_; }

private:
    uint8_t pin_;
    unsigned int read_delay_ms_;
    float multiplier_;
    
    // Pipeline components
    sensesp::DigitalInputCounter* counter_;
    sensesp::Frequency* frequency_;
    sensesp::SKOutputFloat* sk_output_;
};

} // namespace BoatEngine
