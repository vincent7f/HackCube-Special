# 必须安装的类库

* FastLED
* ArduinoJson


# 新增功能列表

## 小修改
* 删除Software/ESP8266_cn目录
* 删除webfiles.h文件。
  * 节省内存空间，加快刷写速度。
  * 改用/data/目录下的页面文件提供Web页面，需要使用ESP8266FS来上传/data/目录内的内容。ESP8266FS的官网:[https://github.com/esp8266/arduino-esp8266fs-plugin](https://github.com/esp8266/arduino-esp8266fs-plugin)。
* Webinterface.h
  * 增加了web的根路径的处理，即访问http://hackcube/　的默认页面为WIFI.html。
* ESP8266.ino
  * 改为使用ESP8266输出Serial.print()的调试信息。
    * 注释掉setup()中的Serial.swap()一行即可。
* /data/WIFI.html
  * 重新开放该页面。
  
## 新功能
* 全局参数由/data/config.json保存，通过Config.html页面管理，由Setup.html页面进入Config.html页面。
* WIFI AP的配置由/data/config.json文件控制。
* 设置灯光的最大值，在config.json文件中设置"led_brightness"为整数值。
* 访问/xxxx得到返回值yyyy，证明与AT板通信成功。
* 当点击NFC页面Read右侧开关时，清空NFC数据，清空后需要手动刷新NFC页面，否则表格中的数据不会自动清除。
* 支持通过HTTP请求reset/restart ESP8266.(Webinterface.h)
  * URI: /reset 或 /restart
  * reset和restart的区别：
    * ESP.reset() is a hard reset and can leave some of the registers in the old state which can lead to problems, its more or less like the reset button on the PC.
    * ESP.restart() tells the SDK to reboot, so its a more clean reboot, use this one if possible.
 
## 引入新库

### ArduinoJson

在Library manager中搜索ArduinoJson并添加，作者是Benoit

https://arduinojson.org/

  
 
