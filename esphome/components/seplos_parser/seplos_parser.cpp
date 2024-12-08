#include "seplos_parser.h"
#include "esphome/core/log.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace seplos_parser {

static const char *TAG = "seplos_parser.component";

void SeplosParser::setup() {
  ESP_LOGI("seplos", "Polling BMS data...");
  for (int i = 0; i < this->bms_count_; i++) {
      ESP_LOGI("seplos", "Simulating data for BMS %d", i);
      // Hier kann die echte Lese- und Verarbeitungslogik implementiert werden.
  }
}

void SeplosParser::loop() {

}

void SeplosParser::dump_config(){
    for (auto *sensor : this->sensors_) {
        LOG_SENSOR("  ", "Sensor", sensor);
    }

//    for(auto *text_sensor : this->text_sensors_){
//        LOG_TEXT_SENSOR("  ", "Text sensor", text_sensor);
//    }
//
//    for(auto *binary_sensor : this->binary_sensors_){
//        LOG_BINARY_SENSOR("  ", "Binary sensor", binary_sensor);
//    }
}
void SeplosParser::set_bms_count(int bms_count) {
  this->bms_count_ = bms_count;  // Wert speichern
  ESP_LOGI("SeplosParser", "BMS Count gesetzt auf: %d", bms_count);
}

}  // namespace seplos_parser
}  // namespace esphome
