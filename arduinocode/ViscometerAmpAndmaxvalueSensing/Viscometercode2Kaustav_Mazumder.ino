
const int txPin = 8;
const int rxPin = A0;

const int txFrequency = 5000;
const int threshold = 10;

void setup() {
  Serial.begin(9600);

  // Start continuous transmission
  tone(txPin, txFrequency);
}

void loop() {
  unsigned long start = micros();
  unsigned long crossings = 0;

  int minValue = 1023;
  int maxValue = 0;
  int previous = analogRead(rxPin);

  // Measure receiver for approximately 20 ms
  while (micros() - start < 20000) {
    int value = analogRead(rxPin);

    if (value < minValue) minValue = value;
    if (value > maxValue) maxValue = value;

    if (previous < 512  &&
        value >= 512 ) {
      crossings++;
    }

    previous = value;
  }

  float amplitude =
      (maxValue - minValue) ;

  float maxvalue = maxValue ;

  Serial.print("Amplitude:");
  Serial.print(amplitude, 3);
  Serial.print("\tMaxvalue:");
  Serial.println(maxvalue, 1);
}
