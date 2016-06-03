#include "rubik-cube-notation.inc"


#declare rubik_cube_patterns_3x3x3_anaconda = array[14] {
  L, U, -B, -U, R, -L, B, -R, F, -B, D, R, -D, -F
};


#declare rubik_cube_patterns_3x3x3_black_mamba = array[14] {
  R, D, L, -F, R, -L, D, -R, U, -D, B, -U, -R, -D
};


#declare rubik_cube_patterns_3x3x3_center_edge_corner = array[20] {
  -U, R2, L2, F2, B2, -U, R, L, F, -B, U, F2, D2, R2, L2, F2, U2, F2, -U, F2
};


#declare rubik_cube_patterns_3x3x3_checkerboard_exchanged = array[3] {
  M2, E2, S2
};


#declare rubik_cube_patterns_3x3x3_checkerboard_with_faces = array[8] {
  U2, F2, U2, F2, B2, U2, F2, D2
};


#declare rubik_cube_patterns_3x3x3_checkerboard_twisted = array[16] {
  F, B2, -R, D2, B, R, U, -D, R, -L, -D, -F, R2, D, F2, -B
};


#declare rubik_cube_patterns_3x3x3_checkerboard_with_zigzag = array[11] {
  R2, L2, F2, B2, U, F2, B2, U2, F2, B2, U
};


#declare rubik_cube_patterns_3x3x3_cross = array[11] {
  U, F, -B, L2, U2, L2, -F, B, U2, L2, U
};


#declare rubik_cube_patterns_3x3x3_cross_twisted = array[16] {
  R2, -L, D, F2, -R, -D, -R, L, -U, D, R, D, B2, -R, U, D2
};


#declare rubik_cube_patterns_3x3x3_cube_in_cube = array[15] {
  F, L, F, -U, R, U, F2, L2, -U, -L, B, -D, -B, L2, U
};


#declare rubik_cube_patterns_3x3x3_cube_in_cube_in_cube = array[18] {
  -U, -L, -U, -F, R2, -B, R, F, U, B2, U, -B, L, -U, F, U, R, -F
};


#declare rubik_cube_patterns_3x3x3_green_mamba = array[13] {
  R, D, R, F, -R, -F, B, D, -R, -U, -B, U, D2
};


#declare rubik_cube_patterns_3x3x3_opposite_corners = array[12] {
  R, L, U2, F2, D2, F2, R, L, F2, D2, B2, D2
};


#declare rubik_cube_patterns_3x3x3_python = array[14] {
  F2, -R, -B, U, -R, L, -F, L, -F, B, -D, R, B, L2
};


#declare rubik_cube_patterns_3x3x3_speedsolving_com = array[12] {
  // -R, -L, U2, F2, D2, F2, R, L, B2, U2, B2, U2
  R, L, U2, F2, D2, F2, -R, -L, B2, U2, B2, U2
};


#declare rubik_cube_patterns_3x3x3_spiral = array[16] {
  -L, -B, D, U, R, -U, -R, D2, R2, D, L, -D, -L, -R, F, U
};


#declare rubik_cube_patterns_3x3x3_spots_4 = array[8] {
  F2, B2, U, -D, R2, L2, U, -D
};


#declare rubik_cube_patterns_3x3x3_spots_6 = array[4] {
  E, S, -E, -S
};


#declare rubik_cube_patterns_3x3x3_superflip = array[20] {
  U, R2, F, B, R, B2, R, U2, L, B2, R, -U, -D, R2, F, -R, L, B2, U2, F2
};


#declare rubik_cube_patterns_3x3x3_tablecloth = array[19] {
  R, L, U2, -F, U2, D2, R2, L2, -F, D2, F2, D, R2, L2, F2, B2, D, B2, L2
};


#declare rubik_cube_patterns_3x3x3_tetris = array[8] {
  L, R, F, B, -U, -D, -L, -R
};


#declare rubik_cube_patterns_3x3x3_twister = array[14] {
  F, -R, U, L, -F, -L, F, -U, R, U, -L, -U, L, -F
};


#declare rubik_cube_patterns_3x3x3_vertical_stripes = array[17] {
  F, U, F, R, L2, B, -D, R, D2, L, -D, B, R2, L, F, U, F
};


#declare rubik_cube_patterns_3x3x3_wire = array[18] {
  R, L, F, B, R, L, F, B, R, L, F, B, R2, B2, L2, R2, B2, L2
};
