<font size=15>小家电智能控制器开发平台<br/>低端MCU开源开发框架</font>
<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>

## **Mcu-Open-Framework     V0.11**
<br/>
当前适配 CMSIDE，FMDIDE，HDIDE，KEILC51。
<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
<font size=5>发布日期 2022-10-14</font>
<br/>

<table>
<tr>
<td><font size=5>嘉兴慕链信息技术有限公司</font></td>
<td  rowspan="5"><font size=6>发布</font></td>
</tr>
<tr></tr>
<tr>
<td><font size=5>浙江智达电子科技有限公司</font></td>
</tr>
<tr></tr>
<tr>
<td><font size=5>浙江智雄智能科技股份有限公司</font></td>
</tr>
</table>
<div STYLE="page-break-after: always;"></div>

## **发布说明：**
<table>
<tr>
<td>发布日期</td>
<td>版本</td>
<td>版本说明</td>
</tr>
<tr>
<td>2022-10-14</td>
<td>V0.11</td>
<td><ul>
<li>添加新增功能信息,调整内容为文件夹字母顺序</li>
</ul></td>
</tr>
<tr>
<td>2022-02-10</td>
<td>V0.10</td>
<td><ul>
<li>预览发布版本V0.10</li>
</ul></td>
</tr>
<tr>
<td>----/--/--</td>
<td>V-.-</td>
<td><ul>
<li>---</li>
</ul></td>
</tr>
</table>

<div STYLE="page-break-after: always;"></div>

## **目录：**
暂无
<div STYLE="page-break-after: always;"></div>

## **一、开发框架库介绍：**
暂无
<br>

项目中部份代码来自IC及IDE供应商或其合作伙伴，代码版权归其所有
在此不一一例举，具体可参看相关文件头部版权信息，
部份移植合并代码及函数或参考的开源代码，由于疏忽可能考虑不周可能会丢失相关版权信息，如有问题可以联系我 13615737172 ，万分抱歉。

<div STYLE="page-break-after: always;"></div>

## **二、开发框架库目录介绍：**

### *<u>开发框架库文件目录结构*</u>
<pre>
mcu_open_fw
├─app
│  ├─appdefault
│  └─general
├─core
│  ├─byd
│  ├─cms
│  ├─fmd
│  ├─hd
│  ├─soc
│  ├─stc
│  └─wxjz
└─drv
    ├─buzzer
    ├─counter
    ├─display
    ├─interrupt
    ├─key
    ├─motor
    ├─ntc
    ├─poweroffcheck
    ├─rtc
    ├─scr
    ├─sensor
    └─zerocross
</pre>

<div STYLE="page-break-after: always;"></div>

### *<u>内核驱动：mcu_open_fw/core*</u>
#### 比亚迪MCU内核专用驱动：mcu_open_fw/core/byd

- byd_core.h：

  比亚迪BF7512DMXXf单片机标准化头文件及标准接口宏定义

#### 中微MCU内核专用驱动：mcu_open_fw/core/cms

- touch_79ft73x目录：

  中微79f738，79ft738触摸库及相关集成代码
  
- cms_core.h：

  中微79f单片机标准化头文件及标准接口宏定义
  
- cms80f_core.h：

  中微80f的C51单片要m标准化头文件及标准接口宏定义

#### 辉芒微MCU内核专用驱动：mcu_open_fw/core/fmd

- FT62F13X目录：

  辉芒微FT62F13X触摸库及相关集成代码
  
- fmd_core.h：

  辉芒微单片机标准化头文件及标准接口宏定义

#### 汉达MCU内核专用驱动：mcu_open_fw/core/fmd

- hd_core.h：

  汉达单片机标准化头文件及标准接口宏定义

#### 赛元微MCU内核专用驱动：mcu_open_fw/core/soc

- soc_core.h：

  赛元微单片机标准化头文件及标准接口宏定义

<div STYLE="page-break-after: always;"></div>

### *<u>外设驱动：mcu_open_fw/drv*</u>
#### BUZZER模块：mcu_open_fw/drv/buzzer

- buzzer目录：

  常规蜂鸣器驱动的软件实现，包含有源GPIO型、无源定时中断取反型、PWM输出型，其中定时中断取反型依赖 125uS 定时中断来实现，PWM输出型依赖MCU硬件PWM功能。

