// Generates a piece of cube with stickers.
//
// gen_param - array of six textures to be applied for the cube
//   stickers. Textures are ordered in the following way: right face
//   (0); top face (1); back face (2); left face (3); bottom face (4);
//   front face (5).
// Note. Interiors are just colored in black.

union {
  // Piece.
  #local piece_edge_radius = 0.06;

  object {
    Round_Box(<-0.5, -0.5, -0.5>, <0.5, 0.5, 0.5>, piece_edge_radius, 1)
    pigment { Black }
  }

  // Stickers.
  #local thickness_ = 0.01;           // Thickness of the sticker. (outer part)
  #local bt = thickness_ + 0.5;       // Thickness of the block used for sticker creation.
  #local s = 0.5 - piece_edge_radius; // Sticker size (a half of it, actually).
  #local ser = 0.05;                  // Sticker edge radius.

  #if (pos.x = dim.x - 1) object { Round_Box(< bt,  -s,  -s>, <0, s, s>, ser, 1) texture { gen_param[0] }} #end
  #if (pos.y = dim.y - 1) object { Round_Box(< -s,  bt,  -s>, <s, 0, s>, ser, 1) texture { gen_param[1] }} #end
  #if (pos.z = dim.z - 1) object { Round_Box(< -s,  -s,  bt>, <s, s, 0>, ser, 1) texture { gen_param[2] }} #end

  #if (pos.x = 0)         object { Round_Box(<-bt,  -s,  -s>, <0, s, s>, ser, 1) texture { gen_param[3] }} #end
  #if (pos.y = 0)         object { Round_Box(< -s, -bt,  -s>, <s, 0, s>, ser, 1) texture { gen_param[4] }} #end
  #if (pos.z = 0)         object { Round_Box(< -s,  -s, -bt>, <s, s, 0>, ser, 1) texture { gen_param[5] }} #end

  translate 0.5
}
