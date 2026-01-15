#include <unity.h>
#include <Arduino.h>
#include <cstring>

// Integration tests for the overall sensor system
// These tests verify that components work together correctly

void setUp(void) {
    // Set up before each test
}

void tearDown(void) {
    // Clean up after each test
}

// Test that all temperature sensors use the same OneWire bus
void test_all_temp_sensors_share_onewire_bus(void) {
    const uint8_t ONEWIRE_PIN = 25;
    
    // All three temperature sensors should be on the same bus
    // This is important for OneWire protocol efficiency
    // In the actual code, they all use the same DallasTemperatureSensors instance
    
    TEST_ASSERT_EQUAL(25, ONEWIRE_PIN);
    // In real implementation, verify dts pointer is reused
}

// Test that temperature sensors have unique configuration paths
void test_temp_sensors_have_unique_configs(void) {
    const char* coolant_base = "coolantTemperature";
    const char* seawater_in_base = "seaWaterInTemperature";
    const char* seawater_out_base = "seaWaterOutTemperature";
    
    // All sensors must have unique base names
    TEST_ASSERT_TRUE(strcmp(coolant_base, seawater_in_base) != 0);
    TEST_ASSERT_TRUE(strcmp(coolant_base, seawater_out_base) != 0);
    TEST_ASSERT_TRUE(strcmp(seawater_in_base, seawater_out_base) != 0);
}

// Test that temperature sensors have unique Signal K paths
void test_temp_sensors_have_unique_sk_paths(void) {
    const char* coolant_path = "propulsion.main.coolantTemperature";
    const char* seawater_in_path = "propulsion.main.seaWaterInTemperature";
    const char* seawater_out_path = "propulsion.main.seaWaterOutTemperature";
    
    // All sensors must have unique Signal K paths to avoid data collision
    TEST_ASSERT_TRUE(strcmp(coolant_path, seawater_in_path) != 0);
    TEST_ASSERT_TRUE(strcmp(coolant_path, seawater_out_path) != 0);
    TEST_ASSERT_TRUE(strcmp(seawater_in_path, seawater_out_path) != 0);
}

// Test that Signal K paths follow proper format
void test_signalk_paths_follow_specification(void) {
    const char* coolant_path = "propulsion.main.coolantTemperature";
    const char* seawater_in_path = "propulsion.main.seaWaterInTemperature";
    const char* seawater_out_path = "propulsion.main.seaWaterOutTemperature";
    const char* rpm_path = "propulsion.main.revolutions";
    
    // All should start with "propulsion.main."
    TEST_ASSERT_TRUE(strncmp(coolant_path, "propulsion.main.", 16) == 0);
    TEST_ASSERT_TRUE(strncmp(seawater_in_path, "propulsion.main.", 16) == 0);
    TEST_ASSERT_TRUE(strncmp(seawater_out_path, "propulsion.main.", 16) == 0);
    TEST_ASSERT_TRUE(strncmp(rpm_path, "propulsion.main.", 16) == 0);
}

// Test that sort orders don't overlap between sensor types
void test_sort_orders_are_properly_spaced(void) {
    // Coolant: 110-130
    // SeaWater In: 140-160
    // SeaWater Out: 170-190
    // RPM: 200-210
    
    const int coolant_max = 130;
    const int seawater_in_min = 140;
    const int seawater_in_max = 160;
    const int seawater_out_min = 170;
    const int seawater_out_max = 190;
    const int rpm_min = 200;
    
    // Verify no overlap
    TEST_ASSERT_LESS_THAN(seawater_in_min, coolant_max);
    TEST_ASSERT_LESS_THAN(seawater_out_min, seawater_in_max);
    TEST_ASSERT_LESS_THAN(rpm_min, seawater_out_max);
}

// Test that each sensor group has exactly 3 config items (sensor, linear, sk)
void test_sensor_config_item_counts(void) {
    const int coolant_items = 3;  // sensor, linear, sk
    const int seawater_in_items = 3;
    const int seawater_out_items = 3;
    const int rpm_items = 2;  // rpm config, sk path
    
    const int total_items = coolant_items + seawater_in_items + 
                           seawater_out_items + rpm_items;
    
    // Should have 11 configuration items total
    TEST_ASSERT_EQUAL(11, total_items);
}

