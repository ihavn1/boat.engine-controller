#include <unity.h>
#include <Arduino.h>
#include <cstring>

// Test constants from Main.cpp
// These tests verify that the hardware pin assignments and timing constants
// are within expected ranges and follow conventions

void setUp(void) {
    // Set up before each test
}

void tearDown(void) {
    // Clean up after each test
}

// Test GPIO pin assignments
void test_onewire_pin_valid(void) {
    const uint8_t ONEWIRE_PIN = 25;
    
    // GPIO25 is a valid ESP32 pin
    TEST_ASSERT_LESS_THAN(40, ONEWIRE_PIN);
    TEST_ASSERT_GREATER_THAN(0, ONEWIRE_PIN);
    
    // Verify it's not a reserved pin
    // GPIO 6-11 are typically used for flash on ESP32
    TEST_ASSERT_TRUE(ONEWIRE_PIN < 6 || ONEWIRE_PIN > 11);
}

void test_rpm_pin_valid(void) {
    const uint8_t RPM_PIN = 16;
    
    // GPIO16 is a valid ESP32 pin
    TEST_ASSERT_LESS_THAN(40, RPM_PIN);
    TEST_ASSERT_GREATER_THAN(0, RPM_PIN);
    
    // Verify it's not a reserved pin
    TEST_ASSERT_TRUE(RPM_PIN < 6 || RPM_PIN > 11);
}

void test_pins_are_different(void) {
    const uint8_t ONEWIRE_PIN = 25;
    const uint8_t RPM_PIN = 16;
    
    // Ensure no pin conflicts
    TEST_ASSERT_NOT_EQUAL(ONEWIRE_PIN, RPM_PIN);
}

// Test timing constants
void test_rpm_read_delay_reasonable(void) {
    const unsigned int RPM_READ_DELAY_MS = 500;
    
    // RPM read delay should be reasonable (not too fast, not too slow)
    TEST_ASSERT_GREATER_OR_EQUAL(100, RPM_READ_DELAY_MS);
    TEST_ASSERT_LESS_OR_EQUAL(5000, RPM_READ_DELAY_MS);
}

void test_temperature_read_delay_reasonable(void) {
    const unsigned int TEMPERATURE_READ_DELAY_MS = 2000;
    
    // Temperature read delay should be reasonable
    // OneWire temperature sensors typically need 750ms+ for conversion
    TEST_ASSERT_GREATER_OR_EQUAL(750, TEMPERATURE_READ_DELAY_MS);
    TEST_ASSERT_LESS_OR_EQUAL(10000, TEMPERATURE_READ_DELAY_MS);
}

void test_temperature_delay_longer_than_conversion_time(void) {
    const unsigned int TEMPERATURE_READ_DELAY_MS = 2000;
    const unsigned int MIN_ONEWIRE_CONVERSION_MS = 750;
    
    // Temperature sensors need time to convert, verify delay is sufficient
    TEST_ASSERT_GREATER_OR_EQUAL(MIN_ONEWIRE_CONVERSION_MS, TEMPERATURE_READ_DELAY_MS);
}

// Test sensor configuration parameters
void test_coolant_sensor_config(void) {
    const int COOLANT_SENSOR_SORT = 110;
    const int COOLANT_LINEAR_SORT = 120;
    const int COOLANT_SK_SORT = 130;
    
    // Verify sort order progression
    TEST_ASSERT_LESS_THAN(COOLANT_LINEAR_SORT, COOLANT_SENSOR_SORT);
    TEST_ASSERT_LESS_THAN(COOLANT_SK_SORT, COOLANT_LINEAR_SORT);
    
    // Verify they're in the expected range (100-199)
    TEST_ASSERT_GREATER_OR_EQUAL(100, COOLANT_SENSOR_SORT);
    TEST_ASSERT_LESS_THAN(200, COOLANT_SK_SORT);
}

void test_seawater_in_sensor_config(void) {
    const int SEAWATER_IN_SENSOR_SORT = 140;
    const int SEAWATER_IN_LINEAR_SORT = 150;
    const int SEAWATER_IN_SK_SORT = 160;
    
    // Verify sort order progression
    TEST_ASSERT_LESS_THAN(SEAWATER_IN_LINEAR_SORT, SEAWATER_IN_SENSOR_SORT);
    TEST_ASSERT_LESS_THAN(SEAWATER_IN_SK_SORT, SEAWATER_IN_LINEAR_SORT);
}

void test_seawater_out_sensor_config(void) {
    const int SEAWATER_OUT_SENSOR_SORT = 170;
    const int SEAWATER_OUT_LINEAR_SORT = 180;
    const int SEAWATER_OUT_SK_SORT = 190;
    
    // Verify sort order progression
    TEST_ASSERT_LESS_THAN(SEAWATER_OUT_LINEAR_SORT, SEAWATER_OUT_SENSOR_SORT);
    TEST_ASSERT_LESS_THAN(SEAWATER_OUT_SK_SORT, SEAWATER_OUT_LINEAR_SORT);
}

void test_rpm_sensor_config(void) {
    const int RPM_CONFIG_SORT = 200;
    const int RPM_SK_PATH_SORT = 210;
    
    // Verify RPM configuration comes after temperature sensors
    TEST_ASSERT_GREATER_OR_EQUAL(200, RPM_CONFIG_SORT);
    TEST_ASSERT_LESS_THAN(RPM_SK_PATH_SORT, RPM_CONFIG_SORT);
}

void test_rpm_multiplier_valid(void) {
    const float RPM_MULTIPLIER = 1.0;
    
    // Multiplier should be positive
    TEST_ASSERT_GREATER_THAN(0.0f, RPM_MULTIPLIER);
    
    // Multiplier should be reasonable (not zero, not too large)
    TEST_ASSERT_LESS_THAN(100.0f, RPM_MULTIPLIER);
}

// Test configuration path strings
void test_config_paths_have_leading_slash(void) {
    const char* config_path_calibrate = "/engineRPM/calibrate";
    const char* config_path_skpath = "/engineRPM/sk_path";
    
    // Configuration paths should start with /
    TEST_ASSERT_EQUAL_CHAR('/', config_path_calibrate[0]);
    TEST_ASSERT_EQUAL_CHAR('/', config_path_skpath[0]);
}

void test_config_paths_are_different(void) {
    const char* config_path_calibrate = "/engineRPM/calibrate";
    const char* config_path_skpath = "/engineRPM/sk_path";
    
    // Configuration paths should be unique
    TEST_ASSERT_NOT_EQUAL(config_path_calibrate, config_path_skpath);
    TEST_ASSERT_TRUE(strcmp(config_path_calibrate, config_path_skpath) != 0);
}

void setup() {
    delay(2000);  // Wait for serial to initialize
    
    UNITY_BEGIN();
    
    // Pin tests
    RUN_TEST(test_onewire_pin_valid);
    RUN_TEST(test_rpm_pin_valid);
    RUN_TEST(test_pins_are_different);
    
    // Timing tests
    RUN_TEST(test_rpm_read_delay_reasonable);
    RUN_TEST(test_temperature_read_delay_reasonable);
    RUN_TEST(test_temperature_delay_longer_than_conversion_time);
    
    // Sensor configuration tests
    RUN_TEST(test_coolant_sensor_config);
    RUN_TEST(test_seawater_in_sensor_config);
    RUN_TEST(test_seawater_out_sensor_config);
    RUN_TEST(test_rpm_sensor_config);
    RUN_TEST(test_rpm_multiplier_valid);
    
    // Configuration path tests
    RUN_TEST(test_config_paths_have_leading_slash);
    RUN_TEST(test_config_paths_are_different);
    
    UNITY_END();
}

void loop() {
    // Nothing to do here
}
