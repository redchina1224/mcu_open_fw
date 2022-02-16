<font size=15>小家电智能控制器开发平台<br/>MCU开源开发框架</font>
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

