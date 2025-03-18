#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/output/binary_output.h"

namespace esphome {
    namespace ev_scheduler {

        class EVScheduler : public Component {
        public:
            void setup() override;
            void loop() override;

            static const char *get_id();
            void add_switch(esphome::switch_::Switch *sw);
        private:
            std::vector<esphome::switch_::Switch *> switches_;

            unsigned long lastSwitchTime = 0;
            int jobIndex = 0;
            // const unsigned long SWITCH_INTERVAL = 300000;  // 5 minutes
            const unsigned long SWITCH_INTERVAL = 10000;  // 10 seconds

            void switch_jobs();
        };

    }  // namespace ev_scheduler
}  // namespace esphome
