//라이브러리 가져오기
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

//서비스와 특성에 대한 UUID정의 - https://www.uuidgenerator.net 에서 복사 후 붙여넣기 
//아래 UUID영역에 ""안에 붙여넣기
#define SERVICE_UUID  "5725bae0-05e8-4db3-9c7c-0dcfda90c4ee"
#define RGB_CHARACTERISTIC_UUID "adde9a6b-7650-42d6-bd11-64aaf0ffe14c"
#define NOTIFY_CHARACTERISTIC_UUID  "0b4585f2-0cca-463a-8322-4391570f655a"

//RGB LED에 사용될 핀번호 
#define RED_PIN   4
#define GREEN_PIN 15
#define BLUE_PIN  2

//BLE객체 선언
BLEServer *pServer;        //BLE 서버객체
BLEService *pService;      //BLE 서비스객체
BLECharacteristic *pRGBCharacteristic = NULL;  //BLE RGB특성 객체
BLECharacteristic *pCharacteristic = NULL;     //BLE Notify특성 객체

//RGB값을 저장할 변수를 초기화
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

//BLE특성에 대한 콜백 클래스 정의
class MyCallbacks : public BLECharacteristicCallbacks {
  //특성 값을 읽어와서 RGB값을 파싱 후, LED를 제어한다.
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic -> getValue().c_str(); //특성값 읽어오기 

    //값이 유효한 경우에만 처리 
    if(value.length() > 0) {
      //RGB값을 파싱하여 각각의 변수에 저장 
      int delimiterPos1 = value.indexOf(',');
      int delimiterPos2 = value.lastIndexOf(',');

      if(delimiterPos1 != -1 && delimiterPos2 != -1 && delimiterPos2 < value.length()-1) {
        redValue = value.substring(0, delimiterPos1).toInt();
        greenValue = value.substring(delimiterPos1 + 1, delimiterPos2).toInt();
        blueValue = value.substring(delimiterPos2 + 1).toInt();

        //RGB값을 LED의 밝기로 변환하여 제어
        analogWrite(RED_PIN, 255-redValue);
        analogWrite(GREEN_PIN, 255-greenValue);
        analogWrite(BLUE_PIN, 255-blueValue);
      }
    }
  }
};

void setup() {
  BLEDevice::init("RGB LED Control");       //BLE초기화 및 이름을 RGB LED Control로 설정
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);

  //RGB특성 생성 및 설정
  pRGBCharacteristic = pService->createCharacteristic(RGB_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_WRITE);
  pRGBCharacteristic->setCallbacks(new MyCallbacks());

  //Notify Indicate특성 생성 및 설정
  pCharacteristic = pService->createCharacteristic(NOTIFY_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
  
  //BLE디스크립터 생성
  pCharacteristic->addDescriptor(new BLE2902());

  //서비스를 서버에 추가
  pService->start();

  //BLE ADVERTISING
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  //RGB값을 LED의 밝기로 변환하여 제어
  analogWrite(RED_PIN, 255 - redValue);
  analogWrite(GREEN_PIN, 255 - greenValue);
  analogWrite(BLUE_PIN, 255 - blueValue);
}

void loop() {
  //RGB값을 16진수 형태로 변환하여 Notify
  char hexValue[8];
  sprintf(hexValue, "#02X%02X%02X", redValue, greenValue, blueValue);

  //Notify특성의 값을 hexValue로 설정
  pCharacteristic->setValue(hexValue);
  
  //notify()통해 값을 전달
  pCharacteristic->notify();

  delay(100);   //알림 간격을 조정 
}