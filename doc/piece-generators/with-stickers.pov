#include "../doc-scene.inc"
#include "rubik-cube.inc"

rubik_cube_to_object(
  rubik_cube_generate_cube(
    <3, 3, 3>,
    "rubik-cube-generator-with-stickers.inc",
    array[6] {
      pigment { Green },
      pigment { Red },
      pigment { Yellow },
      pigment { Blue },
      pigment { Orange},
      pigment { White }
    }
  )
)
