#include "esphome/core/log.h"
#include "seplos_parser.h"

namespace esphome {
namespace seplos_parser {

static const char *TAG = "seplos_parser.component";

void SeplosParser::setup() {
    ESP_LOGI("seplos", "Setup for %d BMS devices completed.", this->bms_count_);
}

void SeplosParser::loop() {
    ESP_LOGI("seplos", "Polling BMS data...");
    this->read_data_();
}

void SeplosParser::dump_config(){
    ESP_LOGCONFIG(TAG, "Seplos Parser");
}
void read_data_() {
    for (int i = 0; i < this->bms_count_; i++) {
      ESP_LOGI("seplos", "Simulating data for BMS %d", i);
      // Hier kann die echte Lese- und Verarbeitungslogik implementiert werden.
    }

}  // namespace seplos_parser
}  // namespace esphome
