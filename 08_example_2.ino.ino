
#define PIN_LED  9
#define PIN_TRIG 12  
#define PIN_ECHO 13  


#define SND_VEL 346.0   
#define INTERVAL 25     
#define PULSE_DURATION 10
#define _DIST_MIN 100.0   
#define _DIST_MAX 300.0  

#define TIMEOUT ((INTERVAL / 2) * 1000.0) 
#define SCALE (0.001 * 0.5 * SND_VEL)     // 지속 시간을 거리로 변환하는 계수

unsigned long last_sampling_time;   // 단위: msec

// USS에서 거리 값을 읽어오는 함수의 프로토타입 선언
float USS_measure(int TRIG, int ECHO);

void setup() {
  // GPIO 핀 초기화
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);  // 초음파 TRIGGER
  pinMode(PIN_ECHO, INPUT);   // 초음파 ECHO
  digitalWrite(PIN_TRIG, LOW);  // 초음파 센서 OFF
  
  // 시리얼 포트 초기화
  Serial.begin(57600);
  
  // 마지막 샘플링 시간 초기화
  last_sampling_time = millis();
}

void loop() {
  float distance;

  // 다음 샘플링 시간까지 대기
  // millis()는 프로그램이 시작된 이후의 밀리초를 반환합니다.
  // 50일 후에 오버플로우됩니다.
  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO); // 거리 읽기

  if ((distance == 0.0) || (distance > _DIST_MAX)) {
      distance = _DIST_MAX + 10.0;    // 높은 값 설정
      digitalWrite(PIN_LED, HIGH);    // LED OFF
  } else if (distance < _DIST_MIN) {
      distance = _DIST_MIN - 10.0;    // 낮은 값 설정
      digitalWrite(PIN_LED, HIGH);    // LED OFF
  } else {    // 원하는 범위 내
      digitalWrite(PIN_LED, LOW);     // LED ON      
  }

  // 거리를 시리얼 포트에 출력
  Serial.print("Min:");        Serial.print(_DIST_MIN);
  Serial.print(",distance:");  Serial.print(distance);
  Serial.print(",Max:");       Serial.print(_DIST_MAX);
  Serial.println("");
  
  // 마지막 샘플링 시간 업데이트
  last_sampling_time += INTERVAL;
}

// USS에서 거리 값을 읽어오는 함수. 반환 값은 밀리미터 단위입니다.
float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // 단위: mm

  // 펄스 지속 시간에서 거리 변환 예제 (목표 거리 = 17.3m)
  // - pulseIn(ECHO, HIGH, timeout)은 마이크로초 단위의 왕복 시간을 반환합니다.
  // - 편도 거리 = (pulseIn() / 1,000,000) * SND_VEL / 2 (미터 단위)
  //   mm 단위로 변환하려면 * 1,000이 필요 ==> SCALE = 0.001 * 0.5 * SND_VEL
  //
  // - 예: pulseIn()이 100,000이라면 (= 0.1초, 왕복 거리 34.6m)
  //        = 100,000 마이크로초 * 0.001 (밀리초로 변환) * 0.5 * 346 (음속)
  //        = 17,300 mm  ==> 17.3m
}