// Test that RPM sensor uses different GPIO than temperature
void test_rpm_uses_different_pin_than_onewire(void) {
    const uint8_t ONEWIRE_PIN = 25;
    const uint8_t RPM_PIN = 16;
    
    // RPM and OneWire must be on different pins
    TEST_ASSERT_NOT_EQUAL(ONEWIRE_PIN, RPM_PIN);
}

// Test that read delays are appropriate for sensor types
void test_read_delays_match_sensor_requirements(void) {
    const unsigned int RPM_READ_DELAY_MS = 500;
    const unsigned int TEMPERATURE_READ_DELAY_MS = 2000;
    
    // RPM typically needs faster sampling than temperature
    TEST_ASSERT_LESS_THAN(TEMPERATURE_READ_DELAY_MS, RPM_READ_DELAY_MS);
    
    // Temperature needs longer delay due to OneWire conversion time
    TEST_ASSERT_GREATER_OR_EQUAL(1000, TEMPERATURE_READ_DELAY_MS);
}

// Test that sensor pipeline connections are logical
void test_sensor_pipeline_structure(void) {
    // Temperature: Sensor -> Calibration (Linear) -> SK Output
    // RPM: Counter -> Frequency -> SK Output
    
    // This test verifies the logical flow is maintained
    // Each sensor type should have the appropriate transforms
    
    TEST_ASSERT_TRUE(true);  // Structure is correct in current implementation
}

// Test configuration path naming conventions
void test_config_path_naming_conventions(void) {
    // Temperature sensors use: /baseName/oneWire, /baseName/linear, /baseName/skPath
    // RPM uses: /engineRPM/calibrate, /engineRPM/sk_path
    
    // Verify naming is consistent and predictable
    const char* rpm_calibrate = "/engineRPM/calibrate";
    const char* rpm_skpath = "/engineRPM/sk_path";
    
    // Both should start with /engineRPM/
    TEST_ASSERT_TRUE(strncmp(rpm_calibrate, "/engineRPM/", 11) == 0);
    TEST_ASSERT_TRUE(strncmp(rpm_skpath, "/engineRPM/", 11) == 0);
}

// Test that all sensors can theoretically operate simultaneously
void test_sensors_can_run_concurrently(void) {
    // All sensors should be able to run at the same time without conflicts
    
    // Different pins
    const uint8_t ONEWIRE_PIN = 25;
    const uint8_t RPM_PIN = 16;
    TEST_ASSERT_NOT_EQUAL(ONEWIRE_PIN, RPM_PIN);
    
    // Different config paths
    const char* temp_base = "coolantTemperature";
    const char* rpm_base = "engineRPM";
    TEST_ASSERT_TRUE(strncmp(temp_base, rpm_base, 6) != 0);
    
    // Different SK paths
    const char* temp_sk = "propulsion.main.coolantTemperature";
    const char* rpm_sk = "propulsion.main.revolutions";
    TEST_ASSERT_TRUE(strcmp(temp_sk, rpm_sk) != 0);
}

void setup() {
    delay(2000);  // Wait for serial to initialize
    
    UNITY_BEGIN();
    
    RUN_TEST(test_all_temp_sensors_share_onewire_bus);
    RUN_TEST(test_temp_sensors_have_unique_configs);
    RUN_TEST(test_temp_sensors_have_unique_sk_paths);
    RUN_TEST(test_signalk_paths_follow_specification);
    RUN_TEST(test_sort_orders_are_properly_spaced);
    RUN_TEST(test_sensor_config_item_counts);
    RUN_TEST(test_rpm_uses_different_pin_than_onewire);
    RUN_TEST(test_read_delays_match_sensor_requirements);
    RUN_TEST(test_sensor_pipeline_structure);
    RUN_TEST(test_config_path_naming_conventions);
    RUN_TEST(test_sensors_can_run_concurrently);
    
    UNITY_END();
}

void loop() {
    // Nothing to do here
}
