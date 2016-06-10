#include "../doc-scene.inc"
#include "rubik-cube.inc"

camera {
  location <0, 3, -7>
  look_at  <0, 0,  0>
}

#local cube1 = rubik_cube_create_cube(<3, 3, 3>, rubik_cube_colors_classic);

#local cube2 = rubik_cube_create_cube(<3, 3, 3>, rubik_cube_colors_classic);
#local cube2 = rubik_cube_rotate_layers(cube2, array[1] {<-90, 0, 0, 1>});


object {
  rubik_cube_to_object(
    rubik_cube_animate(
      cube1,
      array[1] {<-90, 0, 0, 1>},
      0,
      0.5
    )
  )
  translate -2 * x
}


object {
  rubik_cube_to_object(
    rubik_cube_animate(
      cube2,
      array[1] {<0, -90, 0, 2>},
      0.5,
      1
    )
  )
  translate 2 * x
}
