import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID

# Benutzerdefinierte Konfigurationsoptionen
CONF_BMS_COUNT = 'bms_count'
CONF_UART_ID = 'uart_id'
CONF_THROTTLE_INTERVAL = 'throttle_interval'

DEPENDENCIES = ['uart']

seplos_parser_ns = cg.esphome_ns.namespace('seplos_parser')
SeplosParser = seplos_parser_ns.class_('SeplosParser', cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SeplosParser),
    cv.Required(CONF_BMS_COUNT): cv.int_,
    cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
    cv.Optional(CONF_THROTTLE_INTERVAL, default=5): cv.int_,
}).extend(sensor.SENSOR_SCHEMA)

async def to_code(config):
    # Debugging-Ausgabe
    print(f"Registering SeplosParser with ID: {config[CONF_ID]}")

    
    # Registriere die UART-Komponente
    uart_var = await cg.get_variable(config[CONF_UART_ID])

    # Erstelle die SeplosParser-Instanz
    var = cg.new_Pvariable(
        config[CONF_ID],
        uart_var,  # Die aufgelöste UART-Variable
        config[CONF_BMS_COUNT],
        config[CONF_THROTTLE_INTERVAL]
    print(f"SeplosParser instance created: {var}")
    )

    # Registriere die SeplosParser-Komponente
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config[CONF_UART_ID])

