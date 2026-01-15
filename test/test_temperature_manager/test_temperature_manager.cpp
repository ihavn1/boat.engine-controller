#include <Arduino.h>
#include <unity.h>
#include "sensor_config.h"

using namespace BoatEngine;

// Test that BoatSensorConfig temperature sensor definitions are accessible
void test_temperature_sensor_count(void) {
    // We have 3 temperature sensors defined
    // This verifies the configuration is accessible
    TEST_ASSERT_EQUAL(25, BoatSensorConfig::ONEWIRE_PIN);
    TEST_ASSERT_EQUAL(2000, BoatSensorConfig::TEMPERATURE_READ_DELAY_MS);
}

// Test coolant temperature sensor configuration
void test_coolant_sensor_definition(void) {
    const BoatSensorConfig::TemperatureSensorDef& sensor = BoatSensorConfig::COOLANT_TEMP;
    
    TEST_ASSERT_NOT_NULL(sensor.base_name);
    TEST_ASSERT_NOT_NULL(sensor.human_label);
    TEST_ASSERT_NOT_NULL(sensor.signal_k_path);
    
    TEST_ASSERT_EQUAL_STRING("coolantTemperature", sensor.base_name);
    TEST_ASSERT_EQUAL_STRING("Coolant Temperature", sensor.human_label);
    TEST_ASSERT_EQUAL_STRING("propulsion.main.coolantTemperature", sensor.signal_k_path);
}

// Test seawater inlet temperature sensor configuration
void test_seawater_in_sensor_definition(void) {
    const BoatSensorConfig::TemperatureSensorDef& sensor = BoatSensorConfig::SEAWATER_IN_TEMP;
    
    TEST_ASSERT_NOT_NULL(sensor.base_name);
    TEST_ASSERT_NOT_NULL(sensor.human_label);
    TEST_ASSERT_NOT_NULL(sensor.signal_k_path);
    
    TEST_ASSERT_EQUAL_STRING("seaWaterInTemperature", sensor.base_name);
    TEST_ASSERT_EQUAL_STRING("Sea Water In Temperature", sensor.human_label);
    TEST_ASSERT_EQUAL_STRING("propulsion.main.seaWaterInTemperature", sensor.signal_k_path);
}

// Test seawater outlet temperature sensor configuration
void test_seawater_out_sensor_definition(void) {
    const BoatSensorConfig::TemperatureSensorDef& sensor = BoatSensorConfig::SEAWATER_OUT_TEMP;
    
    TEST_ASSERT_NOT_NULL(sensor.base_name);
    TEST_ASSERT_NOT_NULL(sensor.human_label);
    TEST_ASSERT_NOT_NULL(sensor.signal_k_path);
    
    TEST_ASSERT_EQUAL_STRING("seaWaterOutTemperature", sensor.base_name);
    TEST_ASSERT_EQUAL_STRING("Sea Water Out Temperature", sensor.human_label);
    TEST_ASSERT_EQUAL_STRING("propulsion.main.seaWaterOutTemperature", sensor.signal_k_path);
}

// Test temperature sensor sort orders are defined
void test_temperature_sort_orders(void) {
    // Sort orders should be valid integers
    TEST_ASSERT_GREATER_OR_EQUAL(0, BoatSensorConfig::COOLANT_TEMP.sensor_sort_order);
    TEST_ASSERT_GREATER_OR_EQUAL(0, BoatSensorConfig::SEAWATER_IN_TEMP.sensor_sort_order);
    TEST_ASSERT_GREATER_OR_EQUAL(0, BoatSensorConfig::SEAWATER_OUT_TEMP.sensor_sort_order);
}

// Test temperature sensor sort orders are unique
void test_temperature_sort_orders_unique(void) {
    TEST_ASSERT_NOT_EQUAL(BoatSensorConfig::COOLANT_TEMP.sensor_sort_order,
                          BoatSensorConfig::SEAWATER_IN_TEMP.sensor_sort_order);
    TEST_ASSERT_NOT_EQUAL(BoatSensorConfig::COOLANT_TEMP.sensor_sort_order,
                          BoatSensorConfig::SEAWATER_OUT_TEMP.sensor_sort_order);
    TEST_ASSERT_NOT_EQUAL(BoatSensorConfig::SEAWATER_IN_TEMP.sensor_sort_order,
                          BoatSensorConfig::SEAWATER_OUT_TEMP.sensor_sort_order);
}

// Test temperature sensor Signal K paths are different
void test_temperature_sk_paths_unique(void) {
    TEST_ASSERT_NOT_EQUAL(
        strcmp(BoatSensorConfig::COOLANT_TEMP.signal_k_path, 
               BoatSensorConfig::SEAWATER_IN_TEMP.signal_k_path), 
        0);
    TEST_ASSERT_NOT_EQUAL(
        strcmp(BoatSensorConfig::COOLANT_TEMP.signal_k_path, 
               BoatSensorConfig::SEAWATER_OUT_TEMP.signal_k_path), 
        0);
    TEST_ASSERT_NOT_EQUAL(
        strcmp(BoatSensorConfig::SEAWATER_IN_TEMP.signal_k_path, 
               BoatSensorConfig::SEAWATER_OUT_TEMP.signal_k_path), 
        0);
}

// Test temperature configuration values are reasonable
void test_temperature_configuration_validity(void) {
    // Pin should be a valid GPIO pin (0-39 for ESP32)
    TEST_ASSERT_GREATER_OR_EQUAL(0, BoatSensorConfig::ONEWIRE_PIN);
    TEST_ASSERT_LESS_THAN(40, BoatSensorConfig::ONEWIRE_PIN);
    
    // Read delay should be at least 750ms (DS18B20 conversion takes time)
    TEST_ASSERT_GREATER_OR_EQUAL(750, BoatSensorConfig::TEMPERATURE_READ_DELAY_MS);
    TEST_ASSERT_LESS_THAN(10000, BoatSensorConfig::TEMPERATURE_READ_DELAY_MS);
}

void setup() {
    delay(2000); // Service delay
    UNITY_BEGIN();
    
    RUN_TEST(test_temperature_sensor_count);
    RUN_TEST(test_coolant_sensor_definition);
    RUN_TEST(test_seawater_in_sensor_definition);
    RUN_TEST(test_seawater_out_sensor_definition);
    RUN_TEST(test_temperature_sort_orders);
    RUN_TEST(test_temperature_sort_orders_unique);
    RUN_TEST(test_temperature_sk_paths_unique);
    RUN_TEST(test_temperature_configuration_validity);
    
    UNITY_END();
}

void loop() {
    // Nothing to do here
}