- defineBuzzer_drv.h

  定义配置参数值，当新增可选Buzzer实现时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- loadBuzzer_drv.h

  根据项目配置中定义的Buzzer，载入对应的实现函数头文件。
  
#### COUNTER模块：mcu_open_fw/drv/counter

- defineCounter_drv.h

  定义配置参数值，目前只支持中断中电平检测方式的软件计数器

#### DISPLAY模块：mcu_open_fw/drv/display

- ic_led目录：

  段码式led驱动芯片相关驱动代码。
  
- ic_lcd目录：

  段码式lcd驱动芯片相关驱动代码。
  
- softled_bits目录：

  类流水灯的软件实现，可实现流水灯,柱状充电等效果。
  
- softled_dig8目录：

  类LED数码管显示驱动的软件实现，推荐依赖 125uS 定时中断来实现，防止闪烁。

- softled_dig8_bidir目录：

  类LED数码管显示正反并联发光管驱动的软件实现，推荐依赖 125uS 定时中断来实现，防止闪烁。
  
- softled_dig8_withkeys目录：

  类LED数码管显示驱动的软件实现合并按键检测,仅针对特定电路的按键检测方式,暂不作说明，待有更通用的方案再进行整理说明，推荐依赖 125uS 定时中断来实现。
  
- defineDisplay_drv.h

  定义配置参数值，当新增可选Display实现时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- loadDisplay_drv.h

  根据项目配置中定义的Display，载入对应的实现函数头文件。
#### INTERRUPT模块：mcu_open_fw/drv/inputerrupt

- interrupt_drv.c 与 interrupt_drv.c：

  MCU中断服务函数的集合，很多功能依赖该函数实现其功能。
  
#### KEY模块：mcu_open_fw/drv/key

- irkey目录：

  红外遥控协议按键信号接收的实现，依赖 125uS 定时中断来实现

- rfkey目录：

  射频遥控协议按键信号接收的实现，依赖 125uS 定时中断来实现

- mcutouch目录：

  MCU自带的触摸按键接口标准化，依赖相应单片机触摸库及配置文件来实现
  
- others目录：

  其他无法归类为上述按键方案的驱动接口，如专用IC等，依赖相应接口方式如IIC,SPI,UART等


- defineKey_drv.h

  定义配置参数值，当新增可选KEY实现时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- loadKey_drv.h

  根据项目配置中定义的Key，载入对应的实现函数头文件。
  
- key_drv.c 与 key_drv.h

  单类型按键信号检测与触发标志位产生处理，依赖以上的各类按键信号接口方案，此方案不再更新支持，推荐使用后面的key_Multichannel_drv来实现，以实现后续更好的兼容。
  
- key_Multichannel_drv 与 key_Multichannel_drv.h

  多类型按键信号检测与触发标志位产生处理，依赖以上的各类按键信号接口方案。
  
#### MOTOR模块：mcu_open_fw/drv/motor

- stepmotor目录：

  四相直流步进电机驱动的软件实现。

- defineMotor_drv.h

  定义配置参数值，当新增可选Motor实现时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- loadMotor_drv.h

  根据项目配置中定义的Motor，载入对应的实现函数头文件。
  
#### NTC模块：mcu_open_fw/drv/ntc

- NTC_xxK_Bxxxx目录：

  存放对应B值和K值的阻值宏定义文件及相关参考资料，宏定义值单位为KR
```c
  #define NtcResVal_at23        109.3221
  #define NtcResVal_at24        104.5415
  #define NtcResVal_at25        100
```
  如上示例表示该NTC在23摄氏度时电阻值为 109.3221KR，在24摄氏度电阻值为104.5415KR，在25摄氏度时电阻值为100KR

- defineNtcRes_drv.h

  定义配置参数值，当新增可选NTC时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- ntc_adcval_calc.h

  根据上下拉电阻等参数计算对应温度时ADC，该文件在loadNtcRes_drv.h被include方式引用。

- loadNtcRes_drv.h

  根据项目配置中定义的NTC，载入对应的阻值宏定义文件，并调用ntc_adcval_calc.h计算对应温度时ADC值，用于定义温度ADC值常量表。

- ntc_table.c

  温度ADC值常量数组表，数值由loadNtcRes_drv.h中调用ntc_adcval_calc.h计算而来，项目配置中的TEMPTABLE_BUFFER_LENGTH决定该常量数组表的长度，TableValueTyp决定该常量数组表的数据类型。该文件由ntc_sensor.c通过include方式引用。

