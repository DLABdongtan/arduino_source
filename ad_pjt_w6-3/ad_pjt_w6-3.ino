#include <WiFi.h>       //wifi라이브러리
#include <WebServer.h>  //웹서버 라이브러리

const char* ssid = "106-101";    //현재 접속한 wifi이름 입력
const char* password ="tc092312**"; //접속한 wifi 비밀번호 입력

WebServer server(80);     //*80포트를 사용해서 웹서버 객체 생성

void handleRoot() {
  //경로에 대한 요청을 처리하는 핸들러 
  server.send(200, "text/plain", "Hello ESP32");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);           //시리얼통신 초기화 
  WiFi.begin(ssid, password);     //wifi연결 
  Serial.println("Connected WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  //경로에 대한 요청을 handelRoot()함수로 처리.
  server.on("/", handleRoot);
  //Wi-Fi연결이 완료될 때 까지 대기
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected Info");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());   //IP주소 출력 

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();    //client요청 처리

}
