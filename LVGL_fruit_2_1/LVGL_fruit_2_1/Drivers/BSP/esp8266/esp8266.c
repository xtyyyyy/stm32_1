#include "./BSP/esp8266/esp8266.h"



void mqtt_init(void)
{
	fprintf(stderr,"AT+RST\r\n");//��λ
	delay_ms(1000);
	fprintf(stderr,"ATE0\r\n");//�رջ���
	delay_ms(1000);
	fprintf(stderr,"AT+CWMODE=3\r\n");//����˫ģʽ
	delay_ms(1000);
	fprintf(stderr,"AT+CWJAP=\"XTY\",\"88888888\"\r\n");//����WIFI������˺�
	delay_ms(2000);
	fprintf(stderr,"AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,\"\"\r\n",USERNAME,PASSWORD);//����MQTT��username��password
	delay_ms(2000);
	fprintf(stderr,"AT+MQTTCLIENTID=0,\"%s\"\r\n",CLIENTID);	//����CLIENTID
	delay_ms(2000);
	fprintf(stderr,"AT+MQTTCONN=0,\"%s\",1883,1\r\n",DOMAINNAME);//��������
	delay_ms(2000);
	
	
	fprintf(stderr,"AT+MQTTSUB=0,\"/%s/%s/user/get\",1\r\n",PRODUCTID,DEVICENAME);//����
	
	delay_ms(2000);
	fprintf(stderr,"AT+MQTTPUBRAW=0,\"/sys/%s/%s/thing/event/property/post\",%d,1,0\r\n",PRODUCTID,DEVICENAME,81);
	delay_ms(500);
	fprintf(stderr,"{\"params\":{\"temp\":15,\"Humd\":25,\"LightLux\":22,\"servo\":30,\"bump\":0,\"LEDSwitch\":1}}\r\n");//��Ϣ����
}
