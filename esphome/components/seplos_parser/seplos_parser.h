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

  // Setter für bms_count
  void set_bms_count(int bms_count);

  // Konfiguration der Sensoren über die YAML-Datei
  void add_sensor(sensor::Sensor *sensor);

  // Hier fügen wir eine Liste von Sensoren hinzu
  std::vector<sensor::Sensor *> sensors_;

  // Sensoren für jedes BMS
  std::vector<sensor::Sensor *> pack_voltages;
  std::vector<sensor::Sensor *> currents;
  std::vector<sensor::Sensor *> socs;
  std::vector<sensor::Sensor *> sohs;
  std::vector<sensor::Sensor *> cycle_counts;

 private:
  uart::UARTComponent *uart_parent_{nullptr};  // Standardmäßig auf nullptr
  int bms_count_{1};  // Anzahl der BMS-Geräte, Standardmäßig ein BMS
};


}  // namespace seplos_parser
}  // namespace esphome
