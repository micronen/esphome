#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/macros.h"
#include "esphome/core/helpers.h"

#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif
#ifdef USE_TEXT_SENSOR
#include "esphome/components/text_sensor/text_sensor.h"
#endif
#ifdef USE_BINARY_SENSOR
#include "esphome/components/binary_sensor/binary_sensor.h"
#endif

namespace esphome {
namespace debug {

class DebugComponent : public PollingComponent {
 public:
  void loop() override;
  void update() override;
  float get_setup_priority() const override;
  void dump_config() override;

#ifdef USE_TEXT_SENSOR
  void set_device_info_sensor(text_sensor::TextSensor *device_info) { device_info_ = device_info; }
#endif  // USE_TEXT_SENSOR
#ifdef USE_SENSOR
  void set_free_sensor(sensor::Sensor *free_sensor) { free_sensor_ = free_sensor; }
  void set_block_sensor(sensor::Sensor *block_sensor) { block_sensor_ = block_sensor; }
#if defined(USE_ESP8266) && USE_ARDUINO_VERSION_CODE >= VERSION_CODE(2, 5, 2)
  void set_fragmentation_sensor(sensor::Sensor *fragmentation_sensor) { fragmentation_sensor_ = fragmentation_sensor; }
#endif
  void set_loop_time_sensor(sensor::Sensor *loop_time_sensor) { loop_time_sensor_ = loop_time_sensor; }
  void set_loop_delay_sensor(sensor::Sensor *loop_delay_sensor) { loop_delay_sensor_ = loop_delay_sensor; }
#endif  // USE_SENSOR

#ifdef USE_BINARY_SENSOR
  void set_loop_high_frequency(binary_sensor::BinarySensor *loop_high_frequency) {
    loop_high_frequency_ = loop_high_frequency;
  }
#endif // USE_BINARY_SENSOR

#if defined(USE_SENSOR) && defined(USE_TEXT_SENSOR)
  void set_blocking_sensor(text_sensor::TextSensor *blocking_sensor) { blocking_sensor_ = blocking_sensor; }
  void set_blocking_sensor_time(sensor::Sensor *blocking_sensor_time) { blocking_sensor_time_ = blocking_sensor_time; }
#endif  // USE_SENSOR && USE_TEXT_SENSOR

 protected:
  uint32_t free_heap_{};

#ifdef USE_SENSOR
  uint32_t last_loop_timetag_{0};
  uint32_t max_loop_time_{0};

  sensor::Sensor *free_sensor_{nullptr};
  sensor::Sensor *block_sensor_{nullptr};
#if defined(USE_ESP8266) && USE_ARDUINO_VERSION_CODE >= VERSION_CODE(2, 5, 2)
  sensor::Sensor *fragmentation_sensor_{nullptr};
#endif
  sensor::Sensor *loop_time_sensor_{nullptr};
  sensor::Sensor *loop_delay_sensor_{nullptr};
#endif  // USE_SENSOR

#ifdef USE_BINARY_SENSOR
  binary_sensor::BinarySensor *loop_high_frequency_{nullptr};
#endif // USE_BINARY_SENSOR

#ifdef USE_TEXT_SENSOR
  text_sensor::TextSensor *device_info_{nullptr};
#endif  // USE_TEXT_SENSOR

#if defined(USE_SENSOR) && defined(USE_TEXT_SENSOR)
  sensor::Sensor *blocking_sensor_time_{nullptr};
  text_sensor::TextSensor *blocking_sensor_{nullptr};
#endif  // USE_SENSOR && USE_TEXT_SENSOR
};

}  // namespace debug
}  // namespace esphome
