#include "colors.inc"
#include "transforms.inc"
#include "shapes.inc"


camera {
  location <2, 2, -7>
  look_at  <0, 0,  0>
}


light_source {
  <2, 4, -3>
  color White
}

light_source {
  <4, 2, -3>
  color White
}


// Axis
cylinder {
  <0, 0, 0>, <5, 0, 0>, 0.01
  open
  pigment { Red }
}

cylinder {
  <0, 0, 0>, <0, 5, 0>, 0.01
  open
  pigment { Green }
}

cylinder {
  <0, 0, 0>, <0, 0, 5>, 0.01
  open
  pigment { Blue }
}


// Cube
#declare classic_colors = array[6] {Blue, Red, Yellow, Green, Orange, White};


#macro create_part(colors)
  object {
    Round_Box(<-0.5, -0.5, -0.5>, <0.5, 0.5, 0.5>, 0.1, 1)
    pigment {
      cubic colors[0], colors[1], colors[2], colors[3], colors[4], colors[5]
    }
    translate <0.5, 0.5, 0.5>
  }
#end


#macro get_all_parts(dim_x, dim_y, dim_z, colors)
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
	  create_part(part_colors)
	  transform {
	    translate <pos_x, pos_y, pos_z> - <dim_x / 2, dim_y / 2, dim_z / 2>
	  }
	}
      #end
    #end
  #end
  parts
#end


#macro rotate_by_x(dim_x, dim_y, dim_z, parts, layer, a)
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


#macro rotate_by_y(dim_x, dim_y, dim_z, parts, layer, a)
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


#macro rotate_by_z(dim_x, dim_y, dim_z, parts, layer, a)
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


#macro move_parts(dim_x, dim_y, dim_z, parts, movement)
  // todo check that movement is valid.

  #if (movement.x != 0)
    #switch (movement.x)
      #case (-90)
	#local parts = rotate_by_x(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (180) #case (-180)
	#local parts = rotate_by_x(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (90)
	#local parts = rotate_by_x(dim_x, dim_y, dim_z, parts, movement.t, 90);
    #end
  #elseif (movement.y != 0)
    #switch (movement.y)
      #case (-90)
	#local parts = rotate_by_y(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (180) #case (-180)
	#local parts = rotate_by_y(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (90)
	#local parts = rotate_by_y(dim_x, dim_y, dim_z, parts, movement.t, 90);
    #end
  #elseif (movement.z != 0)
    #switch (movement.z)
      #case (-90)
	#local parts = rotate_by_z(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (180) #case (-180)
	#local parts = rotate_by_z(dim_x, dim_y, dim_z, parts, movement.t, 90);
      #case (90)
	#local parts = rotate_by_z(dim_x, dim_y, dim_z, parts, movement.t, 90);
    #end
  #end

  parts
#end


#macro create_cube(dim_x, dim_y, dim_z, colors, movements)
  #local parts = get_all_parts(dim_x, dim_y, dim_z, colors)

  #for (movementIx, 0, dimension_size(movements, 1) - 1)
    #local parts = move_parts(dim_x, dim_y, dim_z, parts, movements[movementIx]);
  #end

  union {
    #for (item, 0, dim_x * dim_y * dim_z - 1)
      object { parts[item] }
    #end
  }
#end


create_cube(
  3, 3, 3, classic_colors,
  array[4] {<90, 0, 0, 1>, <0, 0, 90, 1>, <-90, 0, 0, 1>, <0, 0, -90, 1>}
)
