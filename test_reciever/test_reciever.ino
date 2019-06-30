void setup() {
  Serial.begin(9600);
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);
  digitalWrite(30,1);
  delay(1000);
  digitalWrite(30,0);
}

void loop() {
  int a = digitalRead(A8);
  int b = digitalRead(A9);
  Serial.print(a);
  Serial.println(b);
}
