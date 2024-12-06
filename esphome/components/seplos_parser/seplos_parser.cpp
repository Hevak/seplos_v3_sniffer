#include "seplos_parser.h"
#include "esphome/core/log.h"

namespace esphome {
namespace seplos_parser {

static const char *TAG = "seplos_parser.component";

void SeplosParser::setup() {
    
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


}  // namespace seplos_parser
}  // namespace esphome
