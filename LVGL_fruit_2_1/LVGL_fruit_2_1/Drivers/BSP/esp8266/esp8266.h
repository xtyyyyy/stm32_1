#ifndef _ESP8266_H
#define  _ESP8266_H
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"

#define USERNAME   "test1&k266fnG1Vi1" //用户名
#define PASSWORD   "E764A69EE7F1010D2D91EC92469533A78DC007EF" //密码
#define CLIENTID   "test1|securemode=3\\,signmethod=hmacsha1|" //设备名称
#define PRODUCTID  "k266fnG1Vi1" //产品ID
#define DOMAINNAME "k266fnG1Vi1.iot-as-mqtt.cn-shanghai.aliyuncs.com" //域名
#define DEVICENAME "test1"

void mqtt_init(void); 



#endif /*ESP8266_H*/

