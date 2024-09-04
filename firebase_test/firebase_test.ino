
#include <WiFi.h>
#include <FirebaseESP32.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define FIREBASE_HOST  "https://esp32-led-47e0e-default-rtdb.firebaseio.com/"                       //api key
#define FIREBASE_AUTH  "AIzaSyBv8IHyJvca_n9T_I0W2OeB1voEmAptHbs"                                    //db url
#define WIFI_SSID   "dtClass"
#define WIFI_PASSOWRD   "dlabdongtan"

#define LED_PIN     2           //내장LED

FirebaseData    firebaseData;
FirebaseAuth    auth;
FirebaseConfig  config;

bool signupOK = false;
unsigned long sendDataPrevMillis = 0;

void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Connecting WiFi: ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSOWRD);

    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi Connected");
    Serial.println("IP Address: ");
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    config.api_key = FIREBASE_AUTH;
    config.database_url = FIREBASE_HOST;

    if(Firebase.signUp(&config, &auth, "", "")) {
        Serial.println("ok");
        signupOK = true;
    }
    else {
        //Serial.println(config.signer.signupError.message.c_str());
    }

    config.token_status_callback = tokenStatusCallback;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    pinMode(LED_PIN, OUTPUT);

    if(Firebase.ready() && signupOK) {
        if(Firebase.RTDB.setInt(&firebaseData, "/ledState", 0)) {
            Serial.println("PASSED");
            Serial.println("PATH: "+firebaseData.dataPath());
            Serial.println("TYPE: "+firebaseData.dataType());
        }
        else {
            Serial.println("FAILED");
            Serial.println("REASON: "+firebaseData.errorReason());
        }
    }
}

void loop() {
  // Firebase.ready() 함수는 인증 작업을 처리하기 위해 반복적으로 호출되어야 합니다.
  if (Firebase.ready() && signupOK && \
  (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    // Firebase에서 LED 상태 가져오기
    int ledState = 0;
    if (Firebase.RTDB.getInt(&firebaseData, "/ledState")) {
      if (firebaseData.dataType() == "int") {
        ledState = firebaseData.intData();
        Serial.println(ledState);
        if (ledState == 1) {
          digitalWrite(LED_PIN, HIGH);
        } else {
          digitalWrite(LED_PIN, LOW);
        }
      }
    }
    else {
        Serial.println(firebaseData.errorReason());
    }
  }
}

