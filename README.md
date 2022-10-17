## heating-fan-switch

Challange: A fan has to run when the heating is powered, to improve the heat-up-time of a room.

## Hardware

- 1x Arduino nano
- 1x 100k 1% Resisitor
- 1x 100k ptc (3D Printer heatbed sensor)
- 1x N-Channel MOSFET which is full-on @5V GS-Voltage, i.E. Si4776DY

### Schematic

Arduino +5V -> Power (+5V)
Arduino GND  -> POWER (GND)

100k Thermistor (Pin A) -> Power (+5V)
100k Thermistor (Pin B) -> Arduino A0

100k Resisistor (Pin A) -> Arduino A0
100k Resisistor (Pin B) -> POWER (GND)

MOSFET (G) -> Arduino D0
MOSFET (S) -> POWER (GND)

Load (+) -> Power +5V
Load (-) -> MOSFET (D)
