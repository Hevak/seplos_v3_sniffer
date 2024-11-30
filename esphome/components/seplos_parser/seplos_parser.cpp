#include "esphome/core/application.h"
#include "seplos_parser.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace seplos_parser {

// Konstruktor
SeplosParser::SeplosParser(esphome::uart::UARTComponent *uart, int bms_count, int throttle_interval)
    : UARTDevice(uart), bms_count_(bms_count), throttle_interval_(throttle_interval) {}

// Setup-Methode
void SeplosParser::setup() {
  ESP_LOGI("seplos_parser", "Setup executed");

  // Initialisierung der Sensoren für jede BMS-Instanz
  for (int i = 0; i < bms_count_; i++) {
    std::string prefix = "BMS " + std::to_string(i + 1) + " ";

    auto pack_voltage = new esphome::sensor::Sensor();
    pack_voltage->set_name((prefix + "pack_voltage").c_str());
    pack_voltage->set_unit_of_measurement("V");
    pack_voltage->set_accuracy_decimals(2);
    pack_voltage->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(pack_voltage);
    ESP_LOGI("seplos_parser", "Sensor for %s registered", (prefix + "Pack Voltage").c_str());

    auto current_sensor = new esphome::sensor::Sensor();
    current_sensor->set_name((prefix + "current").c_str());
    current_sensor->set_unit_of_measurement("A");
    current_sensor->set_accuracy_decimals(2);
    current_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(current_sensor);

    auto remaining_capacity_sensor = new esphome::sensor::Sensor();
    remaining_capacity_sensor->set_name((prefix + "remaining_capacity").c_str());
    remaining_capacity_sensor->set_unit_of_measurement("Ah");
    remaining_capacity_sensor->set_accuracy_decimals(2);
    remaining_capacity_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(remaining_capacity_sensor);

    auto total_capacity_sensor = new esphome::sensor::Sensor();
    total_capacity_sensor->set_name((prefix + "total_capacity").c_str());
    total_capacity_sensor->set_unit_of_measurement("Ah");
    total_capacity_sensor->set_accuracy_decimals(2);
    total_capacity_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(total_capacity_sensor);

    auto total_discharge_capacity_sensor = new esphome::sensor::Sensor();
    total_discharge_capacity_sensor->set_name((prefix + "total_discharge_capacity").c_str());
    total_discharge_capacity_sensor->set_unit_of_measurement("Ah");
    total_discharge_capacity_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(total_discharge_capacity_sensor);

    auto soc_sensor = new esphome::sensor::Sensor();
    soc_sensor->set_name((prefix + "soc").c_str());
    soc_sensor->set_unit_of_measurement("%");
    soc_sensor->set_accuracy_decimals(1);
    soc_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(soc_sensor);

    auto soh_sensor = new esphome::sensor::Sensor();
    soh_sensor->set_name((prefix + "soh").c_str());
    soh_sensor->set_unit_of_measurement("%");
    soh_sensor->set_accuracy_decimals(1);
    soh_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(soh_sensor);

    auto cycle_sensor = new esphome::sensor::Sensor();
    cycle_sensor->set_name((prefix + "cycle").c_str());
    cycle_sensor->set_accuracy_decimals(0);
    cycle_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cycle_sensor);

    auto average_cell_voltage_sensor = new esphome::sensor::Sensor();
    average_cell_voltage_sensor->set_name((prefix + "average_cell_voltage").c_str());
    average_cell_voltage_sensor->set_unit_of_measurement("V");
    average_cell_voltage_sensor->set_accuracy_decimals(3);
    average_cell_voltage_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(average_cell_voltage_sensor);

    auto average_cell_temp_sensor = new esphome::sensor::Sensor();
    average_cell_temp_sensor->set_name((prefix + "average_cell_temp").c_str());
    average_cell_temp_sensor->set_unit_of_measurement("°C");
    average_cell_temp_sensor->set_accuracy_decimals(1);
    average_cell_temp_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(average_cell_temp_sensor);

    auto max_cell_voltage_sensor = new esphome::sensor::Sensor();
    max_cell_voltage_sensor->set_name((prefix + "max_cell_voltage").c_str());
    max_cell_voltage_sensor->set_unit_of_measurement("V");
    max_cell_voltage_sensor->set_accuracy_decimals(3);
    max_cell_voltage_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(max_cell_voltage_sensor);

    auto min_cell_voltage_sensor = new esphome::sensor::Sensor();
    min_cell_voltage_sensor->set_name((prefix + "min_cell_voltage").c_str());
    min_cell_voltage_sensor->set_unit_of_measurement("V");
    min_cell_voltage_sensor->set_accuracy_decimals(3);
    min_cell_voltage_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(min_cell_voltage_sensor);

    auto max_cell_temp_sensor = new esphome::sensor::Sensor();
    max_cell_temp_sensor->set_name((prefix + "max_cell_temp").c_str());
    max_cell_temp_sensor->set_unit_of_measurement("°C");
    max_cell_temp_sensor->set_accuracy_decimals(1);
    max_cell_temp_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(max_cell_temp_sensor);

    auto min_cell_temp_sensor = new esphome::sensor::Sensor();
    min_cell_temp_sensor->set_name((prefix + "min_cell_temp").c_str());
    min_cell_temp_sensor->set_unit_of_measurement("°C");
    min_cell_temp_sensor->set_accuracy_decimals(1);
    min_cell_temp_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(min_cell_temp_sensor);

    auto maxdiscurt_sensor = new esphome::sensor::Sensor();
    maxdiscurt_sensor->set_name((prefix + "maxdiscurt").c_str());
    maxdiscurt_sensor->set_unit_of_measurement("A");
    maxdiscurt_sensor->set_accuracy_decimals(2);
    maxdiscurt_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(maxdiscurt_sensor);

    auto maxchgcurt_sensor = new esphome::sensor::Sensor();
    maxchgcurt_sensor->set_name((prefix + "maxchgcurt").c_str());
    maxchgcurt_sensor->set_unit_of_measurement("A");
    maxchgcurt_sensor->set_accuracy_decimals(2);
    maxchgcurt_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(maxchgcurt_sensor);

    auto cell_1_sensor = new esphome::sensor::Sensor();
    cell_1_sensor->set_name((prefix + "cell_1").c_str());
    cell_1_sensor->set_unit_of_measurement("V");
    cell_1_sensor->set_accuracy_decimals(3);
    cell_1_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_1_sensor);

    auto cell_2_sensor = new esphome::sensor::Sensor();
    cell_2_sensor->set_name((prefix + "cell_2").c_str());
    cell_2_sensor->set_unit_of_measurement("V");
    cell_2_sensor->set_accuracy_decimals(3);
    cell_2_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_2_sensor);

    auto cell_3_sensor = new esphome::sensor::Sensor();
    cell_3_sensor->set_name((prefix + "cell_3").c_str());
    cell_3_sensor->set_unit_of_measurement("V");
    cell_3_sensor->set_accuracy_decimals(3);
    cell_3_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_3_sensor);

    auto cell_4_sensor = new esphome::sensor::Sensor();
    cell_4_sensor->set_name((prefix + "cell_4").c_str());
    cell_4_sensor->set_unit_of_measurement("V");
    cell_4_sensor->set_accuracy_decimals(3);
    cell_4_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_4_sensor);

    auto cell_5_sensor = new esphome::sensor::Sensor();
    cell_5_sensor->set_name((prefix + "cell_5").c_str());
    cell_5_sensor->set_unit_of_measurement("V");
    cell_5_sensor->set_accuracy_decimals(3);
    cell_5_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_5_sensor);

    auto cell_6_sensor = new esphome::sensor::Sensor();
    cell_6_sensor->set_name((prefix + "cell_6").c_str());
    cell_6_sensor->set_unit_of_measurement("V");
    cell_6_sensor->set_accuracy_decimals(3);
    cell_6_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_6_sensor);

    auto cell_7_sensor = new esphome::sensor::Sensor();
    cell_7_sensor->set_name((prefix + "cell_7").c_str());
    cell_7_sensor->set_unit_of_measurement("V");
    cell_7_sensor->set_accuracy_decimals(3);
    cell_7_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_7_sensor);

    auto cell_8_sensor = new esphome::sensor::Sensor();
    cell_8_sensor->set_name((prefix + "cell_8").c_str());
    cell_8_sensor->set_unit_of_measurement("V");
    cell_8_sensor->set_accuracy_decimals(3);
    cell_8_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_8_sensor);

    auto cell_9_sensor = new esphome::sensor::Sensor();
    cell_9_sensor->set_name((prefix + "cell_9").c_str());
    cell_9_sensor->set_unit_of_measurement("V");
    cell_9_sensor->set_accuracy_decimals(3);
    cell_9_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_9_sensor);

    auto cell_10_sensor = new esphome::sensor::Sensor();
    cell_10_sensor->set_name((prefix + "cell_10").c_str());
    cell_10_sensor->set_unit_of_measurement("V");
    cell_10_sensor->set_accuracy_decimals(3);
    cell_10_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_10_sensor);

    auto cell_11_sensor = new esphome::sensor::Sensor();
    cell_11_sensor->set_name((prefix + "cell_11").c_str());
    cell_11_sensor->set_unit_of_measurement("V");
    cell_11_sensor->set_accuracy_decimals(3);
    cell_11_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_11_sensor);

    auto cell_12_sensor = new esphome::sensor::Sensor();
    cell_12_sensor->set_name((prefix + "cell_12").c_str());
    cell_12_sensor->set_unit_of_measurement("V");
    cell_12_sensor->set_accuracy_decimals(3);
    cell_12_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_12_sensor);

    auto cell_13_sensor = new esphome::sensor::Sensor();
    cell_13_sensor->set_name((prefix + "cell_13").c_str());
    cell_13_sensor->set_unit_of_measurement("V");
    cell_13_sensor->set_accuracy_decimals(3);
    cell_13_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_13_sensor);

    auto cell_14_sensor = new esphome::sensor::Sensor();
    cell_14_sensor->set_name((prefix + "cell_14").c_str());
    cell_14_sensor->set_unit_of_measurement("V");
    cell_14_sensor->set_accuracy_decimals(3);
    cell_14_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_14_sensor);

    auto cell_15_sensor = new esphome::sensor::Sensor();
    cell_15_sensor->set_name((prefix + "cell_15").c_str());
    cell_15_sensor->set_unit_of_measurement("V");
    cell_15_sensor->set_accuracy_decimals(3);
    cell_15_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_15_sensor);

    auto cell_16_sensor = new esphome::sensor::Sensor();
    cell_16_sensor->set_name((prefix + "cell_16").c_str());
    cell_16_sensor->set_unit_of_measurement("V");
    cell_16_sensor->set_accuracy_decimals(3);
    cell_16_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_16_sensor);

    auto cell_temp_1_sensor = new esphome::sensor::Sensor();
    cell_temp_1_sensor->set_name((prefix + "cell_temp_1").c_str());
    cell_temp_1_sensor->set_unit_of_measurement("°C");
    cell_temp_1_sensor->set_accuracy_decimals(1);
    cell_temp_1_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_temp_1_sensor);

    auto cell_temp_2_sensor = new esphome::sensor::Sensor();
    cell_temp_2_sensor->set_name((prefix + "cell_temp_2").c_str());
    cell_temp_2_sensor->set_unit_of_measurement("°C");
    cell_temp_2_sensor->set_accuracy_decimals(1);
    cell_temp_2_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_temp_2_sensor);

    auto cell_temp_3_sensor = new esphome::sensor::Sensor();
    cell_temp_3_sensor->set_name((prefix + "cell_temp_3").c_str());
    cell_temp_3_sensor->set_unit_of_measurement("°C");
    cell_temp_3_sensor->set_accuracy_decimals(1);
    cell_temp_3_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_temp_3_sensor);

    auto cell_temp_4_sensor = new esphome::sensor::Sensor();
    cell_temp_4_sensor->set_name((prefix + "cell_temp_4").c_str());
    cell_temp_4_sensor->set_unit_of_measurement("°C");
    cell_temp_4_sensor->set_accuracy_decimals(1);
    cell_temp_4_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(cell_temp_4_sensor);

    auto case_temp_sensor = new esphome::sensor::Sensor();
    case_temp_sensor->set_name((prefix + "case_temp").c_str());
    case_temp_sensor->set_unit_of_measurement("°C");
    case_temp_sensor->set_accuracy_decimals(1);
    case_temp_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(case_temp_sensor);

    auto power_temp_sensor = new esphome::sensor::Sensor();
    power_temp_sensor->set_name((prefix + "power_temp").c_str());
    power_temp_sensor->set_unit_of_measurement("°C");
    power_temp_sensor->set_accuracy_decimals(1);
    power_temp_sensor->add_filter(new esphome::sensor::ThrottleFilter(throttle_interval_));
    this->sensors_.push_back(power_temp_sensor);
  }
}

