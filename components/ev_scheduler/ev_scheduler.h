#pragma once

#include "esphome/core/component.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
    namespace ev_scheduler {

        class EVScheduler : public Component {
        public:
            void setup() override;
            void loop() override;
            void dump_config() override;

            // static const char *get_id();
            void add_switch(esphome::switch_::Switch *sw);
            void set_schedule_interval(uint32_t interval) { schedule_interval_ = interval; }
            void set_active(esphome::switch_::Switch *active) { active_ = active; }

            void update_scheduler_state();

        private:
            uint32_t schedule_interval_{300000};  // Default to 5 minutes in milliseconds
            std::vector<esphome::switch_::Switch *> switches_;
            esphome::switch_::Switch *active_ = nullptr;

            unsigned long last_switch_time_ = 0;
            int jobIndex = 0;

            void switch_jobs();
        };

    }  // namespace ev_scheduler
}  // namespace esphome
