Algorithms and Graphs
=====================

Academic discipline exercises.

Building
--------

In order to build, you should have installed `cmake`.

This project should be build out-of-source:

```
	$ mkdir build; cd build
	$ cmake ..
	$ make
```

The default build target is "Debug".  You may set to build
for a Release:

	cmake -D CMAKE_BUILD_TYPE=Release ../

This will strip debugging information and enable optimizations.
If you want to get the `make` output (command-line executions),
run `make VERBOSE=1`.

Cleaning
--------

On `build` directory type `make clean` to remove all
files generated by compiler and linker.

Testing
-------

To run the test suite, on `build` directory type:

```
	$ ctest
```


