# UOSM Telemetry

Project for the embedded software running on the UOSM 2023 Telemetry board.

Currently uses an esp32-s3-devkitc-1

## Setup
1. Install CLion
2. Open the project
3. Install the PlatformIO Plugin (You should be prompted)
4. Your good to go

It's important to install CLion 2023.2 or newer. It adds proper PlatformIO support.


## Pins

FSPID (Master Out) -> Slave In
FSPIQ (Master In) -> Slave Out
FSPICLK (Clk) -> Slave Clk
FSPICS0 (CS) -> Chip Enable

## Notes

Cannot find "Update.h" resolved by using deep+ ldf in .ini