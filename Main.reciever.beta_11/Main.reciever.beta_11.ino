int pos = 1;
void setup()
{
  pinMode(2,OUTPUT); //ra 
  pinMode(3,OUTPUT); //vao
  Serial.begin(9600);
}
void loop()
{
  int a = digitalRead(A0);

  if(a==1 and pos == 1) {digitalWrite(3,1); digitalWrite(2,0); pos = 2;}
  if(a==1 and pos == 2) {digitalWrite(3,0); digitalWrite(2,1); pos = 1;}

  Serial.print(pos);
  Serial.println(a);
}
