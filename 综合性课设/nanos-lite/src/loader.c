#include "proc.h"
#include <elf.h>
#include "fs.h"

#ifdef __ISA_AM_NATIVE__
#define Elf_Ehdr Elf64_Ehdr
#define Elf_Phdr Elf64_Phdr
#else
#define Elf_Ehdr Elf32_Ehdr
#define Elf_Phdr Elf32_Phdr
#endif

// #define DEFAULT_ENTRY ((void *)0x830000c8)

extern size_t ramdisk_read(void *buf, size_t offset, size_t len);
extern size_t ramdisk_write(const void*, size_t, size_t);
extern size_t get_ramdisk_size();

static uintptr_t loader(PCB *pcb, const char *filename)
{
  // printf("loader\n");

  // Elf_Phdr head_pro;//程序头表
  // Elf_Ehdr head_elf;//elf头
  // ramdisk_read(&head_elf,0x0,sizeof(Elf_Ehdr));
  // size_t siz=head_elf.e_phentsize,cnt=head_elf.e_phnum;
  // for (size_t i=0;i<cnt;++i)
  // {
  // 	ramdisk_read((&head_pro),i*siz+head_elf.e_phoff,siz);
  // 	if (head_pro.p_type!=PT_LOAD) continue;
  // 	ramdisk_read((uintptr_t*)(head_pro.p_vaddr),head_pro.p_offset,head_pro.p_filesz);
  // 	if (head_pro.p_filesz==head_pro.p_memsz) continue;
  // 	memset((uintptr_t*)(head_pro.p_vaddr+head_pro.p_filesz),0,head_pro.p_memsz-head_pro.p_filesz);
  // }
  // return head_elf.e_entry;

  Elf_Ehdr Ehdr;
  int fd = fs_open(filename, 0, 0);
  fs_lseek(fd, 0, SEEK_SET);
  fs_read(fd, &Ehdr, sizeof(Ehdr));
  for (int i = 0; i < Ehdr.e_phnum; i++)
  {
    Elf_Phdr Phdr;
    fs_lseek(fd, Ehdr.e_phoff + i * Ehdr.e_phentsize, SEEK_SET);
    fs_read(fd, &Phdr, sizeof(Phdr));
    if (!(Phdr.p_type & PT_LOAD))
    {
      continue;
    }
    fs_lseek(fd, Phdr.p_offset, SEEK_SET);
    fs_read(fd, (void *)Phdr.p_vaddr, Phdr.p_filesz);
    for (unsigned int i = Phdr.p_filesz; i < Phdr.p_memsz; i++)
    {
      ((char *)Phdr.p_vaddr)[i] = 0;
    }
  }
  return Ehdr.e_entry;
  printf("%x\n",Ehdr.e_entry);
}

void naive_uload(PCB *pcb, const char *filename)
{
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %x", entry);
  ((void (*)())entry)();
}

void context_kload(PCB *pcb, void *entry)
{
  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _kcontext(stack, entry, NULL);
}

void context_uload(PCB *pcb, const char *filename)
{
  uintptr_t entry = loader(pcb, filename);

  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _ucontext(&pcb->as, stack, stack, (void *)entry, NULL);
}
