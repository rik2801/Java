#include "colors.inc"
#include "shapes.inc"


// Classic colors used for Rubik's Cubes. White is opposite to yellow,
// red is opposite to orange and blue is opposite to green. Red, white
// and blue colors are clockwise arranged.
#declare rubik_cube_colors_classic = array[6] {Green, Red, Yellow, Blue, Orange, White};


// Generates a piece of cube.
//
// dim - dimensions of the cube (3D vector).
// pos - piece position (3D vector), where the coordinates are numbers
//   from 0 to corresponding dimension minus one.
// gen_name - name of the file that contains the generator
//   implementation.
// gen_param - a parameter which is passed to the generator. If
//   several parameters must be passed, they can be combined in an
//   array.
//
// Normally, a generator returns a piece which is embedded into a cube
// with coordinates <0, 0, 0>, <1, 1, 1>.
//
// Returns the generated piece.
#macro rubik_cube_generate_piece(dim, pos, gen_name, gen_param)
  #include gen_name
#end


// Returns a new cube (3D array of the generated cube pieces).
// Pieces of the cube are created by the provided generator.
//
// dim - dimensions of the cube (3D vector).
// gen_name - name of the file that contains the generator
//   implementation.
// gen_param - parameter which is passed to the generator.
#macro rubik_cube_generate_cube(dim, gen_name, gen_param)
  #local rcube = array[dim.x][dim.y][dim.z];
  #for (pos_x, 0, dim.x - 1)
    #for (pos_y, 0, dim.y - 1)
      #for (pos_z, 0, dim.z - 1)
        #local rcube[pos_x][pos_y][pos_z] =
        object {
          rubik_cube_generate_piece(dim, <pos_x, pos_y, pos_z>, gen_name, gen_param)
          transform {
            translate <pos_x, pos_y, pos_z> - <dim.x / 2, dim.y / 2, dim.z / 2>
          }
        }
      #end
    #end
  #end

  rcube
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
  rubik_cube_generate_cube(dim, "rubik-cube-generator-cube.inc", colors)
#end


// Returns dimensions of the layers perpendicular to the provided
// axis.
//
// dim - cube dimensions.
// axis - dimensions of the layers perpendicular to this axis are
//   returned.
#macro rubik_cube_get_layer_dimensions(dim, axis)
  #if (VEq(rot_axis, x))
    #local layer_dim = <dim.y, dim.z>;
  #elseif (VEq(rot_axis, y))
    #local layer_dim = <dim.z, dim.x>;
  #elseif (VEq(rot_axis, z))
    #local layer_dim = <dim.x, dim.y>;
  #else
    #error concat("Wrong rotation axis: <", vstr(3, rot_axis, ", ", 0, 3), ">\n")
  #end
  layer_dim
#end


// Calculates position of a piece after the layer rotation.
//
// pos_x, pos_y, pos_z - position of the piece to be rotate.
// dim - dimensions of the cube (3D vector).
// a - rotation angle.
//   Valid values are:
//     -180, -90, 0, 90, 180 - for a square layer, and
//     -180, 0, 180          - for a non-square layer.
// rot_axis - an axis, the layer to be rotated around.
//   Valid rotation axis are: x, y, z.
//
// Returns a 3D vector which contains the calculated position.
#macro rubik_cube_calc_rotated_position(pos_x, pos_y, pos_z, dim, a, rot_axis)
  #local layer_dim = rubik_cube_get_layer_dimensions(dim, rot_axis);

  // The calculation method doesn't depend on rotation axis. To unify
  // calculations, a new 2D position vector is introduced.
  #if (VEq(rot_axis, x))
    #local pos = <pos_y, pos_z>; // y to z movement is ccw if look along x.
  #elseif (VEq(rot_axis, y))
    #local pos = <pos_z, pos_x>; // z to x movement is ccw if look along y.
  #elseif (VEq(rot_axis, z))
    #local pos = <pos_x, pos_y>; // x to y movement is ccw if look along z.
  #else
    #error concat("Wrong rotation axis: <", vstr(3, rot_axis, ", ", 0, 3), ">\n")
  #end

  #if (((a = 90) | (a = -90)) & (layer_dim.u != layer_dim.v))
    #error concat("It is impossible to rotate a non-square layer on -90 or 90 degrees.\n",
                  "Layer dimensions: <", vstr(2, layer_dim, ", ", 0, 0), ">.\n",
                  "Rotation axis: <", vstr(3, rot_axis, ", ", 0, 0), ">.\n")
  #end

  #switch (a)
    #case (0)
      #local new_pos = pos;
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


