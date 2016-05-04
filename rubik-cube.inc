#include "colors.inc"
#include "shapes.inc"


// Classic colors used for Rubik's Cubes. White is opposite to yellow,
// red is opposite to orange and blue is opposite to green. Red, white
// and blue colors are clockwise arranged.
#declare rubik_cube_colors_classic = array[6] {Blue, Red, Yellow, Green, Orange, White};


// Generates a piece of cube with defined colors.
//
// colors - array of six colors to be applied for the piece. Colors
//   are ordered in the same manner as for rubik_cube_create_cube()
//   macro.
//
// Returns the generated piece.
#macro rubik_cube_create_part(colors)
  object {
    Round_Box(<-0.5, -0.5, -0.5>, <0.5, 0.5, 0.5>, 0.1, 1)
    pigment {
      cubic colors[0], colors[1], colors[2], colors[3], colors[4], colors[5]
    }
    translate <0.5, 0.5, 0.5>
  }
#end


// Generates all pieces for a cube.
//
// dim_x, dim_y, dim_z - dimensions of the cube.
// colors - array of six colors to be applied for the piece. Colors
//   are ordered in the same manner as for rubik_cube_create_cube()
//   macro.
//
// Returns an array of the generated cube pieces. The pieces are
// placed in the array layer by layer from the front layer to the back
// one. The pieces in a layer are placed line by line from bottom to
// top. The pieces in a line are placed from left to right.
#macro rubik_cube_get_all_parts(dim_x, dim_y, dim_z, colors)
  #local parts = array[dim_x * dim_y * dim_z];
  #for (pos_x, 0, dim_x - 1)
    #for (pos_y, 0, dim_y - 1)
      #for (pos_z, 0, dim_z - 1)
	#local part_colors = colors;
	#if (pos_x != 0)         #local part_colors[3] = Black; #end
	#if (pos_x != dim_x - 1) #local part_colors[0] = Black; #end
	#if (pos_y != 0)         #local part_colors[4] = Black; #end
	#if (pos_y != dim_y - 1) #local part_colors[1] = Black; #end
	#if (pos_z != 0)         #local part_colors[5] = Black; #end
	#if (pos_z != dim_z - 1) #local part_colors[2] = Black; #end

	#local parts[pos_x + pos_y * dim_x + pos_z * dim_x * dim_y] =
	object {
	  rubik_cube_create_part(part_colors)
	  transform {
	    translate <pos_x, pos_y, pos_z> - <dim_x / 2, dim_y / 2, dim_z / 2>
	  }
	}
      #end
    #end
  #end
  parts
#end


// Rotates a layer which is perpendicular to the X axis around it.
//
// dim_x, dim_y, dim_z - dimensions of the cube.
// parts - pieces of the cube.
// layer - the layer to be rotated (position of layer counting from
//   the left to the right).
// a - rotation angle.
//
// Returns pieces of the cube with the rotated layer.
#macro rubik_cube_rotate_by_x(dim_x, dim_y, dim_z, parts, layer, a)
  #local new_parts = parts;

  #for (pos_y, 0, dim_y - 1)
    #for (pos_z, 0, dim_z - 1)
      #local new_pos_y = dim_y - pos_z - 1;
      #local new_pos_z = pos_y;
      #local new_parts[layer + new_pos_y * dim_x + new_pos_z * dim_x * dim_y] =
      object {
	parts[layer + pos_y * dim_x + pos_z * dim_x * dim_y]
	transform {
	  rotate a * x
	}
      }
    #end
  #end

  new_parts
#end


// Rotates a layer which is perpendicular to the Y axis around it.
//
// dim_x, dim_y, dim_z - dimensions of the cube.
// parts - pieces of the cube.
// layer - the layer to be rotated (position of layer counting from
//   the left to the right).
// a - rotation angle.
//
// Returns pieces of the cube with the rotated layer.
#macro rubik_cube_rotate_by_y(dim_x, dim_y, dim_z, parts, layer, a)
  #local new_parts = parts;

  #for (pos_x, 0, dim_x - 1)
    #for (pos_z, 0, dim_z - 1)
      #local new_pos_x = dim_x - pos_z - 1;
      #local new_pos_z = pos_x;
      #local new_parts[new_pos_x + layer * dim_x + new_pos_z * dim_x * dim_y] =
      object {
	parts[pos_x + layer * dim_x + pos_z * dim_x * dim_y]
	transform {
	  rotate a * y
	}
      }
    #end
  #end

  new_parts
#end


// Rotates a layer which is perpendicular to the Z axis around it.
//
// dim_x, dim_y, dim_z - dimensions of the cube.
// parts - pieces of the cube.
// layer - the layer to be rotated (position of layer counting from
//   the left to the right).
// a - rotation angle.
//
// Returns pieces of the cube with the rotated layer.
#macro rubik_cube_rotate_by_z(dim_x, dim_y, dim_z, parts, layer, a)
  #local new_parts = parts;

  #for (pos_x, 0, dim_x - 1)
    #for (pos_y, 0, dim_y - 1)
      #local new_pos_x = dim_x - pos_y - 1;
      #local new_pos_y = pos_x;
      #local new_parts[new_pos_x + new_pos_y * dim_x + layer * dim_x * dim_y] =
      object {
	parts[pos_x + pos_y * dim_x + layer * dim_x * dim_y]
	transform {
	  rotate a * z
	}
      }
    #end
  #end

  new_parts
#end


// Rotate a layer of the provided cube according to the provided
// movement vector.
//
// dim_x, dim_y, dim_z - dimensions of the cube.
// parts - pieces of the cube.
// movement - movement as it described in rubik_cube_create_cube()
//   macro.
//
// Returns pieces of the cube with the rotated layer.
#macro rubik_cube_move_parts(dim_x, dim_y, dim_z, parts, movement)
  // todo check that movement is valid.

  #if (movement.x != 0)
    #switch (movement.x)
      #case (-90)
	#local parts = rubik_cube_rotate_by_x(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (180) #case (-180)
	#local parts = rubik_cube_rotate_by_x(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (90)
	#local parts = rubik_cube_rotate_by_x(dim_x, dim_y, dim_z, parts, movement.t, 90);
    #end
  #elseif (movement.y != 0)
    #switch (movement.y)
      #case (-90)
	#local parts = rubik_cube_rotate_by_y(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (180) #case (-180)
	#local parts = rubik_cube_rotate_by_y(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (90)
	#local parts = rubik_cube_rotate_by_y(dim_x, dim_y, dim_z, parts, movement.t, 90);
    #end
  #elseif (movement.z != 0)
    #switch (movement.z)
      #case (-90)
	#local parts = rubik_cube_rotate_by_z(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (180) #case (-180)
	#local parts = rubik_cube_rotate_by_z(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (90)
	#local parts = rubik_cube_rotate_by_z(dim_x, dim_y, dim_z, parts, movement.t, 90);
    #end
  #end

  parts
#end


// Generates a cube with desired dimensions, colors and rotated layers.
//
// dim_x, dim_y, dim_z - dimensions of the cube.
// colors - array of six colors to be applied for the cube. Colors are
//   ordered in the following way: right face (0); top face (1); back
//   face (2); left face (3); bottom face (4); front face (5).
//   Note. Interior faces are colored in black.
// movement - array of movements to be applied to the generated
//   cube. Each movement is a 4D vector. First three components are
//   rotation angles for layers perpendicular to corresponding axis,
//   the third component indicates the layer to be rotated position
//   (from left to right, from bottom to top or from front to back).
//   Valid values for angles are: -180, -90, 0, 90, 180.
//   Attention! It is invalid to use more than one non-zero angle in
//   the movement vector.
//
// Returns the generated cube in form of an object with center in
// origin. Each piece has a form of a cube of size of 1 unit, i.e. a
// cube 3x3x3 will have size of 3 units.
#macro rubik_cube_create_cube(dim_x, dim_y, dim_z, colors, movements)
  #local parts = rubik_cube_get_all_parts(dim_x, dim_y, dim_z, colors)

  #for (movementIx, 0, dimension_size(movements, 1) - 1)
    #local parts = rubik_cube_move_parts(dim_x, dim_y, dim_z, parts, movements[movementIx]);
  #end

  union {
    #for (item, 0, dim_x * dim_y * dim_z - 1)
      object { parts[item] }
    #end
  }
#end
