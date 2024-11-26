#ifndef ESPHOME_COMPONENTS_SEPLOS_PARSER_H
#define ESPHOME_COMPONENTS_SEPLOS_PARSER_H

#include "esphome.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"  // Sensor-Klasse importieren
#include "esphome/components/sensor/filter.h"


namespace esphome {
namespace seplos_parser {

class SeplosParser : public esphome::Component, public esphome::uart::UARTDevice {
 public:
  struct BMSData {
    esphome::sensor::Sensor *pack_voltage;
    esphome::sensor::Sensor *current;
    esphome::sensor::Sensor *remaining_capacity;
    esphome::sensor::Sensor *total_capacity;
    esphome::sensor::Sensor *total_discharge_capacity;
    esphome::sensor::Sensor *soc;
    esphome::sensor::Sensor *soh;
    esphome::sensor::Sensor *cycle;
    esphome::sensor::Sensor *average_cell_voltage;
    esphome::sensor::Sensor *average_cell_temp;
    esphome::sensor::Sensor *max_cell_voltage;
    esphome::sensor::Sensor *min_cell_voltage;
    esphome::sensor::Sensor *max_cell_temp;
    esphome::sensor::Sensor *min_cell_temp;
    esphome::sensor::Sensor *maxdiscurt;
    esphome::sensor::Sensor *maxchgcurt;
    esphome::sensor::Sensor *cell_1;
    esphome::sensor::Sensor *cell_2;
    esphome::sensor::Sensor *cell_3;
    esphome::sensor::Sensor *cell_4;
    esphome::sensor::Sensor *cell_5;
    esphome::sensor::Sensor *cell_6;
    esphome::sensor::Sensor *cell_7;
    esphome::sensor::Sensor *cell_8;
    esphome::sensor::Sensor *cell_9;
    esphome::sensor::Sensor *cell_10;
    esphome::sensor::Sensor *cell_11;
    esphome::sensor::Sensor *cell_12;
    esphome::sensor::Sensor *cell_13;
    esphome::sensor::Sensor *cell_14;
    esphome::sensor::Sensor *cell_15;
    esphome::sensor::Sensor *cell_16;
    esphome::sensor::Sensor *cell_temp_1;
    esphome::sensor::Sensor *cell_temp_2;
    esphome::sensor::Sensor *cell_temp_3;
    esphome::sensor::Sensor *cell_temp_4;
    esphome::sensor::Sensor *case_temp;
    esphome::sensor::Sensor *power_temp;
  };

  SeplosParser(esphome::uart::UARTComponent *uart, int bms_count, int throttle_interval);
  void setup() override;
  void loop() override;

 private:
  std::vector<uint8_t> buffer;
  std::vector<BMSData> bms;
  int max_bms_count;
  int throttle_interval_;

  bool is_valid_header();
  size_t get_expected_length();
  bool validate_crc(size_t length);
  void process_packet(size_t length);
  uint16_t calculate_modbus_crc(const std::vector<uint8_t> &data, size_t length);
};

}  // namespace seplos_parser
}  // namespace esphome

#endif
