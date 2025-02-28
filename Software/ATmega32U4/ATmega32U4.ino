/*
                 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
               @@@@@@@@@                    @@@@
             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@@
            @@@@@   @@@@@@@@@@@@@@@@@@@@@@@   @@@@@
           @@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@   @@@@@
          @@@@@   @@@@@    @@@@@@@@@@@@@@@@@@   @@@@@
         @@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@
        @@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@
      @@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@@
     @@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@@
    @@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@@
    @@@@@                       @@@@@@@@@@@@@@@@@@@@  @@@@@
     @@@@@   @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@
      @@@@@   @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@@@
       @@@@@   @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@
         @@@@   @@@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@
          @@@@   @@@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@
           @@@@    @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@
            @@@@@   @@@@@@@@@@@@@@@@@   @@@@@@@@@@@
             @@@@@   @@@@@@@@@@@@@@@@@   @@@@@@@@@
              @@@@@                       @@@@@@@
               @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
                 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
       _                   _          _
      | |                 | |        | |
      | |__    __ _   ___ | | __ ___ | |__   _   _   ___
      | '_ \  / _` | / __|| |/ // __|| '_ \ | | | | / _ \
      | | | || (_| || (__ |   <| (__ | |_) || |_| ||  __/
      |_| |_| \__,_| \___||_|\_\\___||_.__/  \__,_| \___|

    Author: mobier
    Email: vxxwej@gmail.com
    Git repository: https://github.com/UnicornTeam/HackCube-Special
*/

long freq_cc1101 = 315000000; //设置CC1101默认监听频率
//long freq_cc1101 = 434000000; //设置CC1101默认监听频率
int rf_class = 1;//设置射频监听模式为固定码
#define Cube_PRINT  Serial1
#define Print_Time 350
unsigned long SerialLastTime;
String Cube_PRINT_data;
#include "HackCube.h"
#include "rf.h"
#include "hid.h"
#include "nfc.h"
#include "SerialCommunication.h"
HackCube hc;
void setup() {
  Cube_PRINT.begin(9600);//设置与ESP8266通信引脚
  delay(2000);
  hc.pinSetup();//初始化模块引脚
  delay(100);
  Cube_PRINT.println("Cubemini Runing...");
  cc1101_config();//配置CC1101 模块，默认监听freq_cc1101 变量中的频率
  delay(4);
  cc1101.PrintConfig();//输出CC 1101关键几个寄存器
  mySwitch.enableReceive(1);//设置mySwitch中断引脚，用于接收固定码信号
  //rf_class=2;
  //freq_cc1101=433920000;
  //RF433_Setup_rollcode();//滚动码CC1101 寄存器配置
  //cc1101_config();
  //Hackradio.enableReceive(RF315_att);//设置中断引脚，接收滚动码信号
  //rf24l01_SnifferSetup();//初始化nRF24L01模块，并打印寄存器数据
  NFC_Switch("on");
  
}
void loop() {

  //rf24Sniffer();//轮询nRF24L01缓存寄存器接收数据
  SnifferEM4100();//通过轮询EM4095的OUT输出引脚解码卡号数据
  //AttackEM4100();//根据指令去模拟/爆破EM4100系列卡片
  SerialCommunication(); //通过串口与ESP8266 进行通信交互数据
  //delay(500);
  /*
  if (rf_class == 1) {
    SnifferFixedCode();//嗅探固定码数据
  } else if (rf_class == 2) {
    SnifferRollcode();//嗅探滚动码数据
  }
  */
}
