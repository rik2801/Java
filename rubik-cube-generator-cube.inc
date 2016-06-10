// Generates a piece of cube with defined colors. Each piece is a cube
// of 1 unit size.
//
// gen_param - array of six colors to be applied for the cube. Colors
//   are ordered in the following way: right face (0); top face (1);
//   back face (2); left face (3); bottom face (4); front face (5).
//   Note. Interior faces are colored in black.

object {
  #local piece_colors = gen_param;

  #if (pos.x != 0)         #local piece_colors[3] = Black; #end
  #if (pos.x != dim.x - 1) #local piece_colors[0] = Black; #end
  #if (pos.y != 0)         #local piece_colors[4] = Black; #end
  #if (pos.y != dim.y - 1) #local piece_colors[1] = Black; #end
  #if (pos.z != 0)         #local piece_colors[5] = Black; #end
  #if (pos.z != dim.z - 1) #local piece_colors[2] = Black; #end

  Round_Box(<-0.5, -0.5, -0.5>, <0.5, 0.5, 0.5>, 0.1, 1)
  pigment {
    cubic piece_colors[0], piece_colors[1], piece_colors[2], piece_colors[3], piece_colors[4], piece_colors[5]
  }
  translate 0.5
}
