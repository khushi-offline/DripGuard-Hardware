# DripGuard Hardware Source Code

## Code 19 — One-Way Communication
The original firmware sends the latest IV monitoring readings from NodeMCU ESP8266 to the Python backend for dashboard display.

## Code 20 — Two-Way Communication (Main Working Code)
Code 20 is the modified version of Code 19 and is the main firmware used for the project demonstration.

- Python dashboard sends bed volume and drip factor settings to NodeMCU ESP8266 through the **Apply Settings** option.
- ESP8266 uses these settings for drop counting and IV monitoring calculations.
- ESP8266 generates updated readings, including drop count, flow rate, infused volume, and remaining time, and sends them to Python for dashboard display.

## Testing Programs
The `testing-code/` directory contains five programs for testing individual hardware components and monitoring functions.
