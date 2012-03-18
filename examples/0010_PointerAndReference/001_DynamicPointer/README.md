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



