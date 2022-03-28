<font size=15>小家电智能控制器开发平台<br/>低端MCU开源开发框架</font>
<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>

## **Mcu-Open-Framework     V0.10**
<br/>
当前适配 CMSIDE，FMDIDE，KEILC51。
<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
<font size=5>发布日期 2021-12-09</font>
<br/>

<table>
<tr>
<td><font size=5></font></td>
<td  rowspan="3"><font size=6>发布</font></td>
</tr>
<tr></tr>
<td><font size=5></font></td>
</tr>
</table>
<div STYLE="page-break-after: always;"></div>

## **发布说明：**
<table>
<tr>
<td>发布日期</td>
<td>版本</td>
<td>版本说明</td>
<tr>
<td>2021-02-10</td>
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

## **一、开发框架介绍：**
暂无
<div STYLE="page-break-after: always;"></div>

## **二、文件目录介绍：**
#### NTC模块：./drv/ntc

- NTC__xxK_Bxxxx目录：

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
  
#### RTC模块：./drv/rtc

- softrtc目录：

  软件RTC时钟实现，rtc时间产生，运行时间标志位产生，依赖 125uS 定时中断来实现

- defineRtc_drv.h

  定义配置参数值，当新增可选RTC实现时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- loadRtc_drv.h

  根据项目配置中定义的RTC，载入对应的实现函数头文件。
  
#### KEY模块：./drv/key

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

  单路按键信号检测与触发标志位产生处理，依赖以上的各类按键信号接口方案。
  
- key_Multichannel_drv 与 key_Multichannel_drv.h

  单路按键信号检测与触发标志位产生处理，依赖以上的各类按键信号接口方案。
  
#### INTERRUPT模块：./drv/inputerrupt

- interrupt_drv.c 与 interrupt_drv.c：

  MCU中断服务函数的集合，很多功能依赖该函数实现其功能。
  
#### DISPLAY模块：./drv/display

- softled目录：

  类LED数码管显示驱动的软件实现，推荐依赖 125uS 定时中断来实现，防止闪烁。

- softled_bits目录：

  类流水灯的软件实现，可实现流水灯,柱状充电等效果。

- defineDisplay_drv.h

  定义配置参数值，当新增可选Display实现时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- loadDisplay_drv.h

  根据项目配置中定义的Display，载入对应的实现函数头文件。

#### BUZZER模块：./drv/buzzer

- buzzer目录：

  常规蜂鸣器驱动的软件实现，包含GPIO型、定时中断取反型、PWM输出型，其中定中断取反型依赖 125uS 定时中断来实现，PWM输出型依赖MCU硬件PWM功能。

- defineBuzzer_drv.h

  定义配置参数值，当新增可选Buzzer实现时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- loadBuzzer_drv.h

  根据项目配置中定义的Buzzer，载入对应的实现函数头文件。

#### MOTOR模块：./drv/motor

- stepmotor目录：

  四相直流步进电机驱动的软件实现。

- defineMotor_drv.h

  定义配置参数值，当新增可选Motor实现时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- loadMotor_drv.h

  根据项目配置中定义的Motor，载入对应的实现函数头文件。
  
#### sensor模块：./drv/sensor

- sensor目录：

  常规标志位型传感器的软件实现,可实现IO型传感器和AD阀值型传感器防抖和标志位处理。

- defineSensor_drv.h

  定义配置参数值，当新增可选Sensor实现时必须在此文件同步更新相应的定义值，以便在项目中可通过该定义值配置使用

- loadSensor_drv.h

  根据项目配置中定义的Sensor，载入对应的实现函数头文件。
