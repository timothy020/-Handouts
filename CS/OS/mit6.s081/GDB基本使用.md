编译代码：`gcc -g -o program program.c`

启动：`gdb ./program`

GDB 命令总结：

| **命令**         | **功能**                                                     | **示例**                                        | **说明**                                               |
| ---------------- | ------------------------------------------------------------ | ----------------------------------------------- | ------------------------------------------------------ |
| `break`          | 在指定位置设置断点。可以设置函数名、行号、地址等位置。       | `break main`<br> `break 10`<br> `break my_func` | 在 `main` 函数、行号 10、或函数 `my_func` 处设置断点。 |
| `run`            | 运行程序。                                                   | `run`                                           | 启动程序执行。                                         |
| `start`          | 从第一行开始                                                 | `start`                                         | 启动并停留在第一行                                     |
| `continue`       | 程序继续执行，直到下一个断点或程序结束。                     | `continue`                                      | 继续程序的执行。                                       |
| `next`           | 执行当前行并跳到下一行，若当前行是函数调用，跳过该函数。     | `next`                                          | 不进入函数，跳到下一行。                               |
| `step`           | 执行当前行并进入函数内部。如果当前行是函数调用，进入该函数。 | `step`                                          | 进入当前行的函数内部。                                 |
| `finish`         | 执行当前函数的剩余部分，并返回调用它的函数。                 | `finish`                                        | 完成当前函数并返回到调用函数的位置。                   |
| `list`           | 查看源代码的某一部分，默认显示当前位置附近的代码。           | `list`<br> `list 10,20`                         | 显示当前代码行及其上下文，或指定显示行号区间的代码。   |
| `where`          | 显示调用栈，查看程序的调用链。                               | `where`                                         | 显示程序的当前调用栈。                                 |
| `print`          | 打印变量的值或表达式的结果。                                 | `print sum`<br> `print i + 10`                  | 打印当前变量的值。                                     |
| `watch`          | 设置监视点，监控某个变量的值变化。                           | `watch sum`                                     | 当 `sum` 变量的值发生变化时暂停程序。                  |
| `delete`         | 删除断点或监视点。                                           | `delete 1`                                      | 删除编号为 1 的断点。                                  |
| `info break`     | 查看所有断点信息。                                           | `info break`                                    | 显示当前所有的断点信息。                               |
| `info watch`     | 查看所有监视点信息。                                         | `info watch`                                    | 显示当前所有的监视点信息。                             |
| `info locals`    | 查看当前函数的局部变量。                                     | `info locals`                                   | 显示当前栈帧中的局部变量。                             |
| `info registers` | 查看所有寄存器的值。                                         | `info registers`                                | 显示 CPU 寄存器的当前值。                              |
| `quit`           | 退出 GDB 调试会话。                                          | `quit`                                          | 退出 GDB。                                             |
| `set variable`   | 修改变量的值。                                               | `set variable sum = 100`                        | 修改变量 `sum` 的值为 100。                            |
| `list`           | 查看当前文件中某个位置的代码段。                             | `list 10,20`<br />`list -`<br />`list 函数名`   | 查看第 10 行到第 20 行的代码。                         |

layout布局：

| **命令**       | **描述**         | **效果**                                                     |
| -------------- | ---------------- | ------------------------------------------------------------ |
| `layout split` | 创建分屏布局     | 上下分屏显示，默认上半部分显示源代码，下半部分显示汇编代码。 |
| `layout regs`  | 显示寄存器信息   | 将下半部分用于显示当前的寄存器内容。                         |
| `layout src`   | 显示源代码       | 将上半部分用于显示当前的源代码。                             |
| `layout asm`   | 显示汇编代码     | 将下半部分用于显示当前的汇编代码。                           |
| `layout stack` | 显示堆栈信息     | 将下半部分用于显示堆栈信息。                                 |
| `layout next`  | 切换到下一个布局 | 在不同的布局视图之间切换（例如，源代码视图、寄存器视图等）。 |
| `layout`       | 查看当前布局状态 | 显示当前布局类型。                                           |

