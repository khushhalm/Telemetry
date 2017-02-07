int s1 = 5,
    s2 = 6,
    s3 = 7;

int counter = 0,
    val1 = 0,
    val2 = 0,
    val3 = 0;

unsigned long timer = 0;

float a = 0,
      b = 0,
      c = 0,
      rpm = 0,
      rps = 0;

void setup() {
  Serial.begin(9600);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  Serial.println("This is The Telemetry System");
  delay(10);
}

void loop() {
  timer = millis();
  //Serial.println(timer);
  if (timer % 5000 == 0)
  {
    c = (timer / 1000);
    Serial.println(c);
    b = counter - a;
    a = counter;
    rps = ((b / 10) / 5);
    rpm = rps * 60;
    Serial.print("The rpm is ");
    Serial.println(rpm);
  }

  // put your main code here, to run repeatedly:
  val1 = digitalRead(s1);
  val2 = digitalRead(s2);
  val3 = digitalRead(s3);
  if (val1 == 1 && val2 == 0 && val3 == 0)
  {
    while (1)
    {
      val1 = digitalRead(s1);
      val2 = digitalRead(s2);
      val3 = digitalRead(s3);
      if ((val1 == 1 && val2 == 1 && val3 == 0) || (val1 == 0 && val2 == 1 && val3 == 0) || (val1 == 0 && val2 == 1 && val3 == 1) || (val1 == 0 && val2 == 0 && val3 == 1) || (val1 == 1 && val2 == 0 && val3 == 1))
      {
        counter++;
        //Serial.println(counter);
        break;
      }
    }
  }
}
