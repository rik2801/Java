#include "../doc-scene.inc"
#include "rubik-cube.inc"

#local rcube = rubik_cube_create_cube(<3, 3, 3>, rubik_cube_colors_classic);

#local fwd_movements  = array[4] {<90, 0, 0, 1>, <0, 0, 90, 1>, <-90, 0, 0, 1>, <0, 0, -90, 1>};
#local back_movements = rubik_cube_reflect_movements(fwd_movements);

rubik_cube_to_object(
  rubik_cube_animate(
    rcube,
    rubik_cube_merge_movements(fwd_movements, back_movements),
    0, 1
  )
)
