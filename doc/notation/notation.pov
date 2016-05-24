#include "../doc-scene.inc"
#include "../../rubik-cube.inc"
#include "../../rubik-cube-notation.inc"

#local superflip = array[20] {
  U, R2, F, B, R, B2, R, U2, L, B2, R, -U, -D, R2, F, -R, L, B2, U2, F2
};

rubik_cube_to_object(
  rubik_cube_rotate_layers(
    rubik_cube_create_cube(<3, 3, 3>, rubik_cube_colors_classic),
    superflip
  )
)
