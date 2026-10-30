# DripGuard — Smart IV Infusion Monitoring and Prediction System

## Project Overview

**DripGuard** is a Smart IV Infusion Monitoring and Prediction System developed to monitor intravenous (IV) fluid flow and provide real-time information about the infusion process.

The system uses a NodeMCU ESP8266 and an IR drop sensor to detect and count IV drops. It processes the collected data to calculate the flow rate, infused volume, and estimated remaining infusion time. These readings are communicated to a Python-based dashboard for monitoring.

DripGuard also supports two-way communication, allowing the dashboard to send settings such as bed volume and drip factor to the ESP8266 through the **Apply Settings** option.

## Key Features

- Real-time IV drop detection and counting.
- IV flow-rate monitoring.
- Calculation of infused fluid volume.
- Estimation of remaining infusion time.
- Two-way communication between the ESP8266 and Python dashboard.
- Configurable bed volume and drip factor through the dashboard.
- Visual status indication using LEDs.
- Audio alerts using a buzzer.

## Hardware Components

The hardware implementation includes:

- NodeMCU ESP8266
- IR drop sensor
- Status LEDs
- Buzzer
- IV fluid setup
- Connecting wires and supporting electronic components

## Repository Structure

```text
DripGuard-Hardware/
│
├── hardware-photos/
│   ├── README.md
│   ├── hardware_components_labeled.jpg
│   ├── assembled_hardware_setup.jpg
│   └── complete_dripguard_prototype.jpg
│
├── source-code/
│   ├── README.md
│   ├── working-code/
│   │   ├── README.md
│   │   ├── dripguard_two_way_communication.ino
│   │   └── dripguard_one_way_communication.ino
│   │
│   └── testing-code/
│       ├── README.md
│       ├── test_01_drop_sensor.ino
│       ├── test_02_status_leds.ino
│       ├── test_03_buzzer.ino
│       ├── test_04_drop_counting.ino
│       └── test_05_flow_volume_time_calculation.ino
│
└── project-documentation/
    ├── Project_Report.pdf
    ├── DripGuard_Presentation.pptx
    ├── PRESENTATION.md
    └── HARDWARE_DEMONSTRATION.md
```

## Hardware Implementation

The `hardware-photos/` directory contains photographs of the individual hardware components, assembled electronic connections, and the complete DripGuard prototype.

## Source Code

The `source-code/` directory is divided into working firmware and testing programs.

### Working Firmware

The `working-code/` directory contains two firmware versions:

**`dripguard_two_way_communication.ino` — Main Working Firmware**

The primary firmware used for the hardware implementation and project demonstration.

- Receives bed volume and drip factor settings from the Python dashboard.
- Uses the received settings for drop counting and IV monitoring calculations.
- Sends updated readings, including drop count, flow rate, infused volume, and remaining time, to the dashboard.

**`dripguard_one_way_communication.ino` — Earlier Firmware**

The earlier firmware version that sends IV monitoring readings from the NodeMCU ESP8266 to the Python backend for dashboard display.

### Testing Programs

The `testing-code/` directory contains five programs developed to test individual hardware components and monitoring functions.

| Program | Testing Purpose |
|---|---|
| `test_01_drop_sensor.ino` | Drop sensor detection |
| `test_02_status_leds.ino` | Status LED operation |
| `test_03_buzzer.ino` | Buzzer operation |
| `test_04_drop_counting.ino` | IV drop counting |
| `test_05_flow_volume_time_calculation.ino` | Flow rate, infused volume, and remaining time calculations |

## Project Documentation

The `project-documentation/` directory contains the supporting documents and demonstration resources.

- [Project Report](project-documentation/Project_Report.pdf)
- [Project Presentation](project-documentation/PRESENTATION.md)
- [Hardware Demonstration Video](project-documentation/HARDWARE_DEMONSTRATION.md)

## Technologies Used

- **Embedded Platform:** NodeMCU ESP8266
- **Programming Language:** Arduino C/C++
- **Dashboard and Backend:** Python
- **Communication:** Wi-Fi
- **Sensing:** IR drop sensor

## Team Members

This project was developed by:

1. **Khushi Patil**
2. **Mrunali Kamble**
3. **Swati Mahto**

## Project Information

- **Project Name:** DripGuard — Smart IV Infusion Monitoring and Prediction System
- **Repository:** DripGuard-Hardware
- **Project Type:** Academic Hardware and Embedded Systems Project

## Configuration Note

Before running the firmware, configure the Wi-Fi network credentials and server IP address according to your local network settings.

---

*This repository contains the hardware implementation, firmware, testing programs, photographs, and supporting documentation for the DripGuard project.*