### 快捷键：

| **快捷键**    | **描述**                                   |
| ------------- | ------------------------------------------ |
| `Ctrl + X, o` | 在不同布局之间切换（如源代码、寄存器等）。 |
| `Ctrl + X, +` | 增大当前窗口的大小。                       |
| `Ctrl + X, -` | 减小当前窗口的大小。                       |
| `Ctrl + X, 2` | 切换到分屏布局（上下两部分）。             |

`layout split`效果如下图：

![image-20241219111815615](https://my-pic.miaops.sbs/2024/12/image-20241219111815615.png)

### 查看寄存器

| 命令            | 目标                                                         | 显示内容                                                 |
| --------------- | ------------------------------------------------------------ | -------------------------------------------------------- |
| `print/x $satp` | 打印寄存器值，通常是直接查看寄存器本身的值                   | 显示 satp 寄存器的完整值，以十六进制格式呈现             |
| `x/2c $satp`    | 查看寄存器值作为地址对应的内存内容，并以字符（ASCII）格式显示 | 将 satp 寄存器的值当作内存地址，显示该地址的内容作为字符 |

其他格式化输出：

| **格式符号** | **含义**                               |
| ------------ | -------------------------------------- |
| x            | 以十六进制格式显示                     |
| d            | 以十进制格式显示                       |
| u            | 以无符号十进制格式显示                 |
| o            | 以八进制格式显示                       |
| t            | 以二进制格式显示                       |
| c            | 显示 ASCII 字符                        |
| s            | 显示以 NULL 结尾的字符串               |
| i            | 显示指令（反汇编显示内存中的机器代码） |



- In many cases, print statements will be sufficient, but sometimes being able to single step through some assembly code or inspecting the variables on the stack is helpful. To use gdb with xv6, run make make qemu-gdb in one window, run gdb (or riscv64-linux-gnu-gdb) in another window, set a break point, followed by followed by 'c' (continue), and xv6 will run until it hits the breakpoint. (See [Using the GNU Debugger](https://pdos.csail.mit.edu/6.828/2019/lec/gdb_slides.pdf) for helpful GDB tips.)
  在许多情况下，打印语句就足够了，但有时能够单步执行某些汇编代码或检查堆栈上的变量会很有帮助。要将 gdb 与 xv6 一起使用，请运行 make make qemu-gdb 在一个窗口中，运行 gdb （或者 

-  ）在另一个窗口中，设置一个断点，然后是“c”（继续），xv6 将运行直到遇到断点。 （有关有用的 GDB 提示，请参阅[使用 GNU 调试器](https://pdos.csail.mit.edu/6.828/2019/lec/gdb_slides.pdf)。）
  
- If your kernel hangs (e.g., due to a deadlock) or cannot execute further (e.g., due to a page fault when executing a kernel instruction), you can use gdb to find out where it is hanging. Run run 'make qemu-gdb' in one window, run gdb (riscv64-linux-gnu-gdb) in another window, followed by followed by 'c' (continue). When the kernel appears to hang hit Ctrl-C in the qemu-gdb window and type 'bt' to get a backtrace.
  如果您的内核挂起（例如，由于死锁）或无法执行 进一步（例如，由于执行内核时出现页面错误 指令），你可以使用 gdb 来找出它挂在哪里。跑步 在一个窗口中运行“make qemu-gdb”，运行 gdb (riscv64-linux-gnu-gdb) 在另一个窗口中，然后是“c”（继续）。当 内核似乎挂起，在 qemu-gdb 窗口中按 Ctrl-C 并输入 'bt' 获取回溯。



调试流程：所在目录`parallels@ubuntu-linux-22-04-02-desktop:~/xv6-labs-2020`

- Server终端：

  ```shell
  make (CPUS=1) qemu-gdb
  ```

- Client终端：

  ```shell
  gdb-multiarch kernel/kernel;
  target remote localhost:26000; #GDB内部
  ```
  
  

测试命令：

- `./grade-lab-util sleep`
- `make GRADEFLAGS=sleep grade`