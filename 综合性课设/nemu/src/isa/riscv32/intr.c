#include "rtl/rtl.h"
#include "cpu/exec.h"

void raise_intr(uint32_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * That is, use ``NO'' to index the IDT.
   */
    decinfo.isa.sepc = epc;
    // printf("epc%x\n", epc);
    decinfo.isa.scause = NO;
    // printf("stvec%x\n", decinfo.isa.stvec);
    // decinfo.jmp_pc = decinfo.isa.stvec;
    rtl_j(decinfo.isa.stvec);
}

bool isa_query_intr(void) {
  return false;
}
