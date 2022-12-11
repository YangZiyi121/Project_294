# CS294V_Project
Tinker : CPU simulator

This project implements a C++ simulator based for a CPU called "Tinker". The simulated architecture is as illustrated in the figure below.

<img src="tinker.png" alt="architecture" />

The architecture is inheredetly similar to the RISC-V architecture. The main similarility is based in the central block that is composed an Instruction Memory (IM) that provides the instructions driven by a Program Counter (PC), a Register File (RF) made of 32 64bits-registers, an Arithmetic Logic Unit (ALU) that performs all the arithmetical and the logical operations, and a Data Memory that holds the data in runtime.

The components named in numbers 1 to 4 are muxes. They are assigned these numbers for easiness of tracking in the simulator core. The diamonds are buffering registers used plugged in the data paths to ensure the synchronization of the different operations being executed in the components of the processor.

<img src="chunk1.png" alt="diamonds and numbered components illustration" width="400px" />

As illustrated in the figure above, the component numbered in 1 is a mux that choses between the two inputs `Rt` and `Rd`. The diamonds on the path that connects `Rt` to the mux are registers used to buffer the signal comming from `Rt` for 2 cycles while waiting for the control signal to arrive (the controls will be discussed later).

<img src="chunk2.png" alt="control block illustration" width="400px" />

The control part in the figure above is used to orchastrate the work of the diffrent components of the CPU using a Decoder that receives the instruction from the IM, transforming it into a sequence of control signals and forwarding them to the Controller that will emit them one by one every cycle. The control signal that comes out of the Controller is splitted to drive every component seperately.

## Artifact evaluation

## Data Path

<img src="DP.png" alt="data path illustration" />

The data path of the CPU is composed of an Instruction Memory (IM), a Register File (RF), an Arithmetic Logic Unit (ALU), and a Data Memory (DM).

The IM has 5 outputs. The first output is the `OP` signal that forwards the OPERATION CODE to the control section. The outputs `Rs` and `Rt` are the operand of several operations. The `Rt` is multiplexed with another output `Rd` (Destination) as the RF is only dual-ported and `Rs` is the required signal when operations are performed with an immediate value sent on another output `L`. Notably, the `Rd` is again multiplexed in `
2`

## Control Path
