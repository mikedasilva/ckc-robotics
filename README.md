# CKC Robotics

A collection of robotics programs. Each project lives in its own folder with its own code, docs, and parts list.

## Projects

| Project | Description | Controller |
|---------|-------------|------------|
| [line-following-car](line-following-car/) | LEGO-built car that follows a black line using two IR sensors | Arduino Nano |

## Adding a new project

Create a new top-level folder (e.g. `my-new-robot/`) following the same layout:

```
my-new-robot/
  README.md       # What it does and how to build/upload it
  firmware/       # Microcontroller code (one folder per sketch)
  docs/           # Parts list, wiring, notes
```

Then add a row to the **Projects** table above.
