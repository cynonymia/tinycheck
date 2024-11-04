# TinyCheck

A small and efficient model checker, verifying assignments for Propositional Formulas.

## Build
```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j
```

## Format
TinyCheck accepts DIMACS-formulas. The assignments have to be provided as a stream of integers (e.g. "1 2 3 ... 99"). Whitespaces and new lines are ignored in the latter.
```
TinyCheck v0.1 (alpha-phase)
A small, efficient model checker
usage: <Formula> [<Model>] [-h] [-d] [-q]
<Source File>:         A file containing the target DIMACS formula. If non specified or "-", stdin is used.
-h, --help:            When specified, this text is printed
                       <Formula> and <Model> are ignored with this argument
-d, --debug:           When specified, verbose is set to debug level.
-q, --quiet:           When specified, verbose is turned off

```
