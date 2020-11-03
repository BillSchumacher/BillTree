BillTree
========

This is a basic btree implementation in C.

The keys are uint64_t and hashed using xxhash.

I needed a dynamic container type, the value is a void pointer so anything can be stored.

It's up to the user to define a FreeValue function to assign the tree.

You should call BillTree_Free on application exit (atexit) or when you're done with it.

The hashed values are not suitable for long term storage according to the developers of xxhash, so you probably 
shouldn't do that.

If valgrind and fastbuild isn't installed the Makefile probably won't work.

Check src/example for usage.


Requirements
----
- xxhash (https://github.com/Cyan4973/xxHash)
- valgrind (Optional)
- fastbuild (Optional) (https://www.fastbuild.org/docs/home.html)

Ubuntu
```
    apt install libxxhash-dev
```

Contributing
----

Feel free to submit a PR.
