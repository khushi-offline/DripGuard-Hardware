# DripGuard Working Firmware

This directory contains the firmware developed for the DripGuard Smart IV Infusion Monitoring and Prediction System.

## Firmware Files

### 1. `dripguard_two_way_communication.ino`
**Main Working Firmware**

The primary firmware used for the hardware implementation and project demonstration.

- Receives bed volume and drip factor settings from the Python dashboard through the Apply Settings option.
- Uses the received settings for drop counting and IV monitoring calculations.
- Sends updated readings, including drop count, flow rate, infused volume, and remaining time, to the Python dashboard.

### 2. `dripguard_one_way_communication.ino`
**Earlier Firmware Version**

The initial firmware developed for one-way communication. It sends the latest IV monitoring readings from the NodeMCU ESP8266 to the Python backend for dashboard display.