- ntc_sensor.c

  与NTC应用相关的功能函数，可实现ADC值转换为摄氏温度，以温度值获取ADC值，摄氏温度转换为华氏温度。

- ntc_sensor.h

  定义ntc_sensor.c的外部接口函数。
  
#### POWEROFFCHECK模块：mcu_open_fw/drv/poweroffcheck

- definePowerOffCheck_drv.h

  定义配置参数值，目前只支持单片机LVD方式的掉电检测
  
#### RTC模块：mcu_open_fw/drv/rtc

- softrtc目录：

  软件RTC时钟实现，rtc时间产生，运行时间标志位产生，依赖 125uS 定时中断来实现

- defineRtc_drv.h

  定义配置参数值，当新增可选RTC实现时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- loadRtc_drv.h

  根据项目配置中定义的RTC，载入对应的实现函数头文件。
  
#### SCR模块：mcu_open_fw/drv/scr

可控硅导通角计算模块(暂未启用)

#### sensor模块：mcu_open_fw/drv/sensor    (请使用app/general/signalfiltering替代)

- sensor目录：

  常规标志位型传感器的软件实现,可实现IO型传感器和AD阀值型传感器防抖和标志位处理。

- defineSensor_drv.h

  定义配置参数值，当新增可选Sensor实现时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- loadSensor_drv.h

  根据项目配置中定义的Sensor，载入对应的实现函数头文件。
  
#### ZEROCROSS模块：mcu_open_fw/drv/zerocross

- defineZerocross_drv.h

  定义配置参数值，目前只支持单片机IO方式的过零检测
  
<div STYLE="page-break-after: always;"></div>

### *<u>应用模块：mcu_open_fw/app*</u>

#### 可共用的通用应用代码：mcu_open_fw/app/general

- intervalwork目录：

  间隔工作代码，某些需要间隔工作的负载控制如5秒开6秒关循环控制等

- pid目录：

  pid通用算法代码,代码较大,并且仍需调校通用性，如测试效果没有很大改善，建议慎用。

- settingdisplayblink目录：

  设置过程代码，实现了进入设置闪烁，改变值时不闪烁，设置超时自动退出等功能
  
- signalfiltering目录：

  信号滤波代码,实现开关信号防抖检测，模拟信号双向开路短路故障检测等
  
- valcheck目录：

  数值合规检测代码,实现数值的限幅，用于数据初始化后合规检测。

<div STYLE="page-break-after: always;"></div>

## **三、项目文件目录介绍：**

### *<u>示例项目文件夹根目录结构：project*</u>

<pre>
project
├─cd_2600
│  ├─config
│  ├─inc
│  ├─src
│  └─cd_2600.uvproj
├─mcu_open_fw （开发框架库文件夹，这里不再展开）
└─project.h
</pre>

<div STYLE="page-break-after: always;"></div>

### *<u>以产品名称命名的用户项目代码目录：project/cd_2600*</u>
#### 用户项目代码配置文件：project/cd_2600/config

- project_cfg.h​ 文件：

  对项目采用的MCU，开发平台，需要载入的板级、应用、用户定应头文件，进行配置

- board_cfg.h 文件：

  对板级资源进行配置，定义端口，及相关端口应用类型。

- displayCode.h​ 文件：

  定义数码管段码显示编码
  
#### 用户项目代码头文件：project/cd_2600/inc

  存放用户代码的头文件。

#### 用户项目代码源文件：project/cd_2600/src

- board.c​ 文件：

  板级资源初始化和统一应用控制接口

- display.c​ 文件：

  数码显示缓存及相关显示控制接口

- main.c​ 文件：

  用户功能逻辑代码
  
#### 用户项目工程文件：project/cd_2600/cd_2600.uvproj

- cd_2600.uvproj​ 文件：

  项目工程文件，不同的IDE会有不同的工程文件后缀
  
#### 开发框架库：project/mcu_open_fw

  直接拷贝所需版本的开发框架库。

#### 项目配置文件指向文件：project/project.h

  - project.h​ 文件：

  直接include指定项目的 project_cfg.h​ 文件，用于给开发框架提供项目配置信息

```c
#ifndef __PROJECTSET_H_
#define __PROJECTSET_H_

#include "cd_2600\config\project_cfg.h"

#endif
```

