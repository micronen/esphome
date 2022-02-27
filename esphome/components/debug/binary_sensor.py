import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import CONF_ID, CONF_LOOP_HIGH_FREQUENCY
from . import CONF_DEBUG_ID, DebugComponent

DEPENDENCIES = ["debug"]

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(CONF_DEBUG_ID): cv.use_id(DebugComponent),
            cv.Optional(
                CONF_LOOP_HIGH_FREQUENCY
            ): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
                {
                    cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                }
            ),
        }
    ).extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    debug_component = await cg.get_variable(config[CONF_DEBUG_ID])

    if CONF_LOOP_HIGH_FREQUENCY in config:
        sens = cg.new_Pvariable(config[CONF_LOOP_HIGH_FREQUENCY][CONF_ID])
        await binary_sensor.register_binary_sensor(
            sens, config[CONF_LOOP_HIGH_FREQUENCY]
        )
        cg.add(debug_component.set_loop_high_frequency(sens))
