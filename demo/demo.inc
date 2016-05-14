#include "colors.inc"


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
