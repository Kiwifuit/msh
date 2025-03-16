# :shell: Mini SHell

msh is a minimal shell for my minimal linux distro. At the moment,
this project has no plans to do anything other than reinvent the
wheel for fun.

## Building

Requires `cmake`, `make`, and a **g**ood **c** **c**ompiler (or use clang)

```sh
mkdir build
cd build
cmake ..
make -j $(nproc) # not really needed as of now, but why not
./msh
```
