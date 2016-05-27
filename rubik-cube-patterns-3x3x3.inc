#include "rubik-cube-notation.inc"


#declare rubik_cube_patterns_3x3x3_checkerboard_exchanged = array[3] {
  M2, E2, S2
};


#declare rubik_cube_patterns_3x3x3_checkerboard_twisted = array[16] {
  F, B2, -R, D2, B, R, U, -D, R, -L, -D, -F, R2, D, F2, -B
};


#declare rubik_cube_patterns_3x3x3_superflip = array[20] {
  U, R2, F, B, R, B2, R, U2, L, B2, R, -U, -D, R2, F, -R, L, B2, U2, F2
};


#declare rubik_cube_patterns_3x3x3_tablecloth = array[19] {
  R, L, U2, -F, U2, D2, R2, L2, -F, D2, F2, D, R2, L2, F2, B2, D, B2, L2
};
