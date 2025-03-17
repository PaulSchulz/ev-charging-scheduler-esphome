# **EV Charging Scheduler for ESPHome**

## **Overview**
This is an **ESPHome external component** that schedules and controls **EV charging relays** in a **round-robin** fashion. It switches **two active relays** among four jobs **every 5 minutes**.

## **Features**
✅ Round-robin scheduling of **EV chargers or loads**
✅ Controls **multiple GPIOs**
✅ Integrates seamlessly with **Home Assistant**
✅ Configurable via ESPHome **YAML**

## **Installation**
### **1. Add External Component to ESPHome**
Modify your **ESPHome YAML** to include the component from this repository:

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/PaulSchulz/ev-charging-scheduler-esphome
      ref: main
```

### **2. Configure GPIO Relays**
Define **four GPIO switches** for relay control:

```yaml
switch:
  - platform: gpio
    pin: 18
    id: relay_1
  - platform: gpio
    pin: 19
    id: relay_2
  - platform: gpio
    pin: 21
    id: relay_3
  - platform: gpio
    pin: 22
    id: relay_4
```

### **3. Enable the Scheduler**
Add the **scheduler component** and specify the relays it controls:

```yaml
ev_scheduler:
  id: my_scheduler
  switches:
    - id: relay_1
    - id: relay_2
    - id: relay_3
    - id: relay_4
```

## **How It Works**
- At **startup**, the scheduler initializes and starts **switching jobs**.
- Every **5 minutes**, it **turns off all relays** and **activates the next two** in sequence.
- The **cycle repeats indefinitely** unless overridden manually in Home Assistant.

## **Customization**
Modify the **switching interval** in `ev_scheduler.cpp`:
```cpp
const unsigned long SWITCH_INTERVAL = 300000;  // Default: 5 minutes
```

## **Logs & Debugging**
Enable logging to see scheduler status:
```yaml
logger:
  level: DEBUG
```

## **Home Assistant Integration**
- Manually override **relays** in Home Assistant using `switch.toggle`.
- Automate scheduling based on **solar availability** or **grid pricing**.

## **Future Improvements**
- [ ] Make the switch interval **configurable in YAML**
- [ ] Add **Home Assistant services** for manual control
- [ ] Support **more than 4 relays**

---
This ESPHome External Component was created with the assistance of ChatGPT

This README gives clear **setup instructions**, **how the component works**, and potential **future features**. Would you like to add anything specific? 🚀
