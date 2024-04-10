load HalfAdder.hdl,
output-file HalfAdder.out,
// compare-to HalfAdder.cmp, (This line is commented out or removed)
output-list x y z cout;

set x 0,
set y 0,
eval,
output;

set x 0,
set y 1,
eval,
output;

set x 1,
set y 0,
eval,
output;

set x 1,
set y 1,
eval,
output;