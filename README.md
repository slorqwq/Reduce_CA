# Reducing Quantum Error Correction Overhead with Versatile Flag-Sharing Syndrome Extraction Circuits

## To enable fault-tolerant quantum computation, efficient error syndrome extraction is crucial.
Given that error correction processes may introduce new errors, the circuits for syndrome extraction
should utilize fewer ancillary qubits and maintain low circuit depth. Hence, minimizing the circuit
area, defined as the product of circuit computation length and physical qubits, is imperative. Flagged
syndrome extraction can reduce the number of physical qubits involved, yet the traditional serial
implementation of syndrome extraction circuits can result in extensive circuit depth. Our proposal
is to parallelize flagged syndrome extraction with shared flag qubits for general quantum stabilizer
codes. Versatile parallelization techniques are employed to decrease the required circuit area.
Specifically, error information from the measurement result and the flag measurement is integrated
into a lookup table decoder’s design, allowing us to parallelize circuit syndrome extraction at once.
We present a parallelized circuit for the [[5, 1, 3]] code, achieving the minimum known circuit area.
This methodology extends to codes with higher distances, as demonstrated with the [[17, 1, 5]] and
[[19, 1, 5]] codes.

### Development environment
 - IDE: Dev-C++ 5.11
 - Compiler: TDM-GCC 4.9.2 64-bit Release 
