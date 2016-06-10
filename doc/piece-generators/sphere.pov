#include "../doc-scene.inc"
#include "rubik-cube.inc"

rubik_cube_to_object(
  rubik_cube_generate_cube(
    <3, 3, 3>,
    "sphere.inc",
    array[2] {Red, White}
  )
)
