# robot_arm
Robot Arm Using Arduino Mega and L293D Motor Control Module

### Dependencies
- [AFMotor.h](https://github.com/adafruit/Adafruit-Motor-Shield-library)
- math.h

## Mathematical Modelling
> [Interative Model](https://www.geogebra.org/m/aj8tkt9k)
>  ![Geogebra Model](https://i.imgur.com/pIoHShv.jpg)

Let `a` and `b`  be the `red` and `green` arm lengths respectively

Then for a coordinate `(r, h)`, angles `alpha` (angle of `red` arm from `X' axis`) and `beta` (angle of `green` arm from `red arm` in counter-clockwise direction) are given by the following relation:

> ![angles](https://i.imgur.com/i8E7hCJ.jpg)

## Major Components
- Arduino
- Three DC Motors
- Three Potentiometers
- L293D Motor Control Module

## Set-up
1. Each Motor is coupled with a potentiometer so that the angles can be measured. Configuration is important and **therefore the code needs to be modified accordingly**.
2. `Motor 1` is used at the bottom to turn the plane of arms at a desired angle `theta` from starting vertical plane (say `XY`).
3. `Motor 2` is used at the root of `red` arm and measures angle `alpha`.
4. `Motor 3` is used at the root of junction of `red` and `green` arms and measures angle `beta`(angle of `green` arm from `red arm` in counter-clockwise direction).
5. Analog Pins of `Motor 1`, `Motor 2` and `Motor 3` potentiometers are connected to `A8`, `A9` and `A10` pin slots respectively.

## Contributos
1. Abhishek Kr Mishra
2. Akash Chauhan
3. Umakant Vashishtha
