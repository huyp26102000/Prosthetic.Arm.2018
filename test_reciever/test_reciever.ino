void setup() {
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,1);
  delay(2000);
  digitalWrite(11,0);
}

void loop() {
  int a = digitalRead(A6);
  int b = digitalRead(A7);
  Serial.print(a);
  Serial.println(b);
}
