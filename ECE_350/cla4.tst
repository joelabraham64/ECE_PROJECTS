load CLA4.hdl,
output-list x[4]%B y[4]%B cin%B z[4]%B cout%B;

// Test Case 1: x=0000, y=0000, cin=0
set x[0]=0, set x[1]=0, set x[2]=0, set x[3]=0,
set y[0]=0, set y[1]=0, set y[2]=0, set y[3]=0,
set cin=0,
eval,
output;

// Test Case 2: x=0001, y=0001, cin=0
set x[0]=1, set x[1]=0, set x[2]=0, set x[3]=0,
set y[0]=1, set y[1]=0, set y[2]=0, set y[3]=0,
set cin=0,
eval,
output;


