
Build with libreadline:
- `cmake -B build/ -S . -Dreadline=1 && cmake --build build/`
Build with `getline()` instead (default):
- `cmake -B build/ -S . -Dreadline=0 && cmake --build build/`
Clean build directory:
- `./clean.sh` (same as just `rm -rf build/`)
Clean built binaries:
- `cmake --build build/ -t clean`
