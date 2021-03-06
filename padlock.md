# PadLock
挂锁常见的是一种无屏、无声音、只支持指纹开锁的便捷锁，目前大部分挂锁都支持蓝牙BLE功能；

支持手机APP通过蓝牙遥控操作；

# 挂锁功能



## 功能描述

|设备	|功能	|描述	|前提条件|
|:----|:-----|:------|:---|
|移动终端|	绑定设备|	绑定挂锁，一个账号可绑定多台挂锁|	设备蓝牙打开|	
||	解绑设备|	管理员用户可解除挂锁与手机账号绑定|	手机联网	|
||	查看信息|	查看设备的uuid,蓝牙MAC，电量，指纹录入个数，开关锁状态|	蓝牙已连接	|
||	一键开锁|	手机端可使用蓝牙钥匙一键打开挂锁|	设备蓝牙打开	|
||	新建钥匙|	对绑定的设备创建钥匙|	手机联网	|
||	删除钥匙|	删除自己创建的钥匙或别人分享给自己的钥匙|	手机联网	|
||	禁用钥匙|	禁用自己创建的钥匙|	手机联网|	
||	钥匙分享|	用户可通过微信分享自己创建的钥匙给其他微信好友|	手机联网|	
||	录入用户|	用户可根据手机端步骤提示录入用户|	蓝牙已连接	|
||	删除用户|	用户可删除挂锁用户|	蓝牙已连接	|
||	一键恢复|	用户可将挂锁一键恢复出厂状态|	蓝牙已连接	|
||	查看开锁记录|	查看绑定挂锁的开锁记录	|蓝牙已连接	|
	

## 功能流程

### 绑定设备

1.手机端进入小程序界面，搜索附近挂锁蓝牙并连接成功；</br>
2.小程序界面下点击绑定按钮，通过蓝牙发送绑定请求，并等待挂锁的授权结果；</br>
3.挂锁端收到绑定请求后，进入绑定模式，等待管理员指纹验证结果(若没有管理员直接返回授权成功)，验证通过返回授权绑定，其他情况则上报授权失败（超时10秒）；</br>
4.手机端根据授权结果给用户相应的提示</br>

![](https://github.com/iToday/iLock/blob/master/images/%E6%8C%82%E9%94%81-%E7%BB%91%E5%AE%9A%E8%AE%BE%E5%A4%87.png)

### 录入用户
在蓝牙连接成功后，用户点击添加用户：</br>
1.手机APP发送用户录入指令到挂锁，并提示用户采集指纹</br>
2.挂锁收到用户录入指令后，进入增加用户模式；</br>
3.挂锁采集到用户指纹后，上报录入进度到手机APP（超时时间10秒，10秒内没有采集到任何指纹或采集完成自动退出增加用户模式）;</br>
4.手机APP根据录入进度及错误码，引导用户操作，若进度 < 100,提示用户继续录入；若进度>= 100，提示录入完成；</br>

![](https://github.com/iToday/iLock/blob/master/images/%E6%8C%82%E9%94%81-%E5%BD%95%E5%85%A5%E7%94%A8%E6%88%B7.png)

### 一键开锁
用户使用蓝牙钥匙可快速打开挂锁，当用户点击蓝牙钥匙开锁时：</br>
1.手机端与服务器数据校验钥匙有效性，确认钥匙有效</br>
2.手机端蓝牙发送开锁命令给挂锁</br>
3.挂锁校验开锁命令中UUID，校验通过则开锁并上传开锁状态，否则上传开锁失败</br>
4.手机端根据上报状态更新界面提示</br>

![](https://github.com/iToday/iLock/blob/master/images/%E6%8C%82%E9%94%81-%E4%B8%80%E9%94%AE%E5%BC%80%E9%94%81.png)

### 开锁记录
可查看最近50次的开锁记录，没有连接蓝牙时查看服务器上的记录；连接蓝牙时，手机APP主动同步锁体上的记录数据；

下面是开锁记录同步流程</br>

![](https://github.com/iToday/iLock/blob/master/images/%E6%8C%82%E9%94%81-%E5%90%8C%E6%AD%A5%E5%BC%80%E9%94%81%E8%AE%B0%E5%BD%95.png)

注：上传完成的判断标准是数据中的记录总数<= 实际收到的记录数

### 一键恢复
前提：蓝牙连接成功
1.用户手机端输入设备的UUID；</br>
2.手机APP发送恢复出厂命令给挂锁</br>
3.挂锁收到恢复出厂命令后，校验UUID是否匹配；匹配则恢复出厂</br>
4.挂锁恢复出厂后，发送恢复出厂成功；其他返回失败（超时5秒）</br>


### 钥匙管理
钥匙管理完全由手机端APP实现；与锁体无关，只要锁体支持开关锁控制；</br>
#### 新建钥匙
只有绑定了设备，才有权限创建对应设备的钥匙；</br>
#### 分享钥匙
注：蓝牙钥匙只能分享一次，客户拿到分享的钥匙，不可再次分享给其他人</br>
#### 禁用钥匙
只有钥匙创建者才有权限禁用钥匙；禁用后，所有使用者都无法使用此钥匙；</br>
#### 删除钥匙
删除钥匙分删除自建钥匙和他建钥匙；</br>

自建钥匙：删除钥匙时，分享出去的钥匙都会失效</br>
他建钥匙：删除钥匙时，只是把本账号下的钥匙信息删除；钥匙创建者及其他使用者都还有效；</br>

