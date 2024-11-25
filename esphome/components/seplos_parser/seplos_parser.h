#ifndef ESPHOME_COMPONENTS_SEPLOS_PARSER_H
#define ESPHOME_COMPONENTS_SEPLOS_PARSER_H

#include "esphome.h"

namespace esphome {
namespace seplos_parser {

class SeplosParser : public UARTDevice {
 public:
  struct BMSData {
    Sensor *pack_voltage;
    Sensor *current;
    Sensor *remaining_capacity;
    Sensor *total_capacity;
    Sensor *total_discharge_capacity;
    Sensor *soc;
    Sensor *soh;
    Sensor *cycle;
    Sensor *average_cell_voltage;
    Sensor *average_cell_temp;
    Sensor *max_cell_voltage;
    Sensor *min_cell_voltage;
    Sensor *max_cell_temp;
    Sensor *min_cell_temp;
    Sensor *maxdiscurt;
    Sensor *maxchgcurt;
    Sensor *cell_1;
    Sensor *cell_2;
    Sensor *cell_3;
    Sensor *cell_4;
    Sensor *cell_5;
    Sensor *cell_6;
    Sensor *cell_7;
    Sensor *cell_8;
    Sensor *cell_9;
    Sensor *cell_10;
    Sensor *cell_11;
    Sensor *cell_12;
    Sensor *cell_13;
    Sensor *cell_14;
    Sensor *cell_15;
    Sensor *cell_16;
    Sensor *cell_temp_1;
    Sensor *cell_temp_2;
    Sensor *cell_temp_3;
    Sensor *cell_temp_4;
    Sensor *case_temp;
    Sensor *power_temp;
  };

  SeplosParser(UARTComponent *uart, int bms_count, int throttle_interval);
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

#endif  // ESPHOME_COMPONENTS_SEPLOS_PARSER_H

