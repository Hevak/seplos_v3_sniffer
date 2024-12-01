import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID, CONF_UART_ID

DEPENDENCIES = ["uart"]

seplos_ns = cg.esphome_ns.namespace("seplos_parser")
SeplosParser = seplos_ns.class_("SeplosParser", cg.PollingComponent, uart.UARTDevice)

CONF_BMS_COUNT = "bms_count"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SeplosParser),
    cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
    cv.Required(CONF_BMS_COUNT): cv.int_range(min=1, max=16),
}).extend(cv.polling_component_schema("1s"))

def to_code(config):
    uart_component = yield cg.get_variable(config[CONF_UART_ID])
    var = cg.new_Pvariable(config[CONF_ID], uart_component, config[CONF_BMS_COUNT])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config)

