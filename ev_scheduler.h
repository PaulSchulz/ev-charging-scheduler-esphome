#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
    namespace ev_scheduler {

        class EVScheduler : public Component {
 public:
            void setup() override;
            void loop() override;

  void set_gpio_switches(std::vector<switch_::Switch *> switches);

 private:
  std::vector<switch_::Switch *> switches_;
  unsigned long lastSwitchTime = 0;
  int jobIndex = 0;
  const unsigned long SWITCH_INTERVAL = 300000;  // 5 minutes

  void switch_jobs();
        };

    }  // namespace ev_scheduler
}  // namespace esphome
