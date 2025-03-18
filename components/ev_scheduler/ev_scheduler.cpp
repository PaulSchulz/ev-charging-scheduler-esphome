#include "ev_scheduler.h"

namespace esphome {
    namespace ev_scheduler {

        static const char *TAG = "ev_scheduler";

        void EVScheduler::setup() {
            ESP_LOGD(TAG, "Scheduler initialized");
            last_switch_time_ = millis();

            //active_ = id(active);
            // Optionally, you can check the switch state during setup
            // update_scheduler_state();

        }

        void EVScheduler::loop() {
            unsigned long now = millis();
            if (now - this->last_switch_time_ >= this->schedule_interval_) {
                switch_jobs();
                last_switch_time_ = now;
            }
        }

        void EVScheduler::dump_config() {
            ESP_LOGCONFIG(TAG, "EV Scheduler:");
            ESP_LOGCONFIG(TAG, "  Schedule interval: %d ms", schedule_interval_);

            ESP_LOGCONFIG(TAG, "  Active Switch: %s (State: %s)",
                                          active_->get_name().c_str(),
                                          active_->state ? "ON" : "OFF");

            ESP_LOGCONFIG(TAG, "  Active charge points:");
            if (switches_.empty()) {
                ESP_LOGCONFIG(TAG, "    (None)");
            } else {
                for (auto *sw : switches_) {
                    if (sw != nullptr) {
                        ESP_LOGCONFIG(TAG, "    - Switch: %s (State: %s)",
                                      sw->get_name().c_str(),
                                      sw->state ? "ON" : "OFF");
                    }
                }
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
            int job2 = (jobIndex + 1) % switches_.size();

            switches_[job1]->turn_on();
            switches_[job2]->turn_on();

            ESP_LOGD(TAG, "Switching points on: %d, %d", job1, job2);

            jobIndex = (jobIndex + 2) % switches_.size();
        }

        void EVScheduler::add_switch(esphome::switch_::Switch *sw) {
            switches_.push_back(sw);
        }

        void EVScheduler::update_scheduler_state() {
            if (active_ != nullptr) {
                // Check the state of the operating switch
                if (active_->state) {
                    // Scheduler is active
                    ESP_LOGD(TAG, "Scheduler is active.");
                    // Add logic here to enable the scheduler (e.g., start tasks)
                } else {
                    // Scheduler is off
                    ESP_LOGD(TAG, "Scheduler is OFF.");
                    // Add logic here to disable the scheduler (e.g., stop tasks)
                }
            }
        }




    }  // namespace ev_scheduler
}  // namespace esphome
