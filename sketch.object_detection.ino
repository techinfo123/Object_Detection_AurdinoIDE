#include <NewPing.h>
#include <Servo.h>

#define ULTRASONIC_SENSOR_TRIG 10
#define ULTRASONIC_SENSOR_ECHO 9
#define motorRightF 2
#define motorRightR 3
#define motorLeftF 4
#define motorLeftR 5

NewPing sonar(ULTRASONIC_SENSOR_TRIG, ULTRASONIC_SENSOR_ECHO);
Servo myServo;

void setup()
{
    Serial.begin(9600); // Initialize serial communication

    // Set the specified pins as OUTPUT
    pinMode(motorRightF, OUTPUT);
    pinMode(motorRightR, OUTPUT);
    pinMode(motorLeftF, OUTPUT);
    pinMode(motorLeftR, OUTPUT);

    myServo.attach(7); // Attach the servo to pin 3
}
int distancef = 9;

void loop()
{
    myServo.write(90);                       // Set the servo to 75 degrees
    unsigned int distance = sonar.ping_cm(); // Measure distance using the ultrasonic sensor

    // Move forward as long as the distance is greater than or equal to 10 cm
    while (distance >= 15)
    {
        digitalWrite(motorRightF, HIGH);
        digitalWrite(motorRightR, LOW);
        digitalWrite(motorLeftF, HIGH);
        digitalWrite(motorLeftR, LOW);

        // Update the distance measurement
        distance = sonar.ping_cm();

        // Print the distance to the serial monitor
        Serial.print("distance1:");
        Serial.print(distance);
        Serial.println();
    }

    // Delay for 100 milliseconds

    myServo.write(0);           // Set the servo to 0 degrees
    distance = sonar.ping_cm(); // Measure distance again
    delay(100);
    if (distance >= 15)
    {
        // Turn right if an obstacle is detected within 10 cm
        digitalWrite(motorRightF, LOW);
        digitalWrite(motorRightR, HIGH);
        digitalWrite(motorLeftF, HIGH);
        digitalWrite(motorLeftR, LOW);

        // Delay for 500 milliseconds
        delay(400);

        // Print the distance to the serial monitor
        Serial.print("distance2:");
        Serial.print(distance);
        Serial.println();

        myServo.write(180);
        distance = sonar.ping_cm(); // Set the servo to 90 degrees
    }
    else
    {
      if(distance>=15)
      {
            // Turn left if an obstacle is detected within 10 cm
            digitalWrite(motorRightF, HIGH);
            digitalWrite(motorRightR, LOW);
            digitalWrite(motorLeftF, LOW);
            digitalWrite(motorLeftR, HIGH);

            // Delay for 500 milliseconds
            delay(400);
            Serial.print("distance3:");
            Serial.print(distance);
            Serial.println(); // Measure distance once more
            // delay(100);
        }
        else
        {
            
            // Stop and turn 180 deg if there's no clear path
            digitalWrite(motorRightF, LOW);
            digitalWrite(motorRightR, HIGH);
            digitalWrite(motorLeftF, HIGH);
            digitalWrite(motorLeftR, LOW);
            // delay(500);

            // // Print the distance to the serial monitor
            // Serial.print("distance4:");
            // Serial.print(distance);
            // Serial.println();

            // Delay for 500 milliseconds
            delay(400);
            Serial.print("distance4:");
            Serial.print(distance);
            Serial.println();
        }
    }
}