#include <USBComposite.h>

//USBCompositeSerial CompositeSerial;

USBHID HID;

const uint8_t reportDescription[] = {
    HID_CONSUMER_REPORT_DESCRIPTOR(),
    HID_KEYBOARD_REPORT_DESCRIPTOR()};

HIDConsumer Consumer(HID);
HIDKeyboard Keyboard(HID);

void setup()
{
  Serial1.begin(250000);
  Serial3.begin(250000);
  Serial1.print("Hello----------");

  HID.begin(reportDescription, sizeof(reportDescription));

  Serial1.println("booting");
}

void loop()
{

  // //String command= "";
  // int command;
  // if (Serial3.available())
  // {

  //   command = Serial3.parseInt();
  //   String cmd = String(command);
  //   cmd.substring(0,4);
  //   //command.trim();
  //   Serial1.print(command);

  //   Consumer.press((uint8_t(command)));
  //   Consumer.release();
  // }


char deviceType[3];
  String subStr;
  String strCmd[4];
  
  if (Serial3.available())
  {
    size_t d = Serial3.readBytesUntil(':', deviceType, sizeof(deviceType) - 1);
    deviceType[d]= '\0';
    if (deviceType[0] == 'K') //Keyboard
    {
      String commands = Serial3.readStringUntil('*');
      Serial1.println(commands);
      Serial1.println(commands.length());
      Serial1.println("################");
      switch (commands.length())
      {
      case 8:
        strCmd[0] = commands.substring(0, commands.indexOf(':'));
        strCmd[1] = commands.substring(commands.indexOf(':')+1, commands.lastIndexOf(':') );
        strCmd[0].trim();
        strCmd[1].trim();

        Keyboard.press(uint8_t(strCmd[0].toInt()));
        Keyboard.press(uint8_t(strCmd[1].toInt()));
        Keyboard.releaseAll();
        break;
      case 10:
        strCmd[0] = commands.substring(0, commands.indexOf(':'));
        subStr = commands.substring(commands.indexOf(':')+1, commands.lastIndexOf(':'));
        strCmd[1] = subStr.substring(0, subStr.indexOf(':'));
        strCmd[2] = subStr.substring(subStr.indexOf(':')+1);
        
        strCmd[0].trim();
        strCmd[1].trim();
        strCmd[2].trim();

        Keyboard.press(uint8_t(strCmd[0].toInt()));
        Keyboard.press(uint8_t(strCmd[1].toInt()));
        Keyboard.press(strCmd[2].charAt(0));
        Keyboard.releaseAll();
        break;
      default:
        Serial1.println("Invalid");
        break;
      }
      
      Serial1.println();


    }

    if (deviceType[0] == 'C') //// Consumer---
    {
      Serial1.println(deviceType);
      int con = Serial3.parseInt();
      
      Serial1.println(uint8_t(con));
      Consumer.press(uint8_t(con));
      Consumer.release();
    }
  }


  delay(20);

}





