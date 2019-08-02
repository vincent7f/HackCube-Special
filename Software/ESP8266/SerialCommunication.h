String Serial_data;
String input_data;
String serial_log;

void SerialCmd(){
  while (Serial.available() > 0) {
    Serial_data += char(Serial.read());
    delay(4);
  }

  serial_log += Serial_data;
  //serial_log = "";
  
  if (Serial_data.length() > 0) {
    //Serial.print("input serial data: ");
    //Serial.println(Serial_data);
    if (Serial_data.substring(1, 3) == "RF") {
      serial_log += "RF";
      
      if (int(Serial_data.indexOf("Jam")) > 0) {
        rf_jam = Serial_data.substring(9, Serial_data.indexOf('\n') - 1);
      } else if (int(Serial_data.indexOf("Sniffer")) > 0) {
        if (int(Serial_data.indexOf("rf24l01")) > 0) {
        } if (int(Serial_data.indexOf("keeloq")) > 0) {
          
        }else {
          AddRfList(Serial_data);
        }
        ajaxData_rf = Serial_data.substring(Serial_data.indexOf("data") + 5, Serial_data.indexOf('\n') - 1);
        LED_STATE(LED_DATA, true);
      } else if (int(Serial_data.indexOf("Progress")) > 0) {
        rf_prog = Serial_data.substring(14, Serial_data.length()).toInt();
        if (rf_prog == "100")
          LED_STATE(LED_RUN);
      }
    } else if (Serial_data.substring(1, 4) == "NFC") { //NFC
      serial_log += "NFC";
            
      if (int(Serial_data.indexOf("progress")) > 0) {
        nfc_prog = Serial_data.substring(15, Serial_data.length()).toInt();
        if (nfc_prog.toInt() > 100)
          nfc_prog = "100";
        if (nfc_prog == "100")
          LED_STATE(LED_RUN);
      } else if (int(Serial_data.indexOf("read")) > 0) {
        Add_NFC(Serial_data);
        ajaxData_nfc = Serial_data.substring(Serial_data.indexOf("data") + 5, Serial_data.length());
        LED_STATE(LED_DATA, true);
      }
    } else if (Serial_data[0] == 0x63) {
      serial_log += "0x63";
            
      ajaxData_rf_24l01 = Serial_data.substring(Serial_data.indexOf("data") + 5, Serial_data.length());
      LED_STATE(LED_DATA, true);
    //} else if (int(Serial_data.indexOf("yyyy")) > 0) {
    //  CONFIG_DOC["xxxx"]="yyyy";
    } else {
      serial_log += "ERROR";
      //Serial.print("error:");
      //Serial.println(Serial_data[0], HEX);
    }
    input_data = Serial_data; 
    Serial_data = "";
  }
}
