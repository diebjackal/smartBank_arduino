#include <SPI.h>
#include <RFID.h>

#define SDA_DIO 10
#define RESET_DIO 9

int productname[5] = {83, 218, 15, 46, 168};
int product[5] = {100, 120, 230, 125, 70};

char ID;
int Total;

byte i = 0;

RFID RC522(SDA_DIO, RESET_DIO);

void setup() {
  Serial.begin(9600);
  SPI.begin();

  RC522.init();
}

void loop() {
  if (RC522.isCard())
  {
    nfc();
  }
}

void nfc() {
  RC522.readCardSerial();
  ID = RC522.serNum[0];
  for (i = 0; i < 5; i++)
  {
    if (productname[i] == ID)
    {
      Serial.print("NFC Number : ");
      Serial.println(Total);
      if (token[i] == 0) {
        Total = Total + product[i];
        Serial.println("NFC tag");
        token[i] = 1;
      } else {
        Total = Total - product[i];
        token[i] = 0;
      }
      break;
    }
    else if (i == 5) {
      Serial.println("Access Denied");
      break;
    }
  }
  delay(200);
}
