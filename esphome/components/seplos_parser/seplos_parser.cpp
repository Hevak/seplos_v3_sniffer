#include "esphome/core/log.h"
#include "seplos_parser.h"

namespace esphome {
namespace seplos_parser {

static const char *TAG = "seplos_parser.component";

void SeplosParser::set_bms_sensors(int index, sensor::Sensor *pack_voltage, sensor::Sensor *current,
                                   sensor::Sensor *soc, sensor::Sensor *soh, sensor::Sensor *cycle_count) {
  if (index < this->bms_count_) {
    this->pack_voltages[index] = pack_voltage;
    this->currents[index] = current;
    this->socs[index] = soc;
    this->sohs[index] = soh;
    this->cycle_counts[index] = cycle_count;
    ESP_LOGI("seplos", "Sensors for BMS%d set.", index);
  } 
  else {
    ESP_LOGW("seplos", "Index %d out of range (max: %d).", index, this->bms_count_ - 1);
  }
}

SeplosParser::SeplosParser(esphome::uart::UARTComponent *uart_parent, int bms_count) {
  this->uart_parent_ = uart_parent;
  this->bms_count_ = bms_count;

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
void SeplosParser::set_uart_parent(esphome::uart::UARTComponent *uart_parent) {
  this->uart_parent_ = uart_parent;
}

}  // namespace seplos_parser
}  // namespace esphome
