# PaciWar

Remake of the "pacifism" mode from Geometry Wars 2.

## Compilation

PaciWar uses CMake to create Makefile/IDE's project files. Additionnaly, 
you need SFML 2 to compile.

Linux (Makefiles), release version :
```
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DSFML_ROOT=path_to_sfml
```

Linux (Makefiles), debug version :
```
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DSFML_ROOT=path_to_sfml
```

If you need more information about that, read CMake documentation.

## Building installer

At the moment, this is only tested on Windows.
PaciWar also uses CPack to build binaries/installers.
