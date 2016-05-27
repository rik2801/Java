#include "doc/doc-scene.inc"
#include "rubik-cube.inc"
#include "rubik-cube-patterns-3x3x3.inc"

rubik_cube_to_object(
  rubik_cube_rotate_layers(
    rubik_cube_create_cube(<3, 3, 3>, rubik_cube_colors_classic),
    rubik_cube_patterns_3x3x3_tablecloth
  )
)
