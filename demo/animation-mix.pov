#include "demo.inc"
#include "../rubik-cube.inc"

rubik_cube_to_object(
  rubik_cube_animate(
    rubik_cube_create_cube(<3, 3, 3>, rubik_cube_colors_classic),
    rubik_cube_generate_random_movements(<3, 3, 3>, 5, seed(1)),
    0, 1)
)
