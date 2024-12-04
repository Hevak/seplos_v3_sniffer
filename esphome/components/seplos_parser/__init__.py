import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID, CONF_UART_ID

DEPENDENCIES = ["uart"]

seplos_parser_ns = cg.esphome_ns.namespace("seplos_parser")
SeplosParser = seplos_parser_ns.class_("SeplosParser", cg.Component) #cg.PollingComponent, uart.UARTDevice)

CONF_BMS_COUNT = "bms_count"
CONF_UART_ID = "uart_id" #neu
CONF_SENSORS = "sensors"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SeplosParser),
    cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
    cv.Required(CONF_BMS_COUNT): cv.int_range(min=1, max=16),
    cv.Optional(CONF_SENSORS, default=[]): cv.ensure_list(sensor.SENSOR_SCHEMA),
}).extend(uart.UART_DEVICE_SCHEMA) #cv.COMPONENT_SCHEMA)

async def to_code(config):
    # Erstelle eine Instanz der SeplosParser-Komponente
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # UART-Komponente verknüpfen
    uart_component = await cg.get_variable(config[CONF_UART_ID])
    cg.add(var.set_uart_parent(uart_component))

    # BMS-Anzahl setzen
    cg.add(var.set_bms_count(config[CONF_BMS_COUNT]))

    # Sensoren hinzufügen
    for sensor_config in config[CONF_SENSORS]:
        sens = await sensor.new_sensor(sensor_config)
        cg.add(var.add_sensor(sens))
