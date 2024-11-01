echo ========================Expected SAT=========================
./build/tinycheck ./examples/xor.dimacs ./examples/xor.sat.model $*
echo ========================Expected UNSAT========================
./build/tinycheck ./examples/xor.dimacs ./examples/xor.unsat.model $*
echo ==============================================================