THIS REPO CONTAINS ODDS AND ENDS

1. Extremely efficient multithreaded singleton

This is basically a double checked singleton with the additional propety that 
the "GetInstance()" method is a pointer to a function, thus it gets switched after initialization.
Once initialization is complete, the singleton GetInstance is then serviced by a different function
that eliminates the "if" statements
