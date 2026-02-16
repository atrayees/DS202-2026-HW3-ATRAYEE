
---

## Build 

### Requirements

- Linux / WSL / macOS
- GCC
- CMake

### Build Steps
 
 The fasta file was downloaded in the examples directory, and named sequence.fasta
 
 From project root:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="Release" ..
make
```

Executable files will be created inside:
```bash
build/examples/
```

To run the code, run:
```bash
./examples/ds202_longest_repeat sequence.fasta
```

Also, next, we generate the random DNA as:
```bash
./examples/ds202_random_generator
```

This creates:
```bash
randomDNA.fasta
```

Finally, to run the code on this randomly generated fasta file, we run:
```bash
./examples/ds202_longest_repeat randomDNA.fasta
```
 
