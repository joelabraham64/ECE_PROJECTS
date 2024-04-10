load FullAdder.hdl,
output-file FullAdder.out,
// compare-to FullAdder.cmp, (This line is commented out or removed)
output-list x y cin z cout;

set x 0,
set y 0,
set cin 0,
eval,
output;

set x 0,
set y 0,
set cin 1,
eval,
output;

set x 0,
set y 1,
set cin 0,
eval,
output;

set x 0,
set y 1,
set cin 1,
eval,
output;

set x 1,
set y 0,
set cin 0,
eval,
output;

set x 1,
set y 0,
set cin 1,
eval,
output;

set x 1,
set y 1,
set cin 0,
eval,
output;

set x 1,
set y 1,
set cin 1,
eval,
output;
