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
#macro rubik_cube_create_piece(colors)
  object {
    Round_Box(<-0.5, -0.5, -0.5>, <0.5, 0.5, 0.5>, 0.1, 1)
    pigment {
      cubic colors[0], colors[1], colors[2], colors[3], colors[4], colors[5]
    }
    translate <0.5, 0.5, 0.5>
  }
#end


// Returns a new cube (3D array of the generated cube pieces).
// Pieces of the cube are smaller cubes of 1 unit size, so a cube
// 3x3x3 will have size of 3 units.
//
// dim - dimensions of the cube (3D vector).
// colors - array of six colors to be applied for the cube. Colors are
//   ordered in the following way: right face (0); top face (1); back
//   face (2); left face (3); bottom face (4); front face (5).
//   Note. Interior faces are colored in black.
#macro rubik_cube_create_cube(dim, colors)
  #local rcube = array[dim.x][dim.y][dim.z];
  #for (pos_x, 0, dim.x - 1)
    #for (pos_y, 0, dim.y - 1)
      #for (pos_z, 0, dim.z - 1)
	#local piece_colors = colors;
	#if (pos_x != 0)         #local piece_colors[3] = Black; #end
	#if (pos_x != dim.x - 1) #local piece_colors[0] = Black; #end
	#if (pos_y != 0)         #local piece_colors[4] = Black; #end
	#if (pos_y != dim.y - 1) #local piece_colors[1] = Black; #end
	#if (pos_z != 0)         #local piece_colors[5] = Black; #end
	#if (pos_z != dim.z - 1) #local piece_colors[2] = Black; #end

	#local rcube[pos_x][pos_y][pos_z] =
	object {
	  rubik_cube_create_piece(piece_colors)
	  transform {
	    translate <pos_x, pos_y, pos_z> - <dim.x / 2, dim.y / 2, dim.z / 2>
	  }
	}
      #end
    #end
  #end

  rcube
#end


// Calculates position of a piece after the layer rotation.
//
// pos_x, pos_y, pos_z - position of the piece to be rotate.
// dim - dimensions of the cube (3D vector).
// a - rotation angle.
//   Valid values are:
//     -180, -90, 90, 180 - for a square layer, and
//     -180, 180          - for a non-square layer.
// rot_axis - an axis, the layer to be rotated around.
//   Valid rotation axis are: x, y, z.
//
// Returns a 3D vector which contains the calculated position.
#macro rubik_cube_calc_rotated_position(pos_x, pos_y, pos_z, dim, a, rot_axis)
  // The calculation method doesn't depend on rotation axis. To unify
  // calculations, a new 2D position vector is introduced.
  #if (VEq(rot_axis, x))
    #local pos = <pos_y, pos_z>; // y to z movement is ccw if look along x.
    #local layer_dim = <dim.y, dim.z>;
  #elseif (VEq(rot_axis, y))
    #local pos = <pos_z, pos_x>; // z to x movement is ccw if look along y.
    #local layer_dim = <dim.z, dim.x>;
  #elseif (VEq(rot_axis, z))
    #local pos = <pos_x, pos_y>; // x to y movement is ccw if look along z.
    #local layer_dim = <dim.x, dim.y>;
  #else
    #error concat("Wrong rotation axis: <", vstr(3, rot_axis, ", ", 0, 3), ">\n")
  #end

  #if (((a = 90) | (a = -90)) & (layer_dim.u != layer_dim.v))
    #error concat("It is impossible to rotate a non-square layer on -90 or 90 degrees.\n",
                  "Layer dimensions: <", vstr(2, layer_dim, ", ", 0, 0), ">.\n",
                  "Rotation axis: <", vstr(3, rot_axis, ", ", 0, 0), ">.\n")
  #end

  #switch (a)
    #case (-90)
      #local new_pos = <pos.v, layer_dim.u - pos.u - 1>;
    #break
    #case (90)
      #local new_pos = <layer_dim.v - pos.v - 1, pos.u>;
    #break
    #case (-180) #case (180)
      #local new_pos = <layer_dim.u - pos.u - 1, layer_dim.v - pos.v - 1>;
    #break
    #else
      #error concat("Wrong angle: ", str(a, 0, 3), ".\n")
  #end

  // Return to initial 3D position vector.
  #if (VEq(rot_axis, x))
    #local new_pos = <pos_x, new_pos.u, new_pos.v>;
  #elseif (VEq(rot_axis, y))
    #local new_pos = <new_pos.v, pos_y, new_pos.u>;
  #elseif (VEq(rot_axis, z))
    #local new_pos = <new_pos.u, new_pos.v, pos_z>;
  #end

  new_pos
#end


// Rotates a layer of the cube according to the movement vector.
//
// rcube - cube, a layer to be rotated of. (3D array)
// movement - array of movements to be applied to the cube. Each
//   movement is a 4D vector. First three components are rotation
//   angles for layers perpendicular to corresponding axis, the third
//   component indicates the layer to be rotated position (from left
//   to right, from bottom to top or from front to back).
//   Attention! It is invalid to use more than one non-zero angle in
//   the movement vector.
// is_latest - shows if the movement is the latest one and no more
//   movements will be applied to the cube. There is no restrictions
//   on the rotation angle of the latest movement. Whereas valid
//   values for a non-latest movement are:
//     -180, -90, 90, 180 - for a square layer, and
//     -180, 180          - for a non-square layer.
//
// Returns cube with the rotated layer.
#macro rubik_cube_rotate_layer(rcube, movement, is_latest)
  #if (movement.x != 0)
    #local rot_axis = x;
    #local a = movement.x;
  #elseif (movement.y != 0)
    #local rot_axis = y;
    #local a = movement.y;
  #elseif (movement.z != 0)
    #local rot_axis = z;
    #local a = movement.z;
  #end

  #local new_cube = rcube;
  #local dim = <dimension_size(rcube, 1), dimension_size(rcube, 2), dimension_size(rcube, 3)>;
  #for (pos_x, 0, dim.x - 1)
    #for (pos_y, 0, dim.y - 1)
      #for (pos_z, 0, dim.z - 1)
        // Only pieces belonging to the layer movement.t must be rotated.
        #if (!((VEq(rot_axis, x) & (pos_x != movement.t)) |
               (VEq(rot_axis, y) & (pos_y != movement.t)) |
               (VEq(rot_axis, z) & (pos_z != movement.t))))

          #if (is_latest = 0)
            #local new_pos = rubik_cube_calc_rotated_position(pos_x, pos_y, pos_z, dim, a, rot_axis);
          #else
            #local new_pos = <pos_x, pos_y, pos_z>;
          #end

          #local new_cube[new_pos.x][new_pos.y][new_pos.z] =
            object {
              rcube[pos_x][pos_y][pos_z]
              transform {
                rotate a * rot_axis
              }
            };
        #end
      #end
    #end
  #end

  new_cube
#end


// Returns a cube with rotated layers.
//
// rcube - cube, layers to be rotated of. (3D array)
// movements - array of movements. Description of a movement can be
//   found in rubik_cube_rotate_layer() macro.
#macro rubik_cube_rotate_layers(rcube, movements)
  #local movementsLen = dimension_size(movements, 1);
  #for (movementIx, 0, movementsLen - 1)
    #local rcube = rubik_cube_rotate_layer(rcube, movements[movementIx], (movementIx = movementsLen - 1 ? 1 : 0));
  #end
  rcube
#end


// Returns a random angle to rotate a layer with respect of this layer
// dimensions. (non-square layers can't be rotated on 90 degrees)
//
// dim - dimensions of the rotated layer (2D vector).
// rand_stream - pseudo-random stream as it returns by the seed()
//   function.
#macro rubik_cube_generate_random_angle(dim, rand_stream)
  #if (dim.u = dim.v)
    #local a = rand(rand_stream);
    #if (a < 1 / 3)
      -90
    #elseif (a < 2 / 3)
      90
    #else
      180
    #end
  #else
    180
  #end
#end


// Returns a random movement.
//
// dim - dimensions of the cube (3D vector).
// rand_stream - pseudo-random stream as it returns by the seed()
//   function.
#macro rubik_cube_generate_random_movement(dim, rand_stream)
  #local axis = rand(rand_stream);
  #if (axis < 1 / 3)
    #local movement = <rubik_cube_generate_random_angle(<dim.y, dim.z>, rand_stream), 0, 0, floor((dim.x - 1) * rand(rand_stream))>;
  #elseif (axis < 2 / 3)
    #local movement = <0, rubik_cube_generate_random_angle(<dim.x, dim.z>, rand_stream), 0, floor((dim.y - 1) * rand(rand_stream))>;
  #else
    #local movement = <0, 0, rubik_cube_generate_random_angle(<dim.x, dim.y>, rand_stream), floor((dim.z - 1) * rand(rand_stream))>;
  #end
  movement
#end


// Returns an array of random movements.
//
// dim - dimensions of the cube (3D vector).
// length - number of elements in the generated array.
// rand_stream - pseudo-random stream as it returns by the seed()
//   function.
#macro rubik_cube_generate_random_movements(dim, length, rand_stream)
  #local movements = array[length];
  #for (movementIx, 0, length - 1)
    #local movements[movementIx] = rubik_cube_generate_random_movement(dim, rand_stream);
  #end
  movements
#end


// Returns a mixed cube.
//
// rcube - cube to be mixed. (3D array)
// number_of_rotations - number of random layers rotations.
// rand_stream - pseudo-random stream as it returns by the seed()
//   function.
#macro rubik_cube_mix(rcube, number_of_rotations, rand_stream)
  #local dim = <dimension_size(rcube, 1), dimension_size(rcube, 2), dimension_size(rcube, 3)>;
  rubik_cube_rotate_layers(rcube, rubik_cube_generate_random_movements(dim, number_of_rotations, rand_stream))
#end


// Returns the cube transformed to an object from its representation
// as a 3D array.
//
// rcube - cube to be transformed. (3D array)
#macro rubik_cube_to_object(rcube)
  #local dim = <dimension_size(rcube, 1), dimension_size(rcube, 2), dimension_size(rcube, 3)>;
  union {
    #for (pos_x, 0, dim.x - 1)
      #for (pos_y, 0, dim.y - 1)
        #for (pos_z, 0, dim.z - 1)
          object { rcube[pos_x][pos_y][pos_z] }
        #end
      #end
    #end
  }
#end
