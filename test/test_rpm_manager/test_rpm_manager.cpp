#include <Arduino.h>
#include <unity.h>
#include <cstring>
#include "sensor_config.h"

using namespace BoatEngine;

// Test RPM sensor GPIO pin configuration
void test_rpm_pin_configuration(void) {
    TEST_ASSERT_EQUAL(16, BoatSensorConfig::RPM_PIN);
}

// Test RPM read delay configuration
void test_rpm_read_delay_configuration(void) {
    TEST_ASSERT_EQUAL(500, BoatSensorConfig::RPM_READ_DELAY_MS);
}

// Test RPM multiplier configuration
void test_rpm_multiplier_configuration(void) {
    TEST_ASSERT_EQUAL(1.0, BoatSensorConfig::RPM_MULTIPLIER);
}

// Test RPM Signal K path
void test_rpm_sk_path(void) {
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::RPM_SK_PATH);
    TEST_ASSERT_EQUAL_STRING("propulsion.main.revolutions", BoatSensorConfig::RPM_SK_PATH);
}

// Test RPM Signal K path configuration
void test_rpm_sk_path_config(void) {
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::RPM_CONFIG_PATH_SKPATH);
    // Verify it's a valid string
    TEST_ASSERT_GREATER_THAN(0, strlen(BoatSensorConfig::RPM_CONFIG_PATH_SKPATH));
}

// Test RPM calibrate configuration path
void test_rpm_calibrate_path(void) {
    TEST_ASSERT_NOT_NULL(BoatSensorConfig::RPM_CONFIG_PATH_CALIBRATE);
    TEST_ASSERT_EQUAL_STRING("/engineRPM/calibrate", BoatSensorConfig::RPM_CONFIG_PATH_CALIBRATE);
}

// Test RPM configuration values are reasonable
void test_rpm_configuration_validity(void) {
    // Pin should be a valid GPIO pin (0-39 for ESP32)
    TEST_ASSERT_GREATER_OR_EQUAL(0, BoatSensorConfig::RPM_PIN);
    TEST_ASSERT_LESS_THAN(40, BoatSensorConfig::RPM_PIN);
    
    // Read delay should be reasonable (50ms to 5000ms)
    TEST_ASSERT_GREATER_OR_EQUAL(50, BoatSensorConfig::RPM_READ_DELAY_MS);
    TEST_ASSERT_LESS_THAN(5000, BoatSensorConfig::RPM_READ_DELAY_MS);
    
    // Multiplier should be positive and reasonable (0.1 to 10.0)
    TEST_ASSERT_GREATER_THAN(0.0, BoatSensorConfig::RPM_MULTIPLIER);
    TEST_ASSERT_LESS_THAN(10.0, BoatSensorConfig::RPM_MULTIPLIER);
}

// Test RPM and temperature use different pins
void test_rpm_and_temperature_pins_different(void) {
    TEST_ASSERT_NOT_EQUAL(BoatSensorConfig::RPM_PIN, BoatSensorConfig::ONEWIRE_PIN);
}

// Test RPM read delay is faster than temperature (for responsiveness)
void test_rpm_delay_faster_than_temperature(void) {
    // RPM should update more frequently than temperature
    TEST_ASSERT_LESS_THAN(BoatSensorConfig::TEMPERATURE_READ_DELAY_MS, BoatSensorConfig::RPM_READ_DELAY_MS);
}

void setup() {
    delay(2000); // Service delay
    UNITY_BEGIN();
    
    RUN_TEST(test_rpm_pin_configuration);
    RUN_TEST(test_rpm_read_delay_configuration);
    RUN_TEST(test_rpm_multiplier_configuration);
    RUN_TEST(test_rpm_sk_path);
    RUN_TEST(test_rpm_sk_path_config);
    RUN_TEST(test_rpm_calibrate_path);
    RUN_TEST(test_rpm_configuration_validity);
    RUN_TEST(test_rpm_and_temperature_pins_different);
    RUN_TEST(test_rpm_delay_faster_than_temperature);
    
    UNITY_END();
}

void loop() {
    // Nothing to do here
}
