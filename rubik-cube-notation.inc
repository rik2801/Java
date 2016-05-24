// Extended David Singmaster's notation for 3x3x3 cubes.
// Each turn is a clockwise (if look directly on the rotated face),
// counter-clockwise turns can be made by negating, for example:
// L' = -L, F2' = -F2, etc.
#declare L   = < -90,    0,    0, 0>;            // Left side.
#declare L2  = <-180,    0,    0, 0>;
#declare R   = <  90,    0,    0, 2>;            // Right side.
#declare R2  = < 180,    0,    0, 2>;
#declare D   = <   0,  -90,    0, 0>;            // Bottom side (down).
#declare D2  = <   0, -180,    0, 0>;
#declare U   = <   0,   90,    0, 2>;            // Top side (up).
#declare U2  = <   0,  180,    0, 2>;
#declare F   = <   0,    0,  -90, 0>;            // Front side.
#declare F2  = <   0,    0, -180, 0>;
#declare B   = <   0,    0,   90, 2>;            // Back side.
#declare B2  = <   0,    0,  180, 2>;
#declare M   = < -90,    0,    0, 1>;            // Middle - the layer between L and R, turn direction as L (top-down).
#declare M2  = <-180,    0,    0, 1>;
#declare E   = <   0,  -90,    0, 1>;            // Equator - the layer between U and D, turn direction as D (left-right).
#declare E2  = <   0, -180,    0, 1>;
#declare S   = <   0,    0,  -90, 1>;            // Standing - the layer between F and B, turn direction as F (clockwise).
#declare S2  = <   0,    0, -180, 1>;
