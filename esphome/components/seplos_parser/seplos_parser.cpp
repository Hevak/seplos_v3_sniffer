#include "seplos_parser.h"
#include "esphome/core/log.h"
#include "esphome/components/uart/uart.h"
#include <unordered_map>

namespace esphome {
namespace seplos_parser {

static const char *TAG = "seplos_parser.component";

void SeplosParser::setup() {
   pack_voltage_.resize(bms_count_, nullptr);
   current_.resize(bms_count_, nullptr);
   remaining_capacity_.resize(bms_count_, nullptr);
   total_capacity_.resize(bms_count_, nullptr);
   total_discharge_capacity_.resize(bms_count_, nullptr);
   soc_.resize(bms_count_, nullptr);
   soh_.resize(bms_count_, nullptr);
   cycle_count_.resize(bms_count_, nullptr);
   average_cell_voltage_.resize(bms_count_, nullptr);
   average_cell_temp_.resize(bms_count_, nullptr);
   max_cell_voltage_.resize(bms_count_, nullptr);
   min_cell_voltage_.resize(bms_count_, nullptr);
   max_cell_temp_.resize(bms_count_, nullptr);
   min_cell_temp_.resize(bms_count_, nullptr);
   maxdiscurt_.resize(bms_count_, nullptr);
   maxchgcurt_.resize(bms_count_, nullptr);
   cell_1_.resize(bms_count_, nullptr);
   cell_2_.resize(bms_count_, nullptr);
   cell_3_.resize(bms_count_, nullptr);
   cell_4_.resize(bms_count_, nullptr);
   cell_5_.resize(bms_count_, nullptr);
   cell_6_.resize(bms_count_, nullptr);
   cell_7_.resize(bms_count_, nullptr);
   cell_8_.resize(bms_count_, nullptr);
   cell_9_.resize(bms_count_, nullptr);
   cell_10_.resize(bms_count_, nullptr);
   cell_11_.resize(bms_count_, nullptr);
   cell_12_.resize(bms_count_, nullptr);
   cell_13_.resize(bms_count_, nullptr);
   cell_14_.resize(bms_count_, nullptr);
   cell_15_.resize(bms_count_, nullptr);
   cell_16_.resize(bms_count_, nullptr);
   cell_temp_1_.resize(bms_count_, nullptr);
   cell_temp_2_.resize(bms_count_, nullptr);
   cell_temp_3_.resize(bms_count_, nullptr);
   cell_temp_4_.resize(bms_count_, nullptr);
   case_temp_.resize(bms_count_, nullptr);
   power_temp_.resize(bms_count_, nullptr);
   
   
   for (auto *sensor : this->sensors_) {
    for (int i = 0; i < bms_count_; i++) {
      std::string pack_voltage_name = "bms" + std::to_string(i) + " pack_voltage";
      std::string current_name = "bms" + std::to_string(i) + " current";
      std::string remaining_capacity_name = "bms" + std::to_string(i) + " remaining_capacity";
      std::string total_capacity_name = "bms" + std::to_string(i) + " total_capacity";
      std::string total_discharge_capacity_name = "bms" + std::to_string(i) + " total_discharge_capacity";
      std::string soc_name = "bms" + std::to_string(i) + " soc";
      std::string soh_name = "bms" + std::to_string(i) + " soh";
      std::string cycle_count_name = "bms" + std::to_string(i) + " cycle_count";
      std::string average_cell_voltage_name = "bms" + std::to_string(i) + " average_cell_voltage";
      std::string average_cell_temp_name = "bms" + std::to_string(i) + " average_cell_temp";
      std::string max_cell_voltage_name = "bms" + std::to_string(i) + " max_cell_voltage";
      std::string min_cell_voltage_name = "bms" + std::to_string(i) + " min_cell_voltage";
      std::string max_cell_temp_name = "bms" + std::to_string(i) + " max_cell_temp";
      std::string min_cell_temp_name = "bms" + std::to_string(i) + " min_cell_temp";
      std::string maxdiscurt_name = "bms" + std::to_string(i) + " maxdiscurt";
      std::string maxchgcurt_name = "bms" + std::to_string(i) + " maxchgcurt";
      std::string cell_1_name = "bms" + std::to_string(i) + " cell_1";
      std::string cell_2_name = "bms" + std::to_string(i) + " cell_2";
      std::string cell_3_name = "bms" + std::to_string(i) + " cell_3";
      std::string cell_4_name = "bms" + std::to_string(i) + " cell_4";
      std::string cell_5_name = "bms" + std::to_string(i) + " cell_5";
      std::string cell_6_name = "bms" + std::to_string(i) + " cell_6";
      std::string cell_7_name = "bms" + std::to_string(i) + " cell_7";
      std::string cell_8_name = "bms" + std::to_string(i) + " cell_8";
      std::string cell_9_name = "bms" + std::to_string(i) + " cell_9";
      std::string cell_10_name = "bms" + std::to_string(i) + " cell_10";
      std::string cell_11_name = "bms" + std::to_string(i) + " cell_11";
      std::string cell_12_name = "bms" + std::to_string(i) + " cell_12";
      std::string cell_13_name = "bms" + std::to_string(i) + " cell_13";
      std::string cell_14_name = "bms" + std::to_string(i) + " cell_14";
      std::string cell_15_name = "bms" + std::to_string(i) + " cell_15";
      std::string cell_16_name = "bms" + std::to_string(i) + " cell_16";
      std::string cell_temp_1_name = "bms" + std::to_string(i) + " cell_temp_1";
      std::string cell_temp_2_name = "bms" + std::to_string(i) + " cell_temp_2";
      std::string cell_temp_3_name = "bms" + std::to_string(i) + " cell_temp_3";
      std::string cell_temp_4_name = "bms" + std::to_string(i) + " cell_temp_4";
      std::string case_temp_name = "bms" + std::to_string(i) + " case_temp";
      std::string power_temp_name = "bms" + std::to_string(i) + " power_temp";
      
       
      if (sensor->get_name() == pack_voltage_name) {
        pack_voltage_[i] = sensor;}
      if (sensor->get_name() == current_name) {
        current_[i] = sensor;}
      if (sensor->get_name() == remaining_capacity_name) {
        remaining_capacity_[i] = sensor;}
      if (sensor->get_name() == total_capacity_name) {
        total_capacity_[i] = sensor;}
      if (sensor->get_name() == total_discharge_capacity_name) {
        total_discharge_capacity_[i] = sensor;}
      if (sensor->get_name() == soc_name) {
        soc_[i] = sensor;}
      if (sensor->get_name() == soh_name) {
        soh_[i] = sensor;}
      if (sensor->get_name() == cycle_count_name) {
        cycle_count_[i] = sensor;}
      if (sensor->get_name() == average_cell_voltage_name) {
        average_cell_voltage_[i] = sensor;}
      if (sensor->get_name() == average_cell_temp_name) {
        average_cell_temp_[i] = sensor;}
      if (sensor->get_name() == max_cell_voltage_name) {
        max_cell_voltage_[i] = sensor;}
      if (sensor->get_name() == min_cell_voltage_name) {
        min_cell_voltage_[i] = sensor;}
      if (sensor->get_name() == max_cell_temp_name) {
        max_cell_temp_[i] = sensor;}
      if (sensor->get_name() == min_cell_temp_name) {
        min_cell_temp_[i] = sensor;}
      if (sensor->get_name() == maxdiscurt_name) {
        maxdiscurt_[i] = sensor;}
      if (sensor->get_name() == maxchgcurt_name) {
        maxchgcurt_[i] = sensor;}
      if (sensor->get_name() == cell_1_name) {
        cell_1_[i] = sensor;}
      if (sensor->get_name() == cell_2_name) {
        cell_2_[i] = sensor;}
      if (sensor->get_name() == cell_3_name) {
        cell_3_[i] = sensor;}
      if (sensor->get_name() == cell_4_name) {
        cell_4_[i] = sensor;}
      if (sensor->get_name() == cell_5_name) {
        cell_5_[i] = sensor;}
      if (sensor->get_name() == cell_6_name) {
        cell_6_[i] = sensor;}
      if (sensor->get_name() == cell_7_name) {
        cell_7_[i] = sensor;}
      if (sensor->get_name() == cell_8_name) {
        cell_8_[i] = sensor;}
      if (sensor->get_name() == cell_9_name) {
        cell_9_[i] = sensor;}
      if (sensor->get_name() == cell_10_name) {
        cell_10_[i] = sensor;}
      if (sensor->get_name() == cell_11_name) {
        cell_11_[i] = sensor;}
      if (sensor->get_name() == cell_12_name) {
        cell_12_[i] = sensor;}
      if (sensor->get_name() == cell_13_name) {
        cell_13_[i] = sensor;}
      if (sensor->get_name() == cell_14_name) {
        cell_14_[i] = sensor;}
      if (sensor->get_name() == cell_15_name) {
        cell_15_[i] = sensor;}
      if (sensor->get_name() == cell_16_name) {
        cell_16_[i] = sensor;}
      if (sensor->get_name() == cell_temp_1_name) {
        cell_temp_1_[i] = sensor;}
      if (sensor->get_name() == cell_temp_2_name) {
        cell_temp_2_[i] = sensor;}
      if (sensor->get_name() == cell_temp_3_name) {
        cell_temp_3_[i] = sensor;}
      if (sensor->get_name() == cell_temp_4_name) {
        cell_temp_4_[i] = sensor;}
      if (sensor->get_name() == case_temp_name) {
        case_temp_[i] = sensor;}
      if (sensor->get_name() == power_temp_name) {
        power_temp_[i] = sensor;}
    }
  }
}

void SeplosParser::loop() {
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
            //ESP_LOGW("seplos", "Ungültige CRC, Paket verworfen.");
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
    //ESP_LOGI("DEBUG", "buffer[3]: 0x%02X, buffer[4]: 0x%02X", buffer[3], buffer[4]);
    uint16_t pack_voltage = (buffer[3] << 8) | buffer[4];
    int16_t current = (buffer[5] << 8) | buffer[6];
    uint16_t remaining_capacity = (buffer[7] << 8) | buffer[8];
    uint16_t total_capacity = (buffer[9] << 8) | buffer[10];
    uint16_t total_discharge_capacity = (buffer[11] << 8) | buffer[12];
    uint16_t soc = (buffer[13] << 8) | buffer[14];
    uint16_t soh = (buffer[15] << 8) | buffer[16];
    uint16_t cycle_count = (buffer[17] << 8) | buffer[18];
    uint16_t average_cell_voltage = (buffer[19] << 8) | buffer[20];
    uint16_t average_cell_temp = (buffer[21] << 8) | buffer[22];
    uint16_t max_cell_voltage = (buffer[23] << 8) | buffer[24];
    uint16_t min_cell_voltage = (buffer[25] << 8) | buffer[26];
    uint16_t max_cell_temp = (buffer[27] << 8) | buffer[28];
    uint16_t min_cell_temp = (buffer[29] << 8) | buffer[30];
    uint16_t maxdiscurt = (buffer[33] << 8) | buffer[34];
    uint16_t maxchgcurt = (buffer[35] << 8) | buffer[36];

    //ESP_LOGI("DEBUG", "pack_voltage: %d", pack_voltage);
    pack_voltage_[bms_index]->publish_state(pack_voltage / 100.0f);
    current_[bms_index]->publish_state(current / 100.0f);
    remaining_capacity_[bms_index]->publish_state(remaining_capacity / 1000.0f);
    total_capacity_[bms_index]->publish_state(total_capacity / 100.0f);
    total_discharge_capacity_[bms_index]->publish_state(total_discharge_capacity / 0.1f);
    soc_[bms_index]->publish_state(soc / 10.0f);
    soh_[bms_index]->publish_state(soh / 10.0f);
    cycle_count_[bms_index]->publish_state(cycle_count);
    average_cell_voltage_[bms_index]->publish_state(average_cell_voltage / 1000.0f);
    average_cell_temp_[bms_index]->publish_state(average_cell_temp / 10.0f - 273.15f);
    max_cell_voltage_[bms_index]->publish_state(max_cell_voltage / 1000.0f);
    min_cell_voltage_[bms_index]->publish_state(min_cell_voltage / 1000.0f);
    max_cell_temp_[bms_index]->publish_state(max_cell_temp / 10.0f - 273.15f);
    min_cell_temp_[bms_index]->publish_state(min_cell_temp / 10.0f - 273.15f);
    maxdiscurt_[bms_index]->publish_state(maxdiscurt / 100.0f);
    maxchgcurt_[bms_index]->publish_state(maxchgcurt / 100.0f);
  }

  if (buffer[2] == 0x34) {
      uint16_t cell_1 = (buffer[3] << 8) | buffer[4];
      uint16_t cell_2 = (buffer[5] << 8) | buffer[6];
      uint16_t cell_3 = (buffer[7] << 8) | buffer[8];
      uint16_t cell_4 = (buffer[9] << 8) | buffer[10];
      uint16_t cell_5 = (buffer[11] << 8) | buffer[12];
      uint16_t cell_6 = (buffer[13] << 8) | buffer[14];
      uint16_t cell_7 = (buffer[15] << 8) | buffer[16];
      uint16_t cell_8 = (buffer[17] << 8) | buffer[18];
      uint16_t cell_9 = (buffer[19] << 8) | buffer[20];
      uint16_t cell_10 = (buffer[21] << 8) | buffer[22];
      uint16_t cell_11 = (buffer[23] << 8) | buffer[24];
      uint16_t cell_12 = (buffer[25] << 8) | buffer[26];
      uint16_t cell_13 = (buffer[27] << 8) | buffer[28];
      uint16_t cell_14 = (buffer[29] << 8) | buffer[30];
      uint16_t cell_15 = (buffer[31] << 8) | buffer[32];
      uint16_t cell_16 = (buffer[33] << 8) | buffer[34];
      uint16_t cell_temp_1 = (buffer[35] << 8) | buffer[36];
      uint16_t cell_temp_2 = (buffer[37] << 8) | buffer[38];
      uint16_t cell_temp_3 = (buffer[39] << 8) | buffer[40];
      uint16_t cell_temp_4 = (buffer[41] << 8) | buffer[42];
      uint16_t case_temp = (buffer[51] << 8) | buffer[52];
      uint16_t power_temp = (buffer[53] << 8) | buffer[54];

      cell_1_[bms_index]->publish_state(cell_1 / 1000.0f);
      cell_2_[bms_index]->publish_state(cell_2 / 1000.0f);
      cell_3_[bms_index]->publish_state(cell_3 / 1000.0f);
      cell_4_[bms_index]->publish_state(cell_4 / 1000.0f);
      cell_5_[bms_index]->publish_state(cell_5 / 1000.0f);
      cell_6_[bms_index]->publish_state(cell_6 / 1000.0f);
      cell_7_[bms_index]->publish_state(cell_7 / 1000.0f);
      cell_8_[bms_index]->publish_state(cell_8 / 1000.0f);
      cell_9_[bms_index]->publish_state(cell_9 / 1000.0f);
      cell_10_[bms_index]->publish_state(cell_10 / 1000.0f);
      cell_11_[bms_index]->publish_state(cell_11 / 1000.0f);
      cell_12_[bms_index]->publish_state(cell_12 / 1000.0f);
      cell_13_[bms_index]->publish_state(cell_13 / 1000.0f);
      cell_14_[bms_index]->publish_state(cell_14 / 1000.0f);
      cell_15_[bms_index]->publish_state(cell_15 / 1000.0f);
      cell_16_[bms_index]->publish_state(cell_16 / 1000.0f);
      cell_temp_1_[bms_index]->publish_state(cell_temp_1 / 10.0f - 273.15f);
      cell_temp_2_[bms_index]->publish_state(cell_temp_2 / 10.0f - 273.15f);
      cell_temp_3_[bms_index]->publish_state(cell_temp_3 / 10.0f - 273.15f);
      cell_temp_4_[bms_index]->publish_state(cell_temp_4 / 10.0f - 273.15f);
      case_temp_[bms_index]->publish_state(case_temp / 10.0f - 273.15f);
      power_temp_[bms_index]->publish_state(power_temp / 10.0f - 273.15f);
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
