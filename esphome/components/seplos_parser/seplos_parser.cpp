#include "esphome/core/log.h"
#include "seplos_parser.h"

namespace esphome {
namespace seplos_parser {

static const char *TAG = "seplos_parser.component";

SeplosParser::SeplosParser(esphome::uart::UARTComponent *uart_parent, int bms_count) : uart_parent_(uart_parent), bms_count_(bms_count) {
//  this->uart_parent_ = uart_parent;
//  this->bms_count_ = bms_count;

  // Initialisierung der Sensor-Listen
  for (int i = 0; i < bms_count; i++) {
    this->pack_voltages.push_back(new sensor::Sensor());
    this->currents.push_back(new sensor::Sensor());
    this->socs.push_back(new sensor::Sensor());
    this->sohs.push_back(new sensor::Sensor());
    this->cycle_counts.push_back(new sensor::Sensor());
  }
}

void SeplosParser::setup() {
    ESP_LOGI("seplos", "Setup for %d BMS devices completed.", this->bms_count_);
}

void SeplosParser::loop() {
//    ESP_LOGI("seplos", "Polling BMS data...");
  for (int i = 0; i < this->bms_count_; i++) {
    float pack_voltage = 50.0 + i;  // Beispielwert
    float current = 5.0 * (i + 1);  // Beispielwert
    float soc = 80.0 - i;           // Beispielwert
    float soh = 90.0 - (i * 2);     // Beispielwert
    int cycle_count = 100 + i;      // Beispielwert

    // Werte an die Sensoren übergeben
    this->pack_voltages[i]->publish_state(pack_voltage);
    this->currents[i]->publish_state(current);
    this->socs[i]->publish_state(soc);
    this->sohs[i]->publish_state(soh);
    this->cycle_counts[i]->publish_state(cycle_count);
  }
}

void SeplosParser::dump_config(){
    ESP_LOGCONFIG(TAG, "Seplos Parser");
}

void SeplosParser::add_sensor(sensor::Sensor *sensor) {
  this->sensors_.push_back(sensor);
  ESP_LOGI(TAG, "Added sensor: %s", sensor->get_name().c_str());
}

void SeplosParser::set_uart_parent(esphome::uart::UARTComponent *uart_parent) {
  this->uart_parent_ = uart_parent;
}

}  // namespace seplos_parser
}  // namespace esphome
