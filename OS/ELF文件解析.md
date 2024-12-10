## ELF文件

### 编译和链接

ELF代表*Executable and Linkable Format*，是类Unix平台最通用的二进制文件格式。下面三种文件的格式都是ELF。

- 目标文件`.o`
- 动态库文件`.so`
- `.o`和`.so`链接得到的二进制可执行文件

编译链接与执行过程中的文件转换如下图所示。

<img src="https://my-pic.miaops.sbs/2024/11/image-20241130162807177.png" alt="image-20241130162807177" style="zoom: 50%;" />

### 文件结构

根据冯诺伊曼原理，程序有指令和数据构成，因此ELF文件存储的内容即代码（指令）+数据+其他元信息。

ELF文件是静态程序转换为进程的桥梁，结构概览如下图：

1. *FILE HEDER*：描述整个文件的组织结构。
2. *Program Header Table*：描述如何将 ELF 文件中的段映射到内存中，它为操作系统的加载器提供信息，告知哪些段需要被加载到内存中、它们的权限以及如何映射。
3. *Section Header Table*：描述 ELF 文件中的各个节，提供了每个节的详细信息，如名称、大小、类型和位置等。
4. *Section / Segment*：节从链接角度描述elf文件，段从内存加载角度描述elf文件。

![image-20241130141031157](https://my-pic.miaops.sbs/2024/11/image-20241130141031157.png)

ELF文件用于链接和加载两个阶段，有两个视图，链接视图和执行视图。

| 视图     | 存储内容                            | 数据结构               | 使用阶段   | 文件格式    |
| -------- | ----------------------------------- | ---------------------- | ---------- | ----------- |
| 链接视图 | 静态程序，用节(Section)组织         | *Section Header Table* | 编译，链接 | `.o` ,`.so` |
| 执行视图 | 加载后到内存分布，用段(Segment)组织 | *Program Header Table* | 加载       | 可执行程序  |

![](https://weichao-io-1257283924.cos.ap-beijing.myqcloud.com/qldownload/%E7%AC%AC-4-%E7%AB%A0%EF%BC%9A%E6%B7%B1%E5%85%A5%E7%90%86%E8%A7%A3-ELF-%E6%96%87%E4%BB%B6%E6%A0%BC%E5%BC%8F/1.png)Section 和 Segment 是 **逻辑到物理的映射关系**：

- 一个Segment对应多个Section
- 一个Section只能对应一个Segment

典型的对应关系：

| **执行段名称（Segments）** | **包含的节（Sections）** | 权限 |
| -------------------------- | ------------------------ | ---- |
| PT_LOAD（代码段）          | .text，.rodata           | R E  |
| PT_LOAD（数据段）          | .data，.bss              | RW   |
| PT_DYNAMIC                 | .dynamic，.got，.plt     | RW   |
| PT_INTERP                  | .interp                  | R    |
| PT_NOTE                    | .note                    | R    |
| PT_SHLIB                   | .shstrtab，.symtab       | RW   |
| PT_TLS                     | .tbss，.tdata            | R,RW |

加载阶段，加载器会按照Segment来组织虚拟内存，构造一个进程的内存空间，完成一个静态文件到进程的转换。



## ELF文件解析

基本思路：根据ELF Header中的元信息，跳转到对应部分进行解析。

![image-20241201124307267](https://my-pic.miaops.sbs/2024/12/image-20241201124307267.png)

### readelf -l fileName

解析ELF文件的文件头，数据结构如下，逐个解析即可：

```cpp
typedef struct
{
  unsigned char	e_ident[EI_NIDENT];	/* Magic number and other info */
  Elf64_Half	e_type;			/* Object file type */
  Elf64_Half	e_machine;		/* Architecture */
  Elf64_Word	e_version;		/* Object file version */
  Elf64_Addr	e_entry;		/* Entry point virtual address */
  Elf64_Off	e_phoff;		/* Program header table file offset */
  Elf64_Off	e_shoff;		/* Section header table file offset */
  Elf64_Word	e_flags;		/* Processor-specific flags */
  Elf64_Half	e_ehsize;		/* ELF header size in bytes */
  Elf64_Half	e_phentsize;		/* Program header table entry size */
  Elf64_Half	e_phnum;		/* Program header table entry count */
  Elf64_Half	e_shentsize;		/* Section header table entry size */
  Elf64_Half	e_shnum;		/* Section header table entry count */
  Elf64_Half	e_shstrndx;		/* Section header string table index */
} Elf64_Ehdr;
```

| 成员        | 含义                                     | 备注                                                         |
| ----------- | ---------------------------------------- | ------------------------------------------------------------ |
| e_ident     | 文件信息                                 | 下标：<br />[0.3]：魔数<br />4：文件类<br />5：数据编码<br />6：文件版本<br />7：补齐 |
| e_type      | 文件类型                                 | ET_NONE，ET_REL，ER_EXEC，ET_DYN，ET_CORE                    |
| e_machine   | 机器架构                                 | EM_NONE，EM_M32，EM_SPARC，EM_386，EM_68K，EM_88K，EM_860，EM_MIPS |
| e_version   | 目标文件版本                             | EV_NONE，EV_CURRENT                                          |
| e_entry     | 入口项地址                               | 上文图中的Entry Point指针                                    |
| e_phoff     | 程序头部表偏移                           | **Program Header Table Offset**                              |
| e_shoff     | 节头表偏移                               | **Section Header Table Offset**                              |
| e_flags     | 文件中与特定处理器相关的标志             |                                                              |
| e_ehsize    | ELF 文件头部的字节长度                   | ELF Header Size                                              |
| e_phentsize | 程序头部表中每个表项的字节长度           | **Program Header Entry Size**                                |
| e_phnum     | 程序头部表的项数                         | **Program Header Entry Number**                              |
| e_shentsize | 节头的字节长度                           | **Section Header Entry Size**                                |
| e_shnum     | 节头表中的项数                           | **Section Header Number**                                    |
| e_shstrndx  | 节头表中与节名字符串表相关的表项的索引值 | **Section Header Table Index Related With Section Name String Table** |



### readelf -S fileName

解析ELF文件的节头表。

依照文件头信息得到节头表：（elf_header为Elf64_Ehdr类型指针）

- 获得节头表地址：`elf_header + elf_header->e_shoff` 
- 遍历节头表：表大小：`elf_header->e_shnum`

- 节头表中每个元素的数据结构如下

```cpp
typedef struct
{
  Elf64_Word	sh_name;		/* Section name (string tbl index) */
  Elf64_Word	sh_type;		/* Section type */
  Elf64_Word	sh_flags;		/* Section flags */
  Elf64_Addr	sh_addr;		/* Section virtual addr at execution */
  Elf64_Off	sh_offset;		/* Section file offset */
  Elf64_Word	sh_size;		/* Section size in bytes */
  Elf64_Word	sh_link;		/* Link to another section */
  Elf64_Word	sh_info;		/* Additional section information */
  Elf64_Word	sh_addralign;		/* Section alignment */
  Elf64_Word	sh_entsize;		/* Entry size if section holds table */
} Elf64_Shdr;
```



### readelf -s fileName

解析ELF文件中符号表。

符号表作为一个节存储，遍历所有节，根据``elf_shdr->sh_type`判断是否为符号表，如果是则解析该节（elf_shdr为Elf64_Shdr类型指针）

- 节中元素数量：`elf_shdr->sh_size / elf_shdr->sh_entsize`

- 符号表作为节中元素结构如下：

```cpp
typedef struct
{
  Elf64_Word	st_name;		/* Symbol name (string tbl index) */
  Elf64_Addr	st_value;		/* Symbol value */
  Elf64_Word	st_size;		/* Symbol size */
  unsigned char	st_info;		/* Symbol type and binding */
  unsigned char	st_other;		/* Symbol visibility */
  Elf64_Section	st_shndx;		/* Section index */
} Elf64_Sym;
```



## 程序执行结果

编译： `gcc -o elf_reader elf_reader.c `

1. 和`readelf -h a.out`对比

![image-20241201163134850](https://my-pic.miaops.sbs/2024/12/image-20241201163134850.png)

![image-20241201163200359](https://my-pic.miaops.sbs/2024/12/image-20241201163200359.png)

2. 和`readelf -S a.out`对比

![image-20241201163435254](https://my-pic.miaops.sbs/2024/12/image-20241201163435254.png)

![image-20241201163344153](https://my-pic.miaops.sbs/2024/12/image-20241201163344153.png)

3. 和`readelf -s a.out`对比

![image-20241201163713440](https://my-pic.miaops.sbs/2024/12/image-20241201163713440.png)

![image-20241201163611181](https://my-pic.miaops.sbs/2024/12/image-20241201163611181.png)


