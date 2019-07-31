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
  
 
## 引入新库

### ArduinoJson

在Library manager中搜索ArduinoJson并添加，作者是Benoit

https://arduinojson.org/

  
 
