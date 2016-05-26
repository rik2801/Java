#include "rubik-cube-notation.inc"

// Every piece is where it's supposed to be but the edges are oriented
// wrong. It is need the highest amount of steps (20) to solve this
// state.
#declare rubik_cube_patterns_3x3x3_superflip = array[20] {
  U, R2, F, B, R, B2, R, U2, L, B2, R, -U, -D, R2, F, -R, L, B2, U2, F2
};
