#include "../doc-scene.inc"
#include "../../rubik-cube.inc"

rubik_cube_to_object(
  rubik_cube_rotate_layers(
    rubik_cube_create_cube(<3, 3, 3>, rubik_cube_colors_classic),
    array[2] {<-90, 0, 0, 1>, <0, -30, 0, 2>}
  )
)
