// 변기 뚜껑 여닫기 / 청소하기 관련 코드
#define TCRT5000 A0
#include <Servo.h>

Servo servo;         // 뚜껑 서보

// 수정사항
/*
서보모터 1-1 : pin 12
서보모터 1-2 : pin 11
서보모터 2 : pin 10
시트 open/close 버튼 : pin 9
시트 앉음 감지 버튼 : pin 8
적외선 센서: pin 1

*/
/* 영민님 변수 시작 */
int SEAT = 2;         // 시트 압력스위치
int SWUP = 3;         // 시트 올림
int SWDN = 4;         // 시트 내림
int sensor = 7;       // 센서 신호핀
int lednormal = 8;    // 평소상태 표시 LED
int ledready = 9;     // 뚜껑열린 상태 표시 LED 
int leduv = 12;       // 사용후 적외선 소독기 LED
int pirState = LOW;   // 센서 초기상태는 움직임이 없음을 가정
int val = 0;          // 센서 신호의 판별을 위한 변수
int sen;              // 시트 상태판별을 위한 변수:SEAT
int sw_up;            // 시트 올림을 위한 변수:SWUP
int sw_dn;            // 시트 내림을 위한 변수:SWDNServo servo;         // 뚜껑 서보
Servo servo2;         // 시트 서보
int SEAT = 2;         // 시트 압력스위치
int SWUP = 3;         // 시트 올림
int SWDN = 4;         // 시트 내림
int sensor = 7;       // 센서 신호핀
int lednormal = 8;    // 평소상태 표시 LED
int ledready = 9;     // 뚜껑열린 상태 표시 LED 
int leduv = 12;       // 사용후 적외선 소독기 LED
int pirState = LOW;   // 센서 초기상태는 움직임이 없음을 가정
int val = 0;          // 센서 신호의 판별을 위한 변수
int sen;              // 시트 상태판별을 위한 변수:SEAT
int sw_up;            // 시트 올림을 위한 변수:SWUP
int sw_dn;            // 시트 내림을 위한 변수:SWDN
/* 영민님 변수 끝 */

int _servoAngle = 0; // 서보모터 1 각도 

int _personLeaveTime = 0; // 사람이 얼마나 감지되지 않았는지 저장하는 변수
int _personLeaveTimeInt = 5; // 사람이 몇 초 감지되지 않았을 때 뚜깡이 닫힐지
int _isCoverOpen = false; // 커버가 열려있는 상태인지

void setup() 
{
  Serial.begin(9600); // 9600bps로 시리얼 통신 시작
  pinMode(TCRT5000, INPUT); // 센서를 입력으로 설정

  // 영민님 초기화 부분
  servo.attach(5);            // 뚜껑 서보모터 지정
  servo2.attach(6);            // 시트 서보모터 지정
  pinMode(lednormal, OUTPUT);  // 평소상태 LED를 출력으로 설정
  pinMode(ledready, OUTPUT);   // 뚜껑열린상태 LED를 출력으로 설정
  pinMode(leduv,OUTPUT);       // 적외선 소독 LED를 출력으로 설정
  pinMode(sensor, INPUT);      // 인체감지 센서를 입력으로 설정
  pinMode(SEAT,INPUT);         // 시트 압력 스위치를 입력으로 설정
  pinMode(SWUP,INPUT);         // 시트 올림 스위치를 입력으로 설정
  pinMode(SWDN,INPUT);         // 시트 내림 스위치를 입력으로 설정servo.attach(5);            // 뚜껑 서보모터 지정
  servo2.attach(6);            // 시트 서보모터 지정
  pinMode(lednormal, OUTPUT);  // 평소상태 LED를 출력으로 설정
  pinMode(ledready, OUTPUT);   // 뚜껑열린상태 LED를 출력으로 설정
  pinMode(leduv,OUTPUT);       // 적외선 소독 LED를 출력으로 설정
  pinMode(sensor, INPUT);      // 인체감지 센서를 입력으로 설정
  pinMode(SEAT,INPUT);         // 시트 압력 스위치를 입력으로 설정
  pinMode(SWUP,INPUT);         // 시트 올림 스위치를 입력으로 설정
  pinMode(SWDN,INPUT);         // 시트 내림 스위치를 입력으로 설정
  
}

// 코드 최대한 읽기 쉽게 짜야함 ㅜ..
void loop() 
{
  int TCRT5000value = analogRead(TCRT5000); // 센서를 읽어서 value에 저장
//  Serial.println("센서 값: ");
//  Serial.println(TCRT5000value); // value값 출력 

  if (TCRT5000value > 1000) { //인체 감지
    _personLeaveTime = 0;
    openCover ();
    setIsCoverOpen (true); // 커버 열린 상태로 초기화
  }
  else { // 인체 비감지
    _personLeaveTime ++;
    delay (1000);
  }

  if (_personLeaveTime > _personLeaveTimeInt) {
    _persionLeaveTime = 0;
    closeCover ();
    cleanCover (); // 뚜껑이 닫히면 커버를 청소한다
    setIsCoverOpen (false); // 커버 닫힌 상태로 초기화 
  }
  
  delay(100);
}
// 뚜껑 닫는 함수
void closeCover () {
  // for문 쓰는건 부하방지를 위해
  for (_servoAngle = ; i >= 0 ; _servoAngle--) { // 뚜껑이 닫힌
    servo.write(_servoAngle);
//    delay(40);
  }
}
// 뚜껑 여는 함수
void openCover () {
  // for문 쓰는건 부하방지를 위해
  if (!_isCoverOpen) {
    for (_servoAngle; i < 120 ; _servoAngle++) { // 뚜껑이 열린다
      servo.write(_servoAngle);
      delay(40);
    }
  }
}
void cleanCover () {
  // 아직 어떤식으로 움직여야할지, 어떤 부품을 쓰는지 파악이 안돼서 안짰다 ㅠ_ㅠ
}
void setIsCoverOpen (bool status) {
  _isCoverOpen = status;

  if (_isCoverOpen) {
    
  }
  else {
    
  }
}
