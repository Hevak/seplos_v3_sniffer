#include "esphome/core/log.h"
#include "seplos_parser.h"

namespace esphome {
namespace seplos_parser {

static const char *TAG = "seplos_parser.component";

void SeplosParser::setup() {

}

void SeplosParser::loop() {

}

void SeplosParser::dump_config(){
    ESP_LOGCONFIG(TAG, "Seplos Parser");
}


}  // namespace seplos_parser
}  // namespace esphome
