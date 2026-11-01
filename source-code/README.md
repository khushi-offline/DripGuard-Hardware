# DripGuard Source Code

This directory contains the firmware and testing programs developed for the DripGuard Smart IV Infusion Monitoring and Prediction System.

## Directory Structure

### `working-code/`

Contains the main working firmware and an earlier firmware version.

- **`dripguard_two_way_communication.ino`** — Main firmware that receives settings from the Python dashboard and sends updated IV monitoring readings back to the dashboard.
- **`dripguard_one_way_communication.ino`** — Earlier firmware that sends IV monitoring readings to the Python backend.

See [`working-code/README.md`](working-code/README.md) for details.

### `testing-code/`

Contains five individual programs for testing the drop sensor, status LEDs, buzzer, drop counting, and flow-rate, volume, and time calculations.

See [`testing-code/README.md`](testing-code/README.md) for details.

## Development Environment

- **Firmware language:** Arduino C/C++
- **Hardware platform:** NodeMCU ESP8266
- **Firmware development environment:** Arduino IDE
- **Dashboard and backend:** Python

## Configuration

Configure the required Wi-Fi credentials and server IP address in the firmware before running it on your local network.
