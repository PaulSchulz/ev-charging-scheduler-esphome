# __init__.py

# This file can be left empty, or you could import specific components if needed.
# For instance, if you have a more complex structure, you could import:
# from .ev_scheduler import EVChargingScheduler
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import switch

AUTO_LOAD = ["switch"]
CONF_SWITCHES = "switches"
CONF_SCHEDULE_INTERVAL = "schedule_interval"

ev_scheduler_ns = cg.esphome_ns.namespace("ev_scheduler")
EVScheduler = ev_scheduler_ns.class_("EVScheduler", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(EVScheduler),
        cv.Required(CONF_SWITCHES): cv.ensure_list(cv.use_id(switch.Switch)),
        cv.Optional(CONF_SCHEDULE_INTERVAL, default="5min"): cv.positive_time_period_milliseconds,
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    for conf in config[CONF_SWITCHES]:
        sw = await cg.get_variable(conf)
        cg.add(var.add_switch(sw))

    cg.add(var.set_schedule_interval(config[CONF_SCHEDULE_INTERVAL]))
