# TrackCall

![C](https://img.shields.io/badge/C-A8B9CC?style=flat-square&logo=c&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=flat-square&logo=cmake&logoColor=white)
![Raspberry Pi Pico](https://img.shields.io/badge/RP2040-A22846?style=flat-square&logo=raspberrypi&logoColor=white)
![GCC ARM](https://img.shields.io/badge/GCC%20ARM-A42E2B?style=flat-square&logo=gnu&logoColor=white)
![VS Code](https://img.shields.io/badge/VS%20Code-007ACC?style=flat-square&logo=visualstudiocode&logoColor=white)

A track-call limiter for slot car racing, built on the RP2040-based Pimoroni Tiny 2040 using the Raspberry Pi Pico C/C++ SDK. When a car comes off the track, the driver needs the track de-energized to safely reset it — TrackCall gives each player exactly 3 of these calls per race, then locks them out.

## Demo

https://github.com/user-attachments/assets/500f5357-b210-4ae8-96cb-c80b4158a5c4

## How It Works

Pressing the **Track Call** button de-energizes the track for one second (so the player can put their car back on) and lights a different LED to show how many calls have been used. Once the 3rd call is used, the track can no longer be de-energized — pressing the button again just flashes all three LEDs to tell the player they're out of chances. The **Reset** button clears the call count back to zero for the next race/heat.

| Call # | LED | Track Power (Relay) |
|:---:|:---:|:---:|
| 0 (ready) | Green | energized |
| 1st call | Yellow | de-energized for 1s |
| 2nd call | Red | de-energized for 1s |
| 3rd call | all off | de-energized for 1s |
| 4th+ attempt | all 3 LEDs flash once | stays energized — call denied |

Inputs are debounced with a 50ms settle read, and the main loop runs on a 250ms cycle.

## Hardware

### Pimoroni Tiny 2040 Pinout

![Tiny 2040 Pinout](./Tiny2040-Pinout.png)

Built and wired against the schematic below.

![My Schematic](./TrackCallZeroSchematic-1.png)

| Component | GPIO |
|---|:---:|
| Track Call button | 2 |
| Green LED | 3 |
| Yellow LED | 4 |
| Red LED | 5 |
| Relay | 6 |
| Reset button | 7 |

## Building & Flashing

**Requirements:** [Raspberry Pi Pico C/C++ SDK](https://github.com/raspberrypi/pico-sdk), CMake, and an ARM GCC embedded toolchain (`arm-none-eabi-gcc`).

Easiest path: open this repo in VS Code with the [Raspberry Pi Pico extension](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico) installed, then run **Compile Project** from its sidebar — it handles the SDK, toolchain, and build for you.

Manual build:

```bash
git clone https://github.com/olael94/TrackCall.git
cd TrackCall
mkdir build && cd build
cmake ..
make
```

To flash: hold **BOOTSEL** on the Tiny 2040 while plugging it into USB, then drag `build/TrackCall.uf2` onto the drive that appears.

## Project Structure

```
TrackCall.c                  — state machine + GPIO logic
CMakeLists.txt                — build configuration
pico_sdk_import.cmake         — pulls in the Pico SDK
TrackCallZeroSchematic-1.png  — circuit schematic
```
