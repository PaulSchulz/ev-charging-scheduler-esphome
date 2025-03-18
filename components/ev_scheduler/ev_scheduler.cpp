#include "ev_scheduler.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/output/binary_output.h"

namespace esphome {
    namespace ev_scheduler {

        static const char *TAG = "ev_scheduler";

        void EVScheduler::setup() {
            ESP_LOGD(TAG, "Scheduler initialized");
            last_switch_time_ = millis();
        }

        void EVScheduler::loop() {
            unsigned long now = millis();
            if (now - this->last_switch_time_ >= this->schedule_interval_) {
                switch_jobs();
                last_switch_time_ = now;
            }
        }

        void EVScheduler::switch_jobs() {
            if (switches_.size() < 4) {
                ESP_LOGE(TAG, "Not enough GPIOs configured!");
                return;
            }

            // Turn OFF all switches
            for (auto *sw : switches_) {
                sw->turn_off();
            }

            // Activate two jobs in round-robin order
            int job1 = jobIndex;
            int job2 = (jobIndex + 1) % 4;

            switches_[job1]->turn_on();
            switches_[job2]->turn_on();

            ESP_LOGD(TAG, "Switching jobs: %d and %d", job1, job2);

            jobIndex = (jobIndex + 2) % 4;
        }

        void EVScheduler::add_switch(esphome::switch_::Switch *sw) {
            switches_.push_back(sw);
        }

    }  // namespace ev_scheduler
}  // namespace esphome
