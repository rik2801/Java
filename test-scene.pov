#include "rubik-cube.inc"


camera {
  location <4, 4, -8>
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
  rubik_cube_generate_random_movements(<3, 3, 3>, 2, seed(1))
)