void SeplosParser::loop() {
  static uint32_t last_time = millis();
  while (this->available()) {
    uint8_t byte = this->read();
    ESP_LOGI("seplos_parser", "Received UART byte: 0x%02X", byte);
    this->buffer.push_back(byte);
    last_time = millis();  // Reset timeout

    if (this->buffer.size() > 100) {
      buffer.erase(buffer.begin(), buffer.end() - 100);
    }

    while (this->buffer.size() >= 5) {
      if (this->is_valid_header()) {
        size_t expected_length = this->get_expected_length();
        if (buffer.size() < expected_length) break;

        if (this->validate_crc(expected_length)) {
          this->process_packet(expected_length);
          buffer.erase(buffer.begin(), buffer.begin() + expected_length);
        } 
        else {
          ESP_LOGW("seplos_parser", "Invalid CRC, dropping packet.");
          buffer.erase(buffer.begin());
        }
      } 
      else {
        buffer.erase(buffer.begin());
      }
    }
  }
  ESP_LOGD("seplos_parser", "Loop running without UART data");
  if (millis() - last_time > 5000) {  // 5 Sekunden Timeout
    ESP_LOGW("seplos_parser", "No UART data for 5 seconds, skipping...");
  }
}

bool SeplosParser::is_valid_header() {
  return (this->buffer[0] >= 0x01 && this->buffer[0] <= 0x10) && this->buffer[1] == 0x04 &&
         (this->buffer[2] == 0x24 || this->buffer[2] == 0x34);
}

size_t SeplosParser::get_expected_length() {
  return (this->buffer[2] == 0x24) ? 36 + 2 + 3 : 52 + 2 + 3;
}

bool SeplosParser::validate_crc(size_t length) {
  uint16_t received_crc = (this->buffer[length - 1] << 8) | this->buffer[length - 2];
  uint16_t calculated_crc = this->calculate_modbus_crc(this->buffer, length - 2);
  return received_crc == calculated_crc;
}

void SeplosParser::process_packet(size_t length) {
  int bms_index = this->buffer[0] - 0x01;
  if (bms_index < 0 || bms_index >= this->bms_count_) {
    ESP_LOGW("seplos_parser", "Invalid BMS ID: %d", buffer[0]);
    return;
  }

  if (buffer[2] == 0x24) {
    // Verarbeite das 36-Byte-Paket und publiziere die Daten
    uint16_t pack_voltage = (this->buffer[4] << 8) | this->buffer[3];
    int16_t current = (this->buffer[6] << 8) | this->buffer[5];
    uint16_t remaining_capacity = (this->buffer[8] << 8) | this->buffer[7];
    uint16_t total_capacity = (this->buffer[10] << 8) | this->buffer[9];
    uint16_t total_discharge_capacity = (this->buffer[12] << 8) | this->buffer[11];
    uint16_t soc = (this->buffer[14] << 8) | this->buffer[13];
    uint16_t soh = (this->buffer[16] << 8) | this->buffer[15];
    uint16_t cycle = (this->buffer[18] << 8) | this->buffer[17];
    uint16_t average_cell_voltage = (this->buffer[20] << 8) | this->buffer[19];
    uint16_t average_cell_temp = (this->buffer[22] << 8) | this->buffer[21];
    uint16_t max_cell_voltage = (this->buffer[24] << 8) | this->buffer[23];
    uint16_t min_cell_voltage = (this->buffer[26] << 8) | this->buffer[25];
    uint16_t max_cell_temp = (this->buffer[28] << 8) | this->buffer[27];
    uint16_t min_cell_temp = (this->buffer[30] << 8) | this->buffer[29];
    uint16_t maxdiscurt = (this->buffer[34] << 8) | this->buffer[33];
    uint16_t maxchgcurt = (this->buffer[36] << 8) | this->buffer[35];

    this->bms[bms_index].pack_voltage->publish_state(pack_voltage / 100);
    this->bms[bms_index].current->publish_state(current / 100);
    this->bms[bms_index].remaining_capacity->publish_state(remaining_capacity / 1000);
    this->bms[bms_index].total_capacity->publish_state(total_capacity / 100);
    this->bms[bms_index].total_discharge_capacity->publish_state(total_discharge_capacity / 0.1);
    this->bms[bms_index].soc->publish_state(soc / 10.0);
    this->bms[bms_index].soh->publish_state(soh / 10.0);
    this->bms[bms_index].cycle->publish_state(cycle);
    this->bms[bms_index].average_cell_voltage->publish_state(average_cell_voltage / 1000);
    this->bms[bms_index].average_cell_temp->publish_state(average_cell_temp / 10 - 273.15);
    this->bms[bms_index].max_cell_voltage->publish_state(max_cell_voltage / 1000);
    this->bms[bms_index].min_cell_voltage->publish_state(min_cell_voltage / 1000);
    this->bms[bms_index].max_cell_temp->publish_state(max_cell_temp / 10 - 273.15);
    this->bms[bms_index].min_cell_temp->publish_state(min_cell_temp / 10 - 273.15);
    this->bms[bms_index].maxdiscurt->publish_state(maxdiscurt / 100);
    this->bms[bms_index].maxchgcurt->publish_state(maxchgcurt / 100);

  } 
  else if (buffer[2] == 0x34) {
    // Verarbeite das 52-Byte-Paket und publiziere die Daten
    uint16_t cell_1 = (this->buffer[4] << 8) | this->buffer[3];
    uint16_t cell_2 = (this->buffer[6] << 8) | this->buffer[5];
    uint16_t cell_3 = (this->buffer[8] << 8) | this->buffer[7];
    uint16_t cell_4 = (this->buffer[10] << 8) | this->buffer[9];
    uint16_t cell_5 = (this->buffer[12] << 8) | this->buffer[11];
    uint16_t cell_6 = (this->buffer[14] << 8) | this->buffer[13];
    uint16_t cell_7 = (this->buffer[16] << 8) | this->buffer[15];
    uint16_t cell_8 = (this->buffer[18] << 8) | this->buffer[17];
    uint16_t cell_9 = (this->buffer[20] << 8) | this->buffer[19];
    uint16_t cell_10 = (this->buffer[22] << 8) | this->buffer[21];
    uint16_t cell_11 = (this->buffer[24] << 8) | this->buffer[23];
    uint16_t cell_12 = (this->buffer[26] << 8) | this->buffer[25];
    uint16_t cell_13 = (this->buffer[28] << 8) | this->buffer[27];
    uint16_t cell_14 = (this->buffer[30] << 8) | this->buffer[29];
    uint16_t cell_15 = (this->buffer[32] << 8) | this->buffer[31];
    uint16_t cell_16 = (this->buffer[34] << 8) | this->buffer[33];
    uint16_t cell_temp_1 = (this->buffer[36] << 8) | this->buffer[35];
    uint16_t cell_temp_2 = (this->buffer[38] << 8) | this->buffer[37];
    uint16_t cell_temp_3 = (this->buffer[40] << 8) | this->buffer[39];
    uint16_t cell_temp_4 = (this->buffer[42] << 8) | this->buffer[41];
    uint16_t case_temp = (this->buffer[52] << 8) | this->buffer[51];
    uint16_t power_temp = (this->buffer[54] << 8) | this->buffer[53];

    this->bms[bms_index].cell_1->publish_state(cell_1 / 1000);
    this->bms[bms_index].cell_2->publish_state(cell_2 / 1000);
    this->bms[bms_index].cell_3->publish_state(cell_3 / 1000);
    this->bms[bms_index].cell_4->publish_state(cell_4 / 1000);
    this->bms[bms_index].cell_5->publish_state(cell_5 / 1000);
    this->bms[bms_index].cell_6->publish_state(cell_6 / 1000);
    this->bms[bms_index].cell_7->publish_state(cell_7 / 1000);
    this->bms[bms_index].cell_8->publish_state(cell_8 / 1000);
    this->bms[bms_index].cell_9->publish_state(cell_9 / 1000);
    this->bms[bms_index].cell_10->publish_state(cell_10 / 1000);
    this->bms[bms_index].cell_11->publish_state(cell_11 / 1000);
    this->bms[bms_index].cell_12->publish_state(cell_12 / 1000);
    this->bms[bms_index].cell_13->publish_state(cell_13 / 1000);
    this->bms[bms_index].cell_14->publish_state(cell_14 / 1000);
    this->bms[bms_index].cell_15->publish_state(cell_15 / 1000);
    this->bms[bms_index].cell_16->publish_state(cell_16 / 1000);
    this->bms[bms_index].cell_temp_1->publish_state(cell_temp_1 / 10 - 273.15);
    this->bms[bms_index].cell_temp_2->publish_state(cell_temp_2 / 10 - 273.15);
    this->bms[bms_index].cell_temp_3->publish_state(cell_temp_3 / 10 - 273.15);
    this->bms[bms_index].cell_temp_4->publish_state(cell_temp_4 / 10 - 273.15);
    this->bms[bms_index].case_temp->publish_state(case_temp / 10 - 273.15);
    this->bms[bms_index].power_temp->publish_state(power_temp / 10 - 273.15);
  }
}

uint16_t SeplosParser::calculate_modbus_crc(const std::vector<uint8_t> &data, size_t length) {
  uint16_t crc = 0xFFFF;
  for (size_t pos = 0; pos < length; pos++) {
    crc ^= static_cast<uint16_t>(data[pos]);
    for (int i = 0; i < 8; i++) {
      if (crc & 0x0001) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

}  // namespace seplos_parser
}  // namespace esphome
