
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

CONFIG_SCHEMA = sensor.sensor_schema(SeplosParser).extend(
    {
        cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
        cv.Required(CONF_BMS_COUNT): cv.int_range(min=1, max=16),
        cv.Required(CONF_THROTTLE_INTERVAL): cv.positive_int,
    }
)

async def to_code(config):
    # Erstelle die SeplosParser-Instanz
    var = cg.new_Pvariable(
        config[CONF_ID],
        await cg.get_variable(config[CONF_UART_ID]),  # Hole die UART-Instanz
        config[CONF_BMS_COUNT],
        config[CONF_THROTTLE_INTERVAL]
    )
    # Registriere die SeplosParser-Komponente
    await cg.register_component(var, config)
    except Exception as e:
        cg.esphome_ns.logger.error(f"Error while registering component: {e}")

    # Registriere die UART-Instanz für die SeplosParser-Komponente
    await uart.register_uart_device(var, config[CONF_UART_ID])
    except Exception as e:
        cg.esphome_ns.logger.error(f"Error while registering UART device: {e}")

