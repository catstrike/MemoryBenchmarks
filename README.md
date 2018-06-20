# Memory Benchmarks

Benchmarks work only for Mac at this point. I'm going to add Windows and Linux soon.

First you need to build the project
```
$ make
```

To run Writing Test:
```
$ ./writing
```

To run Alignment Test with proper alignment and without locks:
```
$ ./crw
```

To run Alignment Test unaligned without locks:
```
$ ./crw_unaligned
```

To run Alignment Test unaligned with locks:
```
$ ./crw_unaligned_locked
```
