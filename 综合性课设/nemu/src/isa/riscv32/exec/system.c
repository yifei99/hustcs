#include "cpu/exec.h"
extern void raise_intr(uint32_t, vaddr_t);

make_EHelper(ecallsret)
{

    switch (id_src2->val)
    {
    case 0x000:
        // printf("ecall\n");
        raise_intr(reg_l(17), decinfo.seq_pc);
        print_asm_template1(ecall);
        break;
    case 0x102:
        // printf("sret\n");
        // printf("sret:%x\n", decinfo.isa.sepc);
        rtl_j(decinfo.isa.sepc);
        print_asm_template1(sret);                     
        break;
    default:
        assert(0);
    }
}

make_EHelper(csrr)
{
    // printf("csrr\n");
    switch (id_src2->val)
    {
    case 0x105:
        // printf("rstvec\n");
        rtl_li(&s0, decinfo.isa.stvec);
        rtl_mv(&s1, &id_src->val);
        decinfo.isa.stvec = s1 | s0;
        break;
    case 0x142:
        // printf("rscause\n");
        rtl_li(&s0, decinfo.isa.scause);
        rtl_mv(&s1, &id_src->val);
        decinfo.isa.scause = s1 | s0;
        break;
    case 0x100:
        // printf("rsstatus\n");
        rtl_li(&s0, decinfo.isa.sstatus);
        rtl_mv(&s1, &id_src->val);
        decinfo.isa.sstatus = s1 | s0;
        break;
    case 0x141:
        // printf("rsepc\n");
        rtl_li(&s0, decinfo.isa.sepc);
        rtl_mv(&s1, &id_src->val);
        decinfo.isa.sepc = s1 | s0;
        break;
    default:
        assert(0);
    }
    rtl_sr(id_dest->reg, &s0, 4);

    print_asm_template1(csrr);
}
make_EHelper(csrw)
{
//     printf("csrw\n");
    switch (id_src2->val)
    {
    case 0x105:
        // printf("wstvec\n");
        rtl_li(&s0, decinfo.isa.stvec);
        rtl_mv(&s1, &id_src->val);
        decinfo.isa.stvec = s1;
        // printf("stvec%x",s1);
        break;
    case 0x142:
        // printf("wscause\n");
        rtl_li(&s0, decinfo.isa.scause);
        rtl_mv(&s1, &id_src->val);
        decinfo.isa.scause = s1;
        break;
    case 0x100:
        // printf("wsstatus\n");
        rtl_li(&s0, decinfo.isa.sstatus);
        rtl_mv(&s1, &id_src->val);
        decinfo.isa.sstatus = s1;
        break;
    case 0x141:
        // printf("wsepc\n");
        rtl_li(&s0, decinfo.isa.sepc);
        rtl_mv(&s1, &id_src->val);
        decinfo.isa.sepc = s1;
        break;
    default:
        assert(0);
    }
    rtl_sr(id_dest->reg, &s0, 4);

    print_asm_template1(csrw);
}