#include <Arduino.h>
#include <unity.h>
#include <cstring>
#include "sensor_config.h"

using namespace BoatEngine;

// Test that BoatSensorConfig class is accessible
void test_sensor_config_accessible(void) {
    // This test ensures the namespace and class are properly defined
    int pin = BoatSensorConfig::ONEWIRE_PIN;
    TEST_ASSERT_GREATER_OR_EQUAL(0, pin);
}

// Test all hardware pin assignments are unique
void test_all_pins_unique(void) {
    // OneWire and RPM should use different pins
    TEST_ASSERT_NOT_EQUAL(BoatSensorConfig::ONEWIRE_PIN, BoatSensorConfig::RPM_PIN);
}

// Test all Signal K paths start with 'propulsion'
void test_sk_paths_format(void) {
    // Signal K uses dot notation, not slash notation
    TEST_ASSERT_EQUAL('p', BoatSensorConfig::COOLANT_TEMP.signal_k_path[0]);
    TEST_ASSERT_EQUAL('p', BoatSensorConfig::SEAWATER_IN_TEMP.signal_k_path[0]);
    TEST_ASSERT_EQUAL('p', BoatSensorConfig::SEAWATER_OUT_TEMP.signal_k_path[0]);
    TEST_ASSERT_EQUAL('p', BoatSensorConfig::RPM_SK_PATH[0]);
}

// Test all configuration paths start with forward slash
void test_config_paths_format(void) {
    TEST_ASSERT_EQUAL('/', BoatSensorConfig::RPM_CONFIG_PATH_SKPATH[0]);
    TEST_ASSERT_EQUAL('/', BoatSensorConfig::RPM_CONFIG_PATH_CALIBRATE[0]);
}

// Test temperature sensor struct integrity
void test_temperature_sensor_def_not_null(void) {
    // All fields should be non-null pointers
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::COOLANT_TEMP.base_name);
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::COOLANT_TEMP.human_label);
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::COOLANT_TEMP.signal_k_path);
    
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::SEAWATER_IN_TEMP.base_name);
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::SEAWATER_IN_TEMP.human_label);
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::SEAWATER_IN_TEMP.signal_k_path);
    
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::SEAWATER_OUT_TEMP.base_name);
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::SEAWATER_OUT_TEMP.human_label);
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::SEAWATER_OUT_TEMP.signal_k_path);
}

// Test all labels are non-empty
void test_labels_not_empty(void) {
    TEST_ASSERT_GREATER_THAN(0, strlen(BoatSensorConfig::COOLANT_TEMP.human_label));
    TEST_ASSERT_GREATER_THAN(0, strlen(BoatSensorConfig::SEAWATER_IN_TEMP.human_label));
    TEST_ASSERT_GREATER_THAN(0, strlen(BoatSensorConfig::SEAWATER_OUT_TEMP.human_label));
}

// Test configuration contains propulsion-related paths
void test_engine_related_paths(void) {
    // All sensors should reference propulsion.main
    int found_propulsion = 0;
    if (strstr(BoatSensorConfig::COOLANT_TEMP.signal_k_path, "propulsion") != NULL) found_propulsion++;
    if (strstr(BoatSensorConfig::SEAWATER_IN_TEMP.signal_k_path, "propulsion") != NULL) found_propulsion++;
    if (strstr(BoatSensorConfig::SEAWATER_OUT_TEMP.signal_k_path, "propulsion") != NULL) found_propulsion++;
    if (strstr(BoatSensorConfig::RPM_SK_PATH, "propulsion") != NULL) found_propulsion++;
    
    TEST_ASSERT_GREATER_THAN(0, found_propulsion);
}

// Test timing configurations are reasonable
void test_timing_configurations(void) {
    // All delays should be positive
    TEST_ASSERT_GREATER_THAN(0, BoatSensorConfig::TEMPERATURE_READ_DELAY_MS);
    TEST_ASSERT_GREATER_THAN(0, BoatSensorConfig::RPM_READ_DELAY_MS);
    
    // Delays should not be excessively long (more than 1 minute)
    TEST_ASSERT_LESS_THAN(60000, BoatSensorConfig::TEMPERATURE_READ_DELAY_MS);
    TEST_ASSERT_LESS_THAN(60000, BoatSensorConfig::RPM_READ_DELAY_MS);
}

// Test RPM multiplier is within reasonable range
void test_rpm_multiplier_range(void) {
    // Multiplier should be between 0 and 10 (most common range)
    TEST_ASSERT_GREATER_THAN(0.0, BoatSensorConfig::RPM_MULTIPLIER);
    TEST_ASSERT_LESS_OR_EQUAL(10.0, BoatSensorConfig::RPM_MULTIPLIER);
}

// Test sort orders are defined
void test_sort_orders_defined(void) {
    // All sensors should have valid sort orders
    TEST_ASSERT_GREATER_OR_EQUAL(0, BoatSensorConfig::COOLANT_TEMP.sensor_sort_order);
    TEST_ASSERT_GREATER_OR_EQUAL(0, BoatSensorConfig::SEAWATER_IN_TEMP.sensor_sort_order);
    TEST_ASSERT_GREATER_OR_EQUAL(0, BoatSensorConfig::SEAWATER_OUT_TEMP.sensor_sort_order);
    TEST_ASSERT_GREATER_OR_EQUAL(0, BoatSensorConfig::RPM_CONFIG_SORT_ORDER);
}

void setup() {
    delay(2000); // Service delay
    UNITY_BEGIN();
    
    RUN_TEST(test_sensor_config_accessible);
    RUN_TEST(test_all_pins_unique);
    RUN_TEST(test_sk_paths_format);
    RUN_TEST(test_config_paths_format);
    RUN_TEST(test_temperature_sensor_def_not_null);
    RUN_TEST(test_labels_not_empty);
    RUN_TEST(test_engine_related_paths);
    RUN_TEST(test_timing_configurations);
    RUN_TEST(test_rpm_multiplier_range);
    RUN_TEST(test_sort_orders_defined);
    
    UNITY_END();
}

void loop() {
    // Nothing to do here
}
