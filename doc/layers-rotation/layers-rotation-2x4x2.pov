#include "../doc-scene.inc"
#include "../../rubik-cube.inc"

rubik_cube_to_object(
  rubik_cube_rotate_layers(
    rubik_cube_create_cube(<2, 4, 2>, rubik_cube_colors_classic),
    array[1] {<0, 0, 90, 0>}
  )
)
