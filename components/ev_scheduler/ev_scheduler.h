#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
// #include "esphome/components/output/binary_output.h"

namespace esphome {
    namespace ev_scheduler {

        class EVScheduler : public Component {
        public:
            void setup() override;
            void loop() override;

            static const char *get_id();
            void add_switch(esphome::switch_::Switch *sw);
            void set_schedule_interval(uint32_t interval) { schedule_interval_ = interval; }

        private:
            std::vector<esphome::switch_::Switch *> switches_;

            unsigned long last_switch_time_ = 0;
            int jobIndex = 0;
            uint32_t schedule_interval_{300000};  // Default to 5 minutes in milliseconds

            void switch_jobs();
        };

    }  // namespace ev_scheduler
}  // namespace esphome
