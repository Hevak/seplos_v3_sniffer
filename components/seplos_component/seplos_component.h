#pragma once
#include "esphome.h"

class SeplosComponent : public PollingComponent, public UARTDevice {
 public:
  SeplosComponent(UARTComponent *parent, int bms_count, uint32_t update_interval = 1000)
      : PollingComponent(update_interval), UARTDevice(parent) {
    this->bms_count_ = bms_count;
    this->sensors_.resize(bms_count);
  }

  void setup() override {
    ESP_LOGI("seplos", "Setup for %d BMS devices completed.", this->bms_count_);
  }

  void update() override {
    ESP_LOGI("seplos", "Polling BMS data...");
    this->read_data_();
  }

 private:
  int bms_count_;
  std::vector<Sensor *> sensors_;

  void read_data_() {
    for (int i = 0; i < this->bms_count_; i++) {
      ESP_LOGI("seplos", "Simulating data for BMS %d", i);
      // Hier kann die echte Lese- und Verarbeitungslogik implementiert werden.
    }
  }
};
