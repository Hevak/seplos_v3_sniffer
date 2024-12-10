#include "seplos_parser.h"
#include "esphome/core/log.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace seplos_parser {

static const char *TAG = "seplos_parser.component";

void SeplosParser::setup() {
   pack_voltage_.resize(bms_count_, nullptr);
   current_.resize(bms_count_, nullptr);

   for (auto *sensor : this->sensors_) {
    for (int i = 0; i < bms_count_; i++) {
      // Erstelle die erwarteten Namen für Spannung und Strom
      std::string pack_voltage_name = "bms" + std::to_string(i) + " pack_voltage";
      std::string current_name = "bms" + std::to_string(i) + " current";

      if (sensor->get_name() == pack_voltage_name) {
        pack_voltage_[i] = sensor;}
      if (sensor->get_name() == current_name) {
        current_[i] = sensor;}
    }
  }
}

void SeplosParser::loop() {
  //float voltage = pack_voltage_[0]->state;
  //float voltage = pack_voltage_[1]->state;
  pack_voltage_[0]->publish_state(5.0);
  current_[0]->publish_state(5.0);
  pack_voltage_[1]->publish_state(5.0);
  current_[1]->publish_state(5.0);
   
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