// Checks if a rotation is a valid one:
//   -180, -90, 0, 90, 180 - for a square layer, and
//   -180, 0, 180          - for a non square layer.
//
// dim - dimensions of the cube. (3D vector)
// rot_axis - an axis, the layer to be rotated around.
//   Valid rotation axis are: x, y, z.
// a - rotation angle to be examined.
//
// Returns:
//   0 - rotation is invalid.
//   1 - rotation is valid.
#macro rubik_cube_is_rotation_valid(dim, rot_axis, a)
  #local result = 0;

  // If angle is zero then rotation axis could be equal zero too. It
  // is impossimle to determine layer dimensions for such axis.
  #if (a != 0)
    #local layer_dim = rubik_cube_get_layer_dimensions(dim, rot_axis);

    #if (layer_dim.u = layer_dim.v)
      #local min_angle = 90;
    #else
      #local min_angle = 180;
    #end

    #if (mod(a, min_angle) = 0)
      #local result = 1;
    #end
  #else
    #local result = 0;
  #end

  result
#end


// Rotates a layer of the cube according to the movement vector.
//
// rcube - cube, a layer to be rotated of. (3D array)
// movement - a movement to be applied to the cube. Each movement is a
//   4D vector. First three components are rotation angles for layers
//   perpendicular to corresponding axis, the third component
//   indicates the layer to be rotated position (from left to right,
//   from bottom to top or from front to back).
//   Attention! It is invalid to use more than one non-zero angle in
//   the movement vector.
// is_latest - shows if the movement is the latest one and no more
//   movements will be applied to the cube. There is no restrictions
//   on the rotation angle of the latest movement. Whereas valid
//   values for a non-latest movement are:
//     -180, -90, 0, 90, 180 - for a square layer, and
//     -180, 0, 180          - for a non-square layer.
//
// Warning! If is_latest was set to true and a restricted rotation
// angle was used in the previsous macro execution, another execution
// will break the cube.
//
// Returns cube with the rotated layer.
#macro rubik_cube_rotate_layer(rcube, movement, is_latest)
  #local rot_axis = <0, 0, 0>;
  #local a = 0;

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
        #if (!((VEq(rot_axis, x) & (pos_x != abs(movement.t))) |
               (VEq(rot_axis, y) & (pos_y != abs(movement.t))) |
               (VEq(rot_axis, z) & (pos_z != abs(movement.t)))))

          #if ((is_latest = 0) |
               rubik_cube_is_rotation_valid(dim, rot_axis, a))
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
  #local a = rand(rand_stream);
  #if (dim.u = dim.v)
    #if (a < 0.25)
      -180
    #elseif (a < 0.5)
      -90
    #elseif (a < 0.75)
      90
    #else
      180
    #end
  #else
    #if (a < 0.5)
      -180
    #else
      180
    #end
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
    #local movement = <rubik_cube_generate_random_angle(<dim.y, dim.z>, rand_stream), 0, 0, floor((dim.x - 1) * rand(rand_stream) + 0.5)>;
  #elseif (axis < 2 / 3)
    #local movement = <0, rubik_cube_generate_random_angle(<dim.x, dim.z>, rand_stream), 0, floor((dim.y - 1) * rand(rand_stream) + 0.5)>;
  #else
    #local movement = <0, 0, rubik_cube_generate_random_angle(<dim.x, dim.y>, rand_stream), floor((dim.z - 1) * rand(rand_stream) + 0.5)>;
  #end
  movement
#end


// Checks if two movements rotates the same layer.
//
// movement1, movement2 - examined movements.
//
// Returns:
//   0 - different layers are rotated;
//   1 - same layer is rotated.
#macro rubik_cube_is_same_layer_rotated(movement1, movement2)
  #local result = 0;
  #if (abs(movement1.t) = abs(movement2.t))
    #local axis1 = <movement1.x, movement1.y, movement1.z>;
    #local axis2 = <movement2.x, movement2.y, movement2.z>;
    #local angle_between_axes = VAngleD(axis1, axis2);
    #if ((angle_between_axes = 0) | (angle_between_axes = 180))
      #local result = 1;
    #end
  #end
  result
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

    // Forbid two rotations of the same layer in a row.
    #if (movementIx > 0)
      #if (rubik_cube_is_same_layer_rotated(movements[movementIx - 1], movements[movementIx]))
        #local movementIx = movementIx - 1;
      #end
    #end
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


// Returns an array of movements opposite to the provided ones.
//
// movements - movements to be reflected.
#macro rubik_cube_reflect_movements(movements)
  #local number_of_movements = dimension_size(movements, 1);
  #local result = array[number_of_movements];
  #for (resultIx, 0, number_of_movements - 1)
    #local result[resultIx] = -movements[number_of_movements - 1 - resultIx];
  #end
  result
#end


// Returns a merged array of movements.
//
// m1, m2 - arrays to be merged.
#macro rubik_cube_merge_movements(m1, m2)
  #local result = array[dimension_size(m1, 1) + dimension_size(m2, 1)];
  #local resultIx = 0;
  #for (m1Ix, 0, dimension_size(m1, 1) - 1)
    #local result[resultIx] = m1[m1Ix];
    #local resultIx = resultIx + 1;
  #end
  #for (m2Ix, 0, dimension_size(m2, 1) - 1)
    #local result[resultIx] = m2[m2Ix];
    #local resultIx = resultIx + 1;
  #end
  result
