`.data`，`.text` ：ROM

`.bss`：RAM



任务切换硬件：

- 定时器``SysTick_Handler`：周期转换
- `SVC_Handler`和``PendSV_Handler`：专门做任务切换



栈：**满递增（C语言）**，满递减，空递增，空递减



全连接编译



是否从`reset_handler`开始运行

![image-20241210194736852](https://my-pic.miaops.sbs/2024/12/image-20241210194736852.png)



![image-20241210195502031](https://my-pic.miaops.sbs/2024/12/image-20241210195502031.png)

![image-20241210205359754](https://my-pic.miaops.sbs/2024/12/image-20241210205359754.png)