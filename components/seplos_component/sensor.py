import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID, UNIT_VOLT, UNIT_AMPERE, UNIT_PERCENT, ICON_FLASH, STATE_CLASS_MEASUREMENT

DEPENDENCIES = ["uart"]

seplos_ns = cg.esphome_ns.namespace("seplos_component")
SeplosComponent = seplos_ns.class_("SeplosComponent", cg.PollingComponent, uart.UARTDevice)

CONF_BMS_COUNT = "bms_count"
CONF_UART_ID = "uart_id"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SeplosComponent),
    cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
    cv.Required(CONF_BMS_COUNT): cv.int_range(min=1, max=16),
}).extend(cv.polling_component_schema("1s"))

def to_code(config):
    uart_component = yield cg.get_variable(config[CONF_UART_ID])
    var = cg.new_Pvariable(config[CONF_ID], uart_component, config[CONF_BMS_COUNT])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config)
