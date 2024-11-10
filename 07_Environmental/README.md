
Build with libreadline:
- `cmake -B build/ -S . -Dreadline=1 && cmake --build build/`
Build with `getline()` instead (default):
- `cmake -B build/ -S . -Dreadline=0 && cmake --build build/`
Clean build directory:
- `./clean.sh`
Clean built binaries:
- `cmake --build build/ -t clean`
Run tests:
- `ctest` in build directory (only tests with `RHasher` in the name are relevant)
