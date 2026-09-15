#include <Servo.h>

// Pin definitions
const int trigPin = 8;    // Ultrasonic sensor Trig pin
const int echoPin = 9;   // Ultrasonic sensor Echo pin
const int servoPin1 = 10; // First servo motor signal pin
const int servoPin2 = 11; // Second servo motor signal pin

// Servo objects
Servo binServo1;
Servo binServo2;

// Adjustable parameters
const int distanceThreshold = 20; // Distance in cm to trigger the bin (adjust as needed)
int openTime = 3000;             // Time in milliseconds to keep the bin open (adjustable, e.g., 10000 for 10 seconds)

// Variables
long duration;
int distance;

void setup() {
  // Initialize serial communication for debugging (optional)
  Serial.begin(9600);
  
  // Set ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Attach servos to pins
  binServo1.attach(servoPin1);
  binServo2.attach(servoPin2);
  
  // Initialize servos to closed position (assume 0 degrees is closed)
  binServo1.write(0);
  binServo2.write(0);
}

void loop() {
  // Measure distance using ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance in cm
  
  // Print distance for debugging (optional)
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Check if object is within threshold
  if (distance < distanceThreshold && distance > 0) { // Added >0 to avoid false positives
    // Open the bin (rotate both servos to, e.g., 90 degrees)
    binServo1.write(90);
    binServo2.write(90);
    
    // Wait for the adjustable open time
    delay(openTime);
    
    // Close the bin (rotate both servos back to 0 degrees)
    binServo1.write(0);
    binServo2.write(0);
    
    // Optional: Add a small delay to prevent immediate re-triggering
    delay(1000);
  }
  
  // Small delay between measurements
  delay(100);
}