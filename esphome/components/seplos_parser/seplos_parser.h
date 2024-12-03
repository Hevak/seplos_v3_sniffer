#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include <vector>



namespace esphome {
namespace seplos_parser {

class SeplosParser : public Component {
 public:
  SeplosParser(esphome::uart::UARTComponent *uart_parent, int bms_count);
  void setup() override;
  void loop() override;
  void dump_config() override;
  void set_uart_parent(esphome::uart::UARTComponent *uart_parent);

  // Sensoren für jedes BMS
  std::vector<sensor::Sensor *> pack_voltages;
  std::vector<sensor::Sensor *> currents;
  std::vector<sensor::Sensor *> socs;
  std::vector<sensor::Sensor *> sohs;
  std::vector<sensor::Sensor *> cycle_counts;

 private:
  uart::UARTComponent *uart_parent_;
  int bms_count_;  // Anzahl der BMS-Geräte
};


}  // namespace seplos_parser
}  // namespace esphome
