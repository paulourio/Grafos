Pointers
========

Diference of malloc/free and new/delete
---------------------------------------

Copied from:
http://stackoverflow.com/questions/240212/what-is-the-difference-between-new-delete-and-malloc-free


new/delete
----------

    Allocate/release memory
        Memory allocated from 'Free Store'
        Returns a fully typed pointer.
        new (standard version) never returns a NULL (will throw on failure)
        Are called with Type-ID (compiler calculates the size)
        Has a version explicitly to handle arrays.
        Reallocating (to get more space) not handled intuitively (because of copy constructor).
        If they call malloc/free is implementation defined.
        Can add a new memory allocator to deal with low memory (set_new_handler)
        operator new/delete can be overridden legally
        constructor/destructor used to initialize/destroy the object

malloc/free
-----------

    Allocates/release memory
        Memory allocated from 'Heap'
        Returns a void*
        Returns NULL on failure
        Must specify the size required in bytes.
        Allocating array requires manual calculation of space.
        Reallocating larger chunk of memory simple (No copy constructor to worry about)
        They will NOT call new/delete
        No way to splice user code into the allocation sequence to help with low memory.
        malloc/free can NOT be overridden legally

Technically memory allocated by new comes from the 'Free Store' while memory allocated by malloc comes from the 'Heap'. Whether these two areas are the same is an implementation details, which is another reason that malloc and new can not be mixed.


Using New/Delete
================

Look the example.  We create an integer, use it and then we release.

At this point, you can run `make valgrind` (make sure you have it installed).
The `./Main` output will be "b value is 56".  Valgrind will tell you
any problem you've made in your program about memory management (for instance,
if you forget to release an allocated block or accessed a not allocated
block).

	==3424== Memcheck, a memory error detector
	==3424== Copyright (C) 2002-2010, and GNU GPL'd, by Julian Seward et al.
	==3424== Using Valgrind-3.6.1-Debian and LibVEX; rerun with -h for copyright info
	==3424== Command: ./Main
	==3424== 
	b value is 56
	==3424== 
	==3424== HEAP SUMMARY:
	==3424==     in use at exit: 0 bytes in 0 blocks
	==3424==   total heap usage: 1 allocs, 1 frees, 4 bytes allocated
	==3424== 
	==3424== All heap blocks were freed -- no leaks are possible
	==3424== 
	==3424== For counts of detected and suppressed errors, rerun with: -v
	==3424== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)


This:

	==3424==   total heap usage: 1 allocs, 1 frees, 4 bytes allocated
	
The main.cpp have allocated and released one time, total of 4 bytes (it's the size of int).

