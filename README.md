# robot_arm
Robot Arm Using Arduino Mega and L293D Motor Control Module

### Dependencies
- [AFMotor.h](https://github.com/adafruit/Adafruit-Motor-Shield-library)
- math.h

# Mathmatical Modelling
> [Interative Model](https://www.geogebra.org/m/aj8tkt9k)
>  ![Geogebra Model](https://i.imgur.com/pIoHShv.jpg)

Let `a` and `b`  be the `red` and `green` arm lengths respectively

Then for a coordinate `(r, h)`, 
angles `alpha` (angle of `red` arm from `X' axis`) and 
`beta` (angle of `green` arm from `red arm` in counter-clockwise direction) 
are given by the following relation:

> ![angles](https://i.imgur.com/i8E7hCJ.jpg)

