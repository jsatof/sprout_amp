# Sprout Amp
Amp plus Cabinet combo plugin for guitar

# Building
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug  -GNinja ..

# Add the following optional flag for override if using clang
# Sets the desired clang specific compiler flags
# -DCMAKE_USER_MAKE_RULES_OVERRIDE=$PWD/../cmake/clang_overrides.cmake
```
