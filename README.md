# iLock
入行智能门锁研发已经2年有余，接触了几款MCU、 ARM linux 系统，闲时整理智能门锁技术资料及个人经验

下面以Linux系统的人脸识别智能锁平台为例；

包括智能锁端、物联网平台、数据服务器、手机端微信小程序；

# 智能门锁功能

## 用例图

### 锁端
![](https://github.com/iToday/iLock/blob/master/images/%E6%99%BA%E8%83%BD%E9%94%81%E7%AB%AF%E7%94%A8%E4%BE%8B.png)

### 服务器端
![](https://github.com/iToday/iLock/blob/master/images/%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%AB%AF%E7%94%A8%E4%BE%8B.png)

### 手机端
![](https://github.com/iToday/iLock/blob/master/images/%E7%A7%BB%E5%8A%A8%E7%AB%AF%E7%94%A8%E4%BE%8B.png)

## 功能描述
|设备|	功能|	描述|	前提条件|
|:---|:-----|:---|:-------|
|智能锁端|	浏览账号|	管理员用户可查看当前门锁绑定的账号	|设备联网	|
||	绑定账号|	管理员用户通过手机APP扫描门锁二维码，关联门锁和手机账号|	设备联网	|
||	OTA升级	|检查服务器软件版本，并更新|	设备联网|	
||	解绑账号|	管理员用户可解除门锁与手机账号绑定|	设备联网	|
|移动终端|	注册登录|	注册手机端账号；通过账号登录服务器	||	
||	查看设备|	查看账号绑定的所有设备|	账号登录|	
||	绑定设备|	扫描设备二维码，绑定对应设备|	账号登录|	
||解绑设备|	解除设备绑定|	账号登录	|
||查看记录|	查看门锁开锁记录|	输入管理员密码	|
||管理用户|	查看、删除、修改门锁用户，添加门锁数字密码用户	|输入管理员密码	
||远程开锁	|输入开锁密码，遥控开锁|	1.输入开锁密码2.锁设备已联网	|
||	一键换锁|	恢复服务器数据，用户更换门锁不需重新录入用户，更改配置|	输入管理员密码|	
||	提醒报警|	设备异常时，服务器推送异常到移动终端，提醒用户采取相应措施|	绑定设备|	
||	无线配网|	手机端可直接配置智能锁WIFI网络的账号、密码，控制设备联网|	设备未联网	|
|服务器端|	查看在线设备|	可统计指定时间段的在线设备	||	
||	查看开锁记录|	查看指定设备的开锁记录||		
||	统计设备位置|	根据锁体IP地址统计锁分布区域	||	
||	重置设备|	支持远程重置锁体数据||		
||	更新升级包|	上传锁体升级包||		
||	统计升级记录|	统计锁体当前版本及更新记录	|	
||	推送更新|	推送更新到用户手机端，提醒用户更新锁体软件	||	

## 拓扑结构
下面是整个产品平台结构图

![](https://github.com/iToday/iLock/blob/master/images/%E6%8B%93%E6%89%91%E7%BB%93%E6%9E%84.png)

`智能设备`：智能门锁通过WIFI网络与服务器通信,智能锁进入低功耗时，自动断开网络，唤醒工作时，自动恢复网络连接；

`服务器`：保存智能设备数据和手机注册的账号数据；

`运维`：运维、客服人员通过专业软件操作服务器数据；


<font color=#00ffff >智能锁在低功耗模式时需要关闭网络模块，设备无法常在线；手机端远程操作时需要保证真能锁联网；每次联网后，将上报所有数据到服务器</font>



# 智能门锁架构

## OneNet云平台架构
![](https://github.com/iToday/iLock/blob/master/images/Linux%E7%B3%BB%E7%BB%9F%E6%99%BA%E8%83%BD%E9%94%81%E4%BA%91%E5%B9%B3%E5%8F%B0%E6%9E%B6%E6%9E%84%E5%9B%BE.png)
## 数据服务器架构
![](https://github.com/iToday/iLock/blob/master/images/%E6%95%B0%E6%8D%AE%E6%9C%8D%E5%8A%A1%E5%99%A8%E6%9E%B6%E6%9E%84.png)
## 智能锁架构
![](https://github.com/iToday/iLock/blob/master/images/linux%E6%99%BA%E8%83%BD%E9%94%81.png)


# 术语
`MQTT`：Message Queuing Telemetry Transport，消息队列遥测传输，是IBM推出的一种针对移动终端设备的基于TCP/IP的发布/预订协议，可以连接大量的远程传感器和控制设备，该协议支持所有平台，几乎可以把所有联网物品和外部连接起来，被用来当做传感器和制动器（比如通过Twitter让房屋联网）的通信协议。

`CoAP`：一种软件协议旨在用于非常简单的电子设备,让他们通过互联网交互通信，它运行于UDP协议之上而不是像HTTP那样运行于TCP之上，CoAP协议非常的小巧;

`关系型数据库`:是把复杂的数据结构归结为简单的二元关系（即二维表格形式）。在关系型数据库中，对数据的操作几乎全部建立在一个或多个关系表格上，通过对这些关联的表格分类、合并、连接或选取等运算来实现数据库的管理.

`时间序列数据库`:用于管理时间序列数据的专业化数据库。区别于传统的关系型数据库，
时序数据库针对时间序列数据的存储、查询和展现进行了专门的优化，从而获得极高
的数据压缩能力、极优的查询性能，特别适用于物联网应用场景。

`分布式数据库`:是指利用高速计算机网络将物理上分散的多个数据存储单元连接起来组成一个逻辑上统一的数据库。分布式数据库的基本思想是将原来集中式数据库中的数据分散存储到多个通过网络连接的数据存储节点上，以获取更大的存储容量和更高的并发访问量.

`SSL证书`：遵守SSL安全套接层协议的服务器数字证书，而SSL安全协议最初是由美国网景Netscape Communication公司设计开发，全称为安全套接层协议 (Secure Sockets Layer) 。
SSL证书指定了在应用程序协议（如HTTP、Telnet、FTP）和TCP/IP之间提供数据安全性分层的机制。它是在传输通信协议（TCP/IP）上实现的一种安全协议，采用公开密钥技术，它为TCP/IP连接提供数据加密、服务器认证、消息完整性以及可选的客户机认证。由于此协议很好地解决了互联网明文传输的不安全问题，很快得到了业界的支持，并已经成为国际标准。
SSL证书由浏览器中受信任的根证书颁发机构在验证服务器身份后颁发，具有网站身份 验证和加密传输双重功能。
