#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/components/uart/uart.h"
#include <vector>

#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif
//#ifdef USE_BINARY_SENSOR
//#include "esphome/components/binary_sensor/binary_sensor.h"
//#endif
//#ifdef USE_TEXT_SENSOR
//#include "esphome/components/text_sensor/text_sensor.h"
//#endif

namespace esphome {
namespace seplos_parser {

class SeplosParser : public uart::UARTDevice, public Component {
#ifdef USE_SENSOR
 protected:
  std::vector<sensor::Sensor *> sensors_;

 public:
  void register_sensor(sensor::Sensor *obj) { this->sensors_.push_back(obj); }
#endif
//#ifdef USE_BINARY_SENSOR
// protected:
//  std::vector<binary_sensor::BinarySensor *> binary_sensors_;
//
// public:
//  void register_binary_sensor(binary_sensor::BinarySensor *obj) { this->binary_sensors_.push_back(obj); }
//#endif
//#ifdef USE_TEXT_SENSOR
// protected:
//  std::vector<text_sensor::TextSensor *> text_sensors_;
//
// public:
//  void register_text_sensor(text_sensor::TextSensor *obj) { this->text_sensors_.push_back(obj); }
//#endif

  void set_bms_count(int bms_count);
  void setup() override;
  void loop() override;
  void dump_config() override;
  bool is_valid_header();
  size_t get_expected_length();
  bool validate_crc(size_t length);
  void process_packet(size_t length);
  uint16_t calculate_modbus_crc(const std::vector<uint8_t> &data, size_t length);

private:
  int bms_count_;  // Variable zur Speicherung von bms_count
  std::vector<uint8_t> buffer;

protected:
  std::vector<sensor::Sensor *> pack_voltage_;
  std::vector<sensor::Sensor *> current_;
  std::vector<sensor::Sensor *> remaining_capacity_;
  std::vector<sensor::Sensor *> total_capacity_;
  std::vector<sensor::Sensor *> total_discharge_capacity_;
  std::vector<sensor::Sensor *> soc_;
  std::vector<sensor::Sensor *> soh_;
  std::vector<sensor::Sensor *> cycle_count_;
};

}  // namespace seplos_parser
}  // namespace esphome
