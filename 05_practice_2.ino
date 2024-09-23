// Define constants
const int LED_PIN = 8;    
const int BLINKS = 5;        
const int BLINK_DURATION = 200; 

void setup() {
  // Set the LED pin as output
//  pinMode(LED_PIN, OUTPUT);

  // Start the serial communication at 57600 baud rate
  Serial.begin(57600);
}

void loop() {

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); 
  delay(1000);

  for (int i = 0; i < BLINKS; i++) {
    digitalWrite(LED_PIN, LOW); 
    delay(BLINK_DURATION / 2);
    digitalWrite(LED_PIN, HIGH);
    delay(BLINK_DURATION / 2);
  }
  digitalWrite(LED_PIN, HIGH); 
  while (true) {} 
}
