#include "temperature_sensor_manager.h"
#include "onewire_helper.h"

namespace BoatEngine {

TemperatureSensorManager::TemperatureSensorManager(uint8_t onewire_pin, 
                                                   unsigned int read_delay_ms)
    : dts_(new sensesp::onewire::DallasTemperatureSensors(onewire_pin))
    , read_delay_ms_(read_delay_ms) {
}

void TemperatureSensorManager::setupSensors() {
    // Set up all pre-configured temperature sensors
    addSensor(BoatSensorConfig::COOLANT_TEMP);
    addSensor(BoatSensorConfig::SEAWATER_IN_TEMP);
    addSensor(BoatSensorConfig::SEAWATER_OUT_TEMP);
}

void TemperatureSensorManager::addSensor(const BoatSensorConfig::TemperatureSensorDef& config) {
    add_onewire_temp(
        dts_,
        read_delay_ms_,
        config.base_name,
        config.signal_k_path,
        config.human_label,
        config.sensor_sort_order,
        config.linear_sort_order,
        config.sk_sort_order
    );
}

} // namespace BoatEngine
