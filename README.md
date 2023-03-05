# 嵌入式课设——利用UDP通信控制实验箱  
编写于2023.3.5，要求自行参照课设要求。  
## 如何使用？
1. `./build_client.bash` 脚本编译控制端(将运行在电脑虚拟机上)  
2. `./build_server.bash` 脚本编译受控端(将运行在实验箱上)  
3. 将生成的remotectld传输到实验箱并运行  
4. 将生成的remotecli_x86在电脑虚拟机内运行
5. 在虚拟机上输入数字、ABCDEF后按回车，数码管将会显示输入的数字
6. 在虚拟机上输入V100，步进电机正转；输入H100，步进电机反转。100是速度，更小的数字会更慢  
7. 在虚拟机上输入I0，第一个LED灯亮/灭状态变化；I1对应第二个LED灯，以此类推，I3对应第四个LED灯  
## 验收答辩  
1. UDP是无连接的、双方对等的协议，因此UDP通信实现部分叫udp_peer  
2. 端口号用以在网络通信层面区分同一主机上的不同Socket。此项目使用的端口号在这里：[protocol.h#L32](https://github.com/developer-ken/ClassFinal_SimpleUDPRemoteController/blob/master/protocol.h#L32)  
  
验收答辩前请完整阅读程序，着重理解以下重点：
1. [udp_peer.c](https://github.com/developer-ken/ClassFinal_SimpleUDPRemoteController/blob/master/udp_peer.c)，UDP初始化、收、发和基于UDP广播的网络发现相关代码  
2. [protocol.c](https://github.com/developer-ken/ClassFinal_SimpleUDPRemoteController/blob/master/protocol.c)，网络通信协议，包含一个数据包的构成、打包、解包相关代码  
3. [Stepper.c](https://github.com/developer-ken/ClassFinal_SimpleUDPRemoteController/blob/master/hwdrivers/Stepper.c)，步进电机控制相关代码，用到了多线程(pthread)，仔细验收的话可能会问到  
4. 我能想到的就这些，其它的都比较简单，看造化吧
