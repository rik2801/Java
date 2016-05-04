#include "rubik-cube.inc"


camera {
  location <2, 2, -7>
  look_at  <0, 0,  0>
}


light_source {
  <2, 4, -3>
  color White
}

light_source {
  <4, 2, -3>
  color White
}


// Axis
cylinder {
  <0, 0, 0>, <5, 0, 0>, 0.01
  open
  pigment { Red }
}

cylinder {
  <0, 0, 0>, <0, 5, 0>, 0.01
  open
  pigment { Green }
}

cylinder {
  <0, 0, 0>, <0, 0, 5>, 0.01
  open
  pigment { Blue }
}


// Cube
rubik_cube_create_cube(
  3, 3, 3, rubik_cube_colors_classic,
  array[4] {<90, 0, 0, 1>, <0, 0, 90, 1>, <-90, 0, 0, 1>, <0, 0, -90, 1>}
)
