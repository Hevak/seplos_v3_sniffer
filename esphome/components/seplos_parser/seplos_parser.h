#pragma once

#include "esphome/core/component.h"

namespace esphome {
namespace seplos_parser {

class SeplosParser : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

 private:
  int bms_count_;  // Anzahl der BMS-Geräte
};


}  // namespace seplos_parser
}  // namespace esphome
