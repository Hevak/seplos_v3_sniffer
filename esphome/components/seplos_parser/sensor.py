import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID, CONF_BMS_COUNT

DEPENDENCIES = ['uart']

seplos_parser_ns = cg.esphome_ns.namespace('seplos_parser')
SeplosParser = seplos_parser_ns.class_('SeplosParser', cg.Component, uart.UARTDevice)

CONF_UART_ID = 'uart_id'
CONF_THROTTLE_INTERVAL = 'throttle_interval'

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SeplosParser),
    cv.Required(CONF_BMS_COUNT): cv.int_,
    cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
    cv.Optional(CONF_THROTTLE_INTERVAL, default=5): cv.int_,  # Standardwert 5 Sekunden
}).extend(sensor.SENSOR_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_UART_ID], config[CONF_BMS_COUNT], config[CONF_THROTTLE_INTERVAL])
    await cg.register_component(var, config)
    uart.setup_uart(var.uart, config)
