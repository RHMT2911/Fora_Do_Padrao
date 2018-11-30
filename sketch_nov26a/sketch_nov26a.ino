int led = 12;
char comando;
void setup() {
pinMode(led, OUTPUT);
Serial.begin(9600);
  
}

void loop() {
while (Serial.available()) {
comando = Serial.read();

switch (comando){
  
  case 'L':
  if (digitalRead(led) == LOW){
  digitalWrite(led, HIGH);
  delay(20);
  }
  break;

  case 'D':
  if (digitalRead(led) == HIGH){
  digitalWrite(led, LOW); 
  delay(20);
  }
  break;

  default:
  digitalWrite(led, digitalRead(led)); 
  break;

  
}
}
}  

