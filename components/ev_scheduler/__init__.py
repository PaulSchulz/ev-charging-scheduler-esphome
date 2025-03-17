# __init__.py

# This file can be left empty, or you could import specific components if needed.
# For instance, if you have a more complex structure, you could import:
# from .ev_scheduler import EVChargingScheduler
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import output
from esphome.const import CONF_ID, CONF_PIN

ev_scheduler_ns = cg.esphome_ns.namespace("ev_scheduler")
EVScheduler = ev_scheduler_ns.class_("EVScheduler", cg.Component)

CONFIG_SCHEMA = output.BINARY_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(EVScheduler),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await output.register_output(var, config)
    await cg.register_component(var, config)
