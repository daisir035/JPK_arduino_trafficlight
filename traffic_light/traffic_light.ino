const int TrigPin = A2; // Set the trig pin position of the sensor
const int EchoPin = A3; // Set the echo pin position of the sensor

const int TrigPin2 = 2; // Set the trig pin position of the sensor
const int EchoPin2 = 3; // Set the echo pin position of the sensor

// Set the LED pin position
const int LED_G1 = 4;  // green light in main road
const int LED_Y1 = 5;  // yellow light in main road
const int LED_R1 = 6;  // red light in main road
const int LED_G2 = 8;  // green light in sider road
const int LED_Y2 = 9;  // yellow light in sider road
const int LED_R2 = 10; // red light in sider road

// float type variable to store the distance in main road
float cm;
float cm2;

int mroad = 1;   // main road switch
int counter = 0; // sider road open counter
float dis = 10;  // the distance to change the light

void setup()
{

  Serial.begin(9600); // Set the baud rate

  pinMode(TrigPin, OUTPUT); // Set the trig pin as output
  pinMode(EchoPin, INPUT);  // Set the echo pin as input
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  // Set the LED pin as output
  pinMode(LED_G1, OUTPUT);
  pinMode(LED_R1, OUTPUT);
  pinMode(LED_Y1, OUTPUT);

  pinMode(LED_G2, OUTPUT);
  pinMode(LED_R2, OUTPUT);
  pinMode(LED_Y2, OUTPUT);
  // turn the LED on in turn (HIGH is the voltage level)
  digitalWrite(LED_G1, HIGH); // keep the green light in main road on
  delay(300);
  digitalWrite(LED_Y1, HIGH);
  delay(300);
  digitalWrite(LED_Y1, LOW);
  digitalWrite(LED_R1, HIGH);
  delay(300);
  digitalWrite(LED_R1, LOW);
  digitalWrite(LED_G2, HIGH);
  delay(300);
  digitalWrite(LED_G2, LOW);
  digitalWrite(LED_Y2, HIGH);
  delay(300);
  digitalWrite(LED_Y2, LOW);
  digitalWrite(LED_R2, HIGH); // turn the red LED in sider road on
}

void loop()
{
  // Sensor data reading and printing

  digitalWrite(TrigPin, LOW);  // pulse the trig pin to start the measurement
  delayMicroseconds(2);        // wait for 2 microseconds
  digitalWrite(TrigPin, HIGH); // set the trig pin high for 10 microseconds
  delayMicroseconds(10);       // wait for 10 microseconds
  digitalWrite(TrigPin, LOW);  // set the trig pin low
  Serial.print("mainroad:");
  cm = pulseIn(EchoPin, HIGH) / 58.0; // measure the distance in cm
  Serial.print(cm);                   // print the distance
  Serial.print("cm");                 // print the unit
  Serial.println();                   // print a new line

  digitalWrite(TrigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin2, LOW);
  cm2 = pulseIn(EchoPin2, HIGH) / 58.0;
  Serial.print("siderroad:");
  Serial.print(cm2);
  Serial.print("cm");
  Serial.println();

  //

  if (cm2 < dis && mroad == 1 && cm > dis) // if the mainroad open and there is no car in main road and there is car in sider road change light
  {
    mroad = 0;
    changemainroad();
    counter = 0;
  }

  if (cm2 >= dis && mroad == 0 || cm < dis && mroad == 0) // if there is no car in sider road or there is car in main road change light
  {
    mroad = 1;
    changeSideroad();
    counter = 0;
  }

  if (mroad == 1 && cm2 < dis && cm < dis) // if there is car in both road count the time
  {
    counter = counter + 1; // count the time
    if (counter > 7)
    {                   // if the time is more than 10s change the light
      counter = 0;      // reset the counter
      changemainroad(); // change the light
      mroad = 0;
      delay(3000);
    }
  }
  delay(1000); // delay 1000ms to avoid the sensor reading error
}

void changemainroad() // change the light in main road
{
  digitalWrite(LED_G1, LOW); // turn off the green light in main road
  for (int a = 0; a < 3; a = a + 1)
  { // blink the yellow light in mian road 3 times slow
    digitalWrite(LED_Y1, HIGH);
    delay(1000);
    digitalWrite(LED_Y1, LOW);
    delay(1000);
  }

  analogWrite(LED_R2, 100); // turn down brightness of the red ligh in the main road

  for (int b = 0; b < 3; b = b + 1)
  { // blink the yellow light in mian road 3 times fast
    digitalWrite(LED_Y1, HIGH);
    delay(500);
    digitalWrite(LED_Y1, LOW);

    delay(500);
  }

  digitalWrite(LED_R2, LOW);  // turn off the red light in sider road
  digitalWrite(LED_R1, HIGH); // turn on the red light in main road
  digitalWrite(LED_G2, HIGH); // turn on the green light in sider road
}

void changeSideroad() // change the light in sider road
{
  digitalWrite(LED_G2, LOW); // turn off the green light in sider road
  for (int a = 0; a < 3; a = a + 1)
  {
    digitalWrite(LED_Y2, HIGH); // blink the yellow light in sider road 3 times slow
    delay(1000);
    digitalWrite(LED_Y2, LOW); // turn off the yellow light in sider road
    delay(1000);
  }

  analogWrite(LED_R1, 100); // turn down brightness of the red ligh in the main road

  for (int a = 0; a < 3; a = a + 1)
  {
    digitalWrite(LED_Y2, HIGH); // blink the yellow light in sider road 3 times fast
    delay(500);
    digitalWrite(LED_Y2, LOW); // turn off the yellow light in sider road
    delay(500);
  }                           // turn down brightness of the red ligh in the main road
  digitalWrite(LED_R1, LOW);  // turn off the red light in main road
  digitalWrite(LED_R2, HIGH); // turn on the red light in sider road
  digitalWrite(LED_G1, HIGH); // turn on the green light in main road
}
