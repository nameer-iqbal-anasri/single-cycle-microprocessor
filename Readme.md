# RV32I MICROPROCESSOR

## DESIGN 
### Phase 1:
A RV32I RISCV Processor in which all integer type commands and operations 
can be performed (including jal,jalr,branch commands etc).Both sequential and control flow 
operations can be executed on this microprocessor. I have used RISCV assembly language 
instructions to decorde them through opcodes then the respective signals gets onn and all the
instructions breakdown into pieces including opcode, immediate ( constant ,if their any ),
alu operation ,registers etc.All this is done on logisim software. This microprocessor 
includes the following blocks:
- immediate generation block
- opcode decoder
- register file
- ALU
- Branch ALU
- ALU controller
And many multiplexers and memories from the top file veiw.

<img align="center" src="Doc/circuit_diagram.jpg" />

### Phase 2:
After implementing on a drag and drop software called
logisim. It is then coded in a hardware discriptive language
called SYSTEMVERILOG.In further upgradation a bus architechture
(SOC) called TILELINK is also implemented in this single cycle
processor which provides communication between memories and core.
For which 2 channel A are used for request signals
and 2 channel D are used for response signals from core to
memories (host to device) and viseversa.
After interconnecting whole processor it is tested on verilator and questa so far.

## SIMULATION
To run the Simulation :
1) Clone the repo.
3) Go to simulation dir :
   ```
   cd Simulation
   ```
### To run on Verilator using FuseSoC
4) ```
   fusesoc --cores-root=. run --target=sim top --vcd --timeout 100000
   ```
5) To see static waveform output on gtk-wave :
   ``` cd build/top_1.0/sim-verilator ```
   ``` gtkwave trace.vcd ```
### To run UVM verification using Questa
4) ```
   make sim
   ```
5) For GUI based simulation
   ```
   make simgui
   ```
## To run jaspergold
4) ```
   jg jaspergold.tcl
   ```

## Sample Tests
There's a folder in ```Simulation/rtl/tests``` which contains the assembly tests, 
convert them into hex using (venus)[https://venus.kvakil.me/] and as above mentioned 
update the hex file path in   ```inst.mem``` and run.
