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
  //pack_voltage_[0]->publish_state(5.0);
  //current_[0]->publish_state(5.0);
  //pack_voltage_[1]->publish_state(5.0);
  //current_[1]->publish_state(5.0);
  while (available()) {
      uint8_t byte = read();
      buffer.push_back(byte);

      // Nur die letzten ca. 100 Bytes behalten
      if (buffer.size() > 100) {
        buffer.erase(buffer.begin(), buffer.end() - 100);
      }

      // Prüfen, ob ein gültiges Paket im Datenstrom erkannt wird
      while (buffer.size() >= 5) {
        if (is_valid_header()) {
          size_t expected_length = get_expected_length();
          if (buffer.size() < expected_length) {
            // Nicht genügend Daten für das komplette Paket
            break;
          }

          if (validate_crc(expected_length)) {
            process_packet(expected_length);
            buffer.erase(buffer.begin(), buffer.begin() + expected_length);
          } else {
            ESP_LOGW("seplos", "Ungültige CRC, Paket verworfen.");
            buffer.erase(buffer.begin());  // Nur das erste Byte verwerfen
          }
        } else {
          // Kein gültiger Header, das erste Byte entfernen
          buffer.erase(buffer.begin());
        }
      }
    }
}

bool SeplosParser::is_valid_header() {
  return (buffer[0] >= 0x01 && buffer[0] <= 0x10) &&
          buffer[1] == 0x04 &&
         (buffer[2] == 0x24 || buffer[2] == 0x34);
}
size_t SeplosParser::get_expected_length() {
  return (buffer[2] == 0x24) ? 36 + 2 + 3 : 52 + 2 + 3;
}
bool SeplosParser::validate_crc(size_t length) {
  uint16_t received_crc = (buffer[length - 1] << 8) | buffer[length - 2];
  uint16_t calculated_crc = calculate_modbus_crc(buffer, length - 2);
  return received_crc == calculated_crc;
}
void SeplosParser::process_packet(size_t length) {
  int bms_index = buffer[0] - 0x01;
  if (bms_index < 0 || bms_index >= bms_count_) {
    ESP_LOGW("seplos", "Ungültige BMS-ID: %d", buffer[0]);
    return;
  }

  if (buffer[2] == 0x24) {  // 36-Byte-Paket
    uint16_t pack_voltage = (buffer[4] << 8) | buffer[3];
    ESP_LOGI("DEBUG", "buffer[3]: 0x%02X, buffer[4]: 0x%02X", buffer[3], buffer[4]);
    int16_t current = (buffer[6] << 8) | buffer[5];
    //uint16_t remaining_capacity = (buffer[8] << 8) | buffer[7];
    //uint16_t total_capacity = (buffer[10] << 8) | buffer[9];
    //uint16_t total_discharge_capacity = (buffer[12] << 8) | buffer[11];
    //uint16_t soc = (buffer[14] << 8) | buffer[13];
    //uint16_t soh = (buffer[16] << 8) | buffer[15];
    //uint16_t cycle = (buffer[18] << 8) | buffer[17];
    //uint16_t average_cell_voltage = (buffer[20] << 8) | buffer[19];
    //uint16_t average_cell_temp = (buffer[22] << 8) | buffer[21];
    //uint16_t max_cell_voltage = (buffer[24] << 8) | buffer[23];
    //uint16_t min_cell_voltage = (buffer[26] << 8) | buffer[25];
    //uint16_t max_cell_temp = (buffer[28] << 8) | buffer[27];
    //uint16_t min_cell_temp = (buffer[30] << 8) | buffer[29];
    //uint16_t maxdiscurt = (buffer[34] << 8) | buffer[33];
    //uint16_t maxchgcurt = (buffer[36] << 8) | buffer[35];

    pack_voltage_[bms_index]->publish_state(pack_voltage);
    ESP_LOGI("DEBUG", "pack_voltage: %d", pack_voltage);
    current_[bms_index]->publish_state(current / 100);
    //bms[bms_index].remaining_capacity->publish_state(remaining_capacity / 1000);
    //bms[bms_index].total_capacity->publish_state(total_capacity / 100);
    //bms[bms_index].total_discharge_capacity->publish_state(total_discharge_capacity / 0.1);
    //bms[bms_index].soc->publish_state(soc / 10.0);
    //bms[bms_index].soh->publish_state(soh / 10.0);
    //bms[bms_index].cycle->publish_state(cycle);
    //bms[bms_index].average_cell_voltage->publish_state(average_cell_voltage / 1000);
    //bms[bms_index].average_cell_temp->publish_state(average_cell_temp / 10 - 273.15);
    //bms[bms_index].max_cell_voltage->publish_state(max_cell_voltage / 1000);
    //bms[bms_index].min_cell_voltage->publish_state(min_cell_voltage / 1000);
    //bms[bms_index].max_cell_temp->publish_state(max_cell_temp / 10 - 273.15);
    //bms[bms_index].min_cell_temp->publish_state(min_cell_temp / 10 - 273.15);
    //bms[bms_index].maxdiscurt->publish_state(maxdiscurt / 100);
    //bms[bms_index].maxchgcurt->publish_state(maxchgcurt / 100);
  }

  if (buffer[2] == 0x34) {
    //uint16_t cell_1 = (buffer[4] << 8) | buffer[3];
    //  uint16_t cell_2 = (buffer[6] << 8) | buffer[5];
    //  uint16_t cell_3 = (buffer[8] << 8) | buffer[7];
    //  uint16_t cell_4 = (buffer[10] << 8) | buffer[9];
    //  uint16_t cell_5 = (buffer[12] << 8) | buffer[11];
    //  uint16_t cell_6 = (buffer[14] << 8) | buffer[13];
    //  uint16_t cell_7 = (buffer[16] << 8) | buffer[15];
    //  uint16_t cell_8 = (buffer[18] << 8) | buffer[17];
    //  uint16_t cell_9 = (buffer[20] << 8) | buffer[19];
    //  uint16_t cell_10 = (buffer[22] << 8) | buffer[21];
    //  uint16_t cell_11 = (buffer[24] << 8) | buffer[23];
    //  uint16_t cell_12 = (buffer[26] << 8) | buffer[25];
    //  uint16_t cell_13 = (buffer[28] << 8) | buffer[27];
    //  uint16_t cell_14 = (buffer[30] << 8) | buffer[29];
    //  uint16_t cell_15 = (buffer[32] << 8) | buffer[31];
    //  uint16_t cell_16 = (buffer[34] << 8) | buffer[33];
    //  uint16_t cell_temp_1 = (buffer[36] << 8) | buffer[35];
    //  uint16_t cell_temp_2 = (buffer[38] << 8) | buffer[37];
    //  uint16_t cell_temp_3 = (buffer[40] << 8) | buffer[39];
    //  uint16_t cell_temp_4 = (buffer[42] << 8) | buffer[41];
    //  uint16_t case_temp = (buffer[52] << 8) | buffer[51];
    //  uint16_t power_temp = (buffer[54] << 8) | buffer[53];

    //  bms[bms_index].cell_1->publish_state(cell_1 / 1000);
    //  bms[bms_index].cell_2->publish_state(cell_2 / 1000);
    //  bms[bms_index].cell_3->publish_state(cell_3 / 1000);
    //  bms[bms_index].cell_4->publish_state(cell_4 / 1000);
    //  bms[bms_index].cell_5->publish_state(cell_5 / 1000);
    //  bms[bms_index].cell_6->publish_state(cell_6 / 1000);
    //  bms[bms_index].cell_7->publish_state(cell_7 / 1000);
    //  bms[bms_index].cell_8->publish_state(cell_8 / 1000);
    //  bms[bms_index].cell_9->publish_state(cell_9 / 1000);
    //  bms[bms_index].cell_10->publish_state(cell_10 / 1000);
    //  bms[bms_index].cell_11->publish_state(cell_11 / 1000);
    //  bms[bms_index].cell_12->publish_state(cell_12 / 1000);
    //  bms[bms_index].cell_13->publish_state(cell_13 / 1000);
    //  bms[bms_index].cell_14->publish_state(cell_14 / 1000);
    //  bms[bms_index].cell_15->publish_state(cell_15 / 1000);
    //  bms[bms_index].cell_16->publish_state(cell_16 / 1000);
    //  bms[bms_index].cell_temp_1->publish_state(cell_temp_1 / 10 - 273.15);
    //  bms[bms_index].cell_temp_2->publish_state(cell_temp_2 / 10 - 273.15);
    //  bms[bms_index].cell_temp_3->publish_state(cell_temp_3 / 10 - 273.15);
    //  bms[bms_index].cell_temp_4->publish_state(cell_temp_4 / 10 - 273.15);
    //  bms[bms_index].case_temp->publish_state(case_temp / 10 - 273.15);
    //  bms[bms_index].power_temp->publish_state(power_temp / 10 - 273.15);
  }
}
uint16_t SeplosParser::calculate_modbus_crc(const std::vector<uint8_t>& data, size_t length) {
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
