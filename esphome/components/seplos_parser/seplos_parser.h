#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"


namespace esphome {
namespace seplos_parser {

class SeplosParser : public Component {
 public:
  SeplosParser(uart::UARTComponent *uart_parent, int bms_count) {
    this->uart_parent_ = uart_parent;
    this->bms_count_ = bms_count;
  }
  void setup() override;
  void loop() override;
  void dump_config() override;

 private:
  int bms_count_;  // Anzahl der BMS-Geräte
};


}  // namespace seplos_parser
}  // namespace esphome
