# Line-Following Car

Code for a LEGO-built line-following robot car controlled by an **Arduino Nano**.

## Project layout

```
firmware/
  line_follower/
    line_follower.ino   # Main sketch loaded onto the Nano
    sketch.yaml         # arduino-cli build profile (Nano board settings)
docs/
  parts.md              # Parts list (electronics)
  wiring.md             # Sensor and motor pin assignments
```

## How it works

Two downward-facing line sensors sit on either side of a black line:

- **Both on white (or both on black)** → drive straight.
- **Left sensor on black** → turn left (left wheel reverses, right wheel moves forward).
- **Right sensor on black** → turn right.

Extra behaviors to keep the LEGO drivetrain reliable:

- **Stable sensor reads** — each sensor is sampled 5 times and majority-voted to filter noise.
- **Kickstart** — when a motor changes direction it's briefly driven at a higher speed to overcome friction.
- **Recovery boost** — when coming out of a turn, both wheels get a short burst of forward power.

All speeds and timings are constants at the top of the sketch for easy tuning.

## Uploading to the Nano

### Arduino IDE

1. Open `firmware/line_follower/line_follower.ino`.
2. **Tools → Board → Arduino AVR Boards → Arduino Nano**.
3. **Tools → Processor** → `ATmega328P` (try `ATmega328P (Old Bootloader)` if the upload fails — common on clones).
4. Select the port under **Tools → Port** and click **Upload**.

### arduino-cli

```sh
arduino-cli core install arduino:avr
cd line-following-car/firmware/line_follower
arduino-cli compile --profile nano
arduino-cli upload  --profile nano -p /dev/cu.usbserial-XXXX
```

Use `--profile nano-old-bootloader` for Nano clones with the older bootloader. Run `arduino-cli board list` to find the port.

## Parts and wiring

- Parts list: [docs/parts.md](docs/parts.md)
- Pin assignments: [docs/wiring.md](docs/wiring.md)
