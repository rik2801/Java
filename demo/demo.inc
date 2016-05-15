#version 3.7;

#include "colors.inc"


light_source {
  <-1000, 1000, -1000>
  color White
}


light_source {
  <1000, 1000, -1000>
  color White
}


sky_sphere {
  pigment { color White }
}


camera {
  location <3, 3, -4>
  look_at  <0, 0,  0>
}
