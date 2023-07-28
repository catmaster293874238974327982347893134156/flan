#ifndef elf_h
#define elf_h
#include <fs/vfs.h>
#include <memory/vmm.h>
#include <stdint.h>

#define AT_NULL 0
#define AT_IGNORE 1
#define AT_EXECFD 2
#define AT_PHDR 3
#define AT_PHENT 4
#define AT_PHNUM 5
#define AT_PAGESZ 6
#define AT_BASE 7
#define AT_FLAGS 8
#define AT_ENTRY 9
#define AT_NOTELF 10
#define AT_UID 11
#define AT_EUID 12
#define AT_GID 13
#define AT_EGID 14

#define ELFDATA2LSB 1
#define ELFDATA2LSB 1
#define ELFOSABI_SYSV 0
#define EM_X86_64 62

#define ELFCLASS64 2
#define ARCH_ELF_ISA 0x3E
#define ARCH_ELF_ENDIANNESS 1

#define EI_CLASS 4      /* Class of machine. */
#define EI_DATA 5       /* Data format. */
#define EI_VERSION 6    /* ELF format version. */
#define EI_OSABI 7      /* Operating system / ABI identification */
#define EI_ABIVERSION 8 /* ABI version */
#define OLD_EI_BRAND 8  /* Start of architecture identification. */
#define EI_PAD 9        /* Start of padding (per SVR4 ABI). */
#define EI_NIDENT 16    /* Size of e_ident array. */
#define ELFMAG "\177ELF"
#define EI_NIDENT 16
// ELF definitions common to all 64-bit architectures.
typedef uint64_t Elf64_Addr;
typedef uint16_t Elf64_Half;
typedef uint64_t Elf64_Off;
typedef int32_t Elf64_Sword;
typedef int64_t Elf64_Sxword;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Lword;
typedef uint64_t Elf64_Xword;

typedef Elf64_Word Elf64_Hashelt;

typedef Elf64_Xword Elf64_Size;
typedef Elf64_Sxword Elf64_Ssize;

#define ET_EXEC 2
#define EM_AMD64 62
#define PT_LOAD 1
#define PT_INTERP 3
#define PT_PHDR 6

#define PF_X 1
#define PF_W 2
#define PF_R 4

// ELF header.
typedef struct {
    unsigned char e_ident[EI_NIDENT]; /* File identification. */
    Elf64_Half e_type;                /* File type. */
    Elf64_Half e_machine;             /* Machine architecture. */
    Elf64_Word e_version;             /* ELF format version. */
    Elf64_Addr e_entry;               /* Entry point. */
    Elf64_Off e_phoff;                /* Program header file offset. */
    Elf64_Off e_shoff;                /* Section header file offset. */
    Elf64_Word e_flags;               /* Architecture-specific flags. */
    Elf64_Half e_ehsize;              /* Size of ELF header in bytes. */
    Elf64_Half e_phentsize;           /* Size of program header entry. */
    Elf64_Half e_phnum;               /* Number of program header entries. */
    Elf64_Half e_shentsize;           /* Size of section header entry. */
    Elf64_Half e_shnum;               /* Number of section header entries. */
    Elf64_Half e_shstrndx;            /* Section name strings section. */
} Elf64_Ehdr;

// Section header.
typedef struct {
    Elf64_Word sh_name;       /* Section name (index into the
                                         section header string table). */
    Elf64_Word sh_type;       /* Section type. */
    Elf64_Xword sh_flags;     /* Section flags. */
    Elf64_Addr sh_addr;       /* Address in memory image. */
    Elf64_Off sh_offset;      /* Offset in file. */
    Elf64_Xword sh_size;      /* Size in bytes. */
    Elf64_Word sh_link;       /* Index of a related section. */
    Elf64_Word sh_info;       /* Depends on section type. */
    Elf64_Xword sh_addralign; /* Alignment in bytes. */
    Elf64_Xword sh_entsize;   /* Size of each entry in section. */
} Elf64_Shdr;

// Program header.
typedef struct {
    Elf64_Word p_type;    /* Entry type. */
    Elf64_Word p_flags;   /* Access permission flags. */
    Elf64_Off p_offset;   /* File offset of contents. */
    Elf64_Addr p_vaddr;   /* Virtual address in memory image. */
    Elf64_Addr p_paddr;   /* Physical address (not used). */
    Elf64_Xword p_filesz; /* Size of contents in file. */
    Elf64_Xword p_memsz;  /* Size of contents in memory. */
    Elf64_Xword p_align;  /* Alignment in memory and file. */
} Elf64_Phdr;

struct auxval {
    uint64_t at_entry;
    uint64_t at_phdr;
    uint64_t at_phent;
    uint64_t at_phnum;
};
bool elf_load(pagemap_t *pagemap, vfs_node_t *node, struct auxval *aux,
              const char **ld_path);
#endif
