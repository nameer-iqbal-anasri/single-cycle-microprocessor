//#include "verilated.h"
#include "Vtop_main.h"
#include "verilated_vcd_c.h" //VCD file

using namespace std;

vluint64_t main_time=0;

int main(int argc, char** argv, char** env){
    Verilated::commandArgs(argc, argv);
    Vtop_main* my_top = new Vtop_main;

    VerilatedVcdC* vcd_file=0;
  
     const char *vcd = Verilated::commandArgsPlusMatch("vcd="); //--vdc use then only it will activate
         if (vcd[0]) {
          Verilated::traceEverOn(true);
          vcd_file = new VerilatedVcdC;
          my_top->trace (vcd_file, 99);
          vcd_file->open ("trace.vcd");
        }

vluint64_t timeout = 0;
	const char *arg_timeout = Verilated::commandArgsPlusMatch("timeout=");
	if (arg_timeout[0]) {
	  timeout = atoi(arg_timeout+9);
  }

vluint64_t vcd_start = 0;
	const char *arg_vcd_start = Verilated::commandArgsPlusMatch("vcd_start=");
	if (arg_vcd_start[0]) {
	  vcd_start = atoi(arg_vcd_start+11);
  }

    bool dump = false;
    my_top->clk = 1;
    my_top->reset = 1; // Set some inputs
    while (!Verilated::gotFinish()) {

        if (vcd_file && !dump && !(main_time >= timeout)) dump = true;
        if (main_time > 10) my_top->reset = 1;
        else my_top->reset = 0;
        
        my_top->eval();

        if (dump)  vcd_file->dump(main_time);
        if (my_top->top_main__DOT__data_mem_adapter__DOT__data_m__DOT__sram[4092]==0xaf &&
            my_top->top_main__DOT__data_mem_adapter__DOT__data_m__DOT__sram[4093]==0xbe &&
            my_top->top_main__DOT__data_mem_adapter__DOT__data_m__DOT__sram[4094]==0xad &&
            my_top->top_main__DOT__data_mem_adapter__DOT__data_m__DOT__sram[4095]==0xde) {
          my_top->reset = 0;
          printf("\n\033[32m=========================================\033[0m\n");
          printf("\033[32m===============TEST PASSED===============\033[0m\n");
          printf("\033[32m=========================================\033[0m\n");
          break;
        }
        else if (my_top->top_main__DOT__data_mem_adapter__DOT__data_m__DOT__sram[4092]==0x1) { // temp to host value and address
          my_top->reset = 0;
          printf("\n\033[31m=========================================\033[0m\n");
          printf("\033[31m===============TEST FAILED===============\033[0m\n");
          printf("\033[31m=========================================\033[0m\n");
          break;
        }
        else if (main_time >= timeout) {
          my_top->reset = 0;
          printf("\n\033[31m=========================================\033[0m\n");
          printf("\033[31m===============TEST TIMEDOUT=============\033[0m\n");
          printf("\033[31m=========================================\033[0m\n");
          break;
	      }
        
        my_top->clk = !my_top->clk;
        
        main_time += 2;
    }

    if (vcd_file)
	        vcd_file->close();
    exit(0);
}
