Running Options
===============

Commands:

 * make # Run the default target, compile with optimization flags (-O2 -DONLINE_JUDGE) and run `diff`.
 * make debug # Compile with debug settings (enabled debug symbols and no optimization).
 * make valgrind # Compile with target `debug` and run valgrind on executable.
 
There is two files `example.in` and `example.out`, first used to pass as
input for the compiled program and second to compare the compiled program
output with the `example.out` content.