#end


// Checks if a movement has a rotation on 180 degrees.
//
// movement - movement to be examined.
//
// Returns:
//   0 - movement has no 180 degrees rotation.
//   1 - movement has a  180 degrees rotation.
#macro rubik_cube_is_movement_180(movement)
  #local result = 0;
  #if (((movement.x = -180) | (movement.x = 180)) |
       ((movement.y = -180) | (movement.y = 180)) |
       ((movement.z = -180) | (movement.z = 180)))
    #local result = 1;
  #end
  result
#end


// Returns number of 90 degrees rotation frames within provided
// movements.
//
// To animate rotations with the same speed, each 180 degrees
// rotation is treated as two 90 degrees rotations.
//
// movements - array of movements to be examined.
#macro rubik_cube_get_number_of_90_frames(movements)
  #local result = dimension_size(movements, 1);
  #for (movementIx, 0, dimension_size(movements, 1) - 1)
    #if (rubik_cube_is_movement_180(movements[movementIx]))
      #local result = result + 1;
    #end
  #end
  result
#end


// Returns the index of a movement which corresponds to the provided
// 90 degrees rotation frame.
//
// movements - array of movements.
// frame - a 90 degrees rotation frame.
// pos_in_180_frame [out] - position of the provided 90 degrees
// rotation frame in a 180 degrees rotation frame:
//     0 - not a 180 frame;
//     1 - first half;
//     2 - second half.
#macro rubik_cube_find_movement(movements, frame, pos_in_180_frame)
  #local number_of_180_frames = 0;
  #declare pos_in_180_frame = 0;

  #for (movementIx, 0, frame)
    #if (rubik_cube_is_movement_180(movements[movementIx - number_of_180_frames]))
      // Modulo prevents increasing position to a value greater than 2
      // if there are several movements with 180 degrees rotations in
      // a row.
      #declare pos_in_180_frame = mod(pos_in_180_frame, 2) + 1;

      // A movement with 180 degrees rotation must be calculated only
      // once.
      #if (pos_in_180_frame = 1)
        #local number_of_180_frames = number_of_180_frames + 1;
      #end
    #else
      #declare pos_in_180_frame = 0;
    #end
  #end

  // If a 180 degrees rotation frame is just started then it should
  // not be considered in further calculations as there is no
  // difference between it and a 90 degrees rotation frame.
  #if (pos_in_180_frame = 1)
    #local number_of_180_frames = number_of_180_frames - 1;
  #end

  #local result = frame - number_of_180_frames;
  result
#end


// Animates a cube.
//
// rcube - cube to be animated. (3D array)
// movements - array of movements to be animated. Description of a
//   movement can be found in rubik_cube_rotate_layer() macro.
// from_clock - time when animation must be started.
// to_clock - time when animation must be stopped.
#macro rubik_cube_animate(rcube, movements, from_clock, to_clock)
  #if (to_clock < from_clock)
    #error concat("to_clock(", str(to_clock, 0, 5), ") can't be bigger then from_clock(", str(from_clock), ").")
  #end
  #if (clock <= from_clock)
    rcube
  #elseif (clock < to_clock)
    #local clocks_per_90_movement = (to_clock - from_clock) / rubik_cube_get_number_of_90_frames(movements);
    #local current_90_frame = floor((clock - from_clock) / clocks_per_90_movement);
    #local pos_in_180_frame = 0;
    #local current_movement = rubik_cube_find_movement(movements, current_90_frame, pos_in_180_frame);

    #local showed_movements = array[current_movement + 1];
    #for (movementIx, 0, current_movement)
      #local showed_movements[movementIx] = movements[movementIx];
    #end

    #local rot_phase = mod((clock - from_clock), clocks_per_90_movement) / clocks_per_90_movement;
    // A 180 degrees rotation frame is twice as long as a 90 degrees
    // rotation frame. For this reason, the rotation phase is twice
    // smaller for such frames.
    #switch (pos_in_180_frame)
      #case (1)
        #local rot_phase = rot_phase / 2;
      #break
      #case (2)
        // 1/2 is added to extend the phase to the second half of the
        // frame.
        #local rot_phase = rot_phase / 2 + 0.5;
      #break
    #end

    #local rotation = <showed_movements[current_movement].x, showed_movements[current_movement].y, showed_movements[current_movement].z>;
    #local rotation = rotation * rot_phase;
    #local showed_movements[current_movement] = <rotation.x, rotation.y, rotation.z, showed_movements[current_movement].t>;

    rubik_cube_rotate_layers(rcube, showed_movements)
  #else
    rubik_cube_rotate_layers(rcube, movements)
  #end
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
