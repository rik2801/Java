#version 3.7;

#include "../rubik-cube.inc"
#include "colors.inc"
#include "textures.inc"


camera {
  location <0, 3, -4>
  look_at  <0, 0,  0>
  focal_point <0, 0.6, -0.75> blur_samples 20 aperture 0.4
}


// Light sources
light_source {
  <-4, 4, -4> * 0.5,
  color White
  fade_distance 4 fade_power 2
  area_light 3 * x, 3 * y, 12, 12 circular orient adaptive 0
}


light_source {
  <0, -0.5, 0>
  color White
  fade_distance 1 fade_power 2
}


sky_sphere {
  pigment { White }
}


// Textures
#local Floor_T = texture {
  pigment {
    White_Wood
    scale <0.5, 0.5, 5>
  }
  normal {
    average
    normal_map {
      [ 1 gradient x 2 slope_map { [0 <0, 1>][0.05 <  1, 0>][0.95 <1, 0>][1 <0, -1>] } scale 2 ]
      [ 1 wood 0.5     slope_map { [0 <0, 0>][0.5  <0.5, 1>][1    <1, 0>]            } turbulence 0.5 scale <0.5, 0.5, 2>]
    }
  }
  finish {
    specular 0.2
    reflection 0.1
  }
};


#local Mirror_T = finish {
  reflection {1.0}
  ambient 0
  diffuse 0
};



// Floor
plane {
  y, 0
  translate -0.6 * y
  texture {
    Floor_T
    rotate -30 * y
  }
}


// Mirror
intersection {
  plane {
    y, 0.05
    texture { Mirror_T }
  }
  cylinder {
    <0, 0, 0>,
    <0, 1, 0>,
    2
  }
  translate -.6 * y
}


// Cube
object {
  rubik_cube_to_object (
    rubik_cube_mix(
      rubik_cube_create_cube(<3, 3, 3>, rubik_cube_colors_classic), 81, seed(810)
    )
  )

  scale .5
  translate .6 * y
  finish {
    ambient 1
    diffuse 1
  }
  rotate 30 * y
}
