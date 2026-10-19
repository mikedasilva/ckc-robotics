# Wiring

Pin assignments used by `firmware/line_follower/line_follower.ino` on the Arduino Nano.

## Current Arduino pin assignments

| Connection               | Arduino pin |
|--------------------------|-------------|
| Left IR sensor OUT       | D2          |
| Right IR sensor OUT      | D3          |
| Left motor driver A-IA   | D5          |
| Left motor driver A-IB   | D6          |
| Right motor driver B-IA  | D9          |
| Right motor driver B-IB  | D10         |

The sections below give more detail on each group.

## Line sensors (TCRT5000, digital inputs)

| Sensor | Nano pin | Reading |
|--------|----------|---------|
| Left   | D2       | `LOW` = black line, `HIGH` = white surface |
| Right  | D3       | `LOW` = black line, `HIGH` = white surface |

## Motors (PWM outputs to L9110S motor driver)

Each motor uses two PWM pins on the L9110S dual motor driver. Driving `A` forward / `B` low moves the wheel forward; the reverse moves it backward.

| Motor | Pin A (forward) | Pin B (reverse) |
|-------|-----------------|-----------------|
| Left  | D5              | D6              |
| Right | D9              | D10             |

All four motor pins are PWM-capable on the Nano, which is required for `analogWrite`.

## Notes

- If a wheel spins the wrong way, swap that motor's two leads at the driver (or swap its A/B pin constants in the sketch).
- If the car steers away from the line instead of toward it, the sensors may be swapped or report inverted logic — check `BLACK`/`WHITE` in the sketch.
