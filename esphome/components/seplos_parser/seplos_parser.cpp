#include "esphome/core/log.h"
#include "seplos_parser.h"

namespace esphome {
namespace seplos_parser {

static const char *TAG = "seplos_parser.component";

SeplosParser::SeplosParser(uart::UARTComponent *uart_parent, int bms_count) {
  this->uart_parent_ = uart_parent;
  this->bms_count_ = bms_count;
}

void SeplosParser::setup() {
    ESP_LOGI("seplos", "Setup for %d BMS devices completed.", this->bms_count_);
}

void SeplosParser::loop() {
    ESP_LOGI("seplos", "Polling BMS data...");
    for (int i = 0; i < this->bms_count_; i++) {
      ESP_LOGI("seplos", "Simulating data for BMS %d", i);
      // Hier kann die echte Lese- und Verarbeitungslogik implementiert werden.
    }
}

void SeplosParser::dump_config(){
    ESP_LOGCONFIG(TAG, "Seplos Parser");
}


}  // namespace seplos_parser
}  // namespace esphome
