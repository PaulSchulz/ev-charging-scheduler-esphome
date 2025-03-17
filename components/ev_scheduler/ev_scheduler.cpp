#include "ev_scheduler.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/output/binary_output.h"

namespace esphome {
    namespace ev_scheduler {

        static const char *TAG = "ev_scheduler";

        // Constructor
        //EVScheduler(Switch *relay_1, Switch *relay_2, Switch *relay_3, Switch *relay_4)
        //: relay_1_(relay_1), relay_2_(relay_2), relay_3_(relay_3), relay_4_(relay_4) {}

        void EVScheduler::setup() {
            ESP_LOGD(TAG, "Scheduler initialized");
            lastSwitchTime = millis();
        }

        void EVScheduler::loop() {
            unsigned long now = millis();

            if (now - lastSwitchTime >= SWITCH_INTERVAL) {
                switch_jobs();
                lastSwitchTime = now;
            }
        }

        //void EVScheduler::set_gpio_switches(std::vector<switch_::Switch *> switches) {
        //switches_ = switches;
        //}

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

    }  // namespace ev_scheduler
}  // namespace esphome
