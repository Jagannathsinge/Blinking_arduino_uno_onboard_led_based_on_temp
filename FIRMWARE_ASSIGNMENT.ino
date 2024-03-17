/*
NAME: Jagannath
DATE: 17/03/2024
DESCRIPTION: Blinking arduino uno onboard led based on temperature
*/

#include <Arduino.h>
#include <TimerOne.h>

// defining temperature sensor to A0
#define LM35 A0
// defining onboard led pin
#define LEDPIN 13

// Variables to store temperature and blink interval
volatile float temperature_celsius; // corrected typo in variable name
volatile unsigned long blink_interval; // changed int to unsigned long for timer interval

// Function declaration
void check_temperature();
void blink_led();

void setup() 
{
  // Initializing baud rate for data communication
  Serial.begin(9600);

  // Setting pin direction led pin as output
  pinMode(LEDPIN, OUTPUT);

  // Interrupt to the timer to trigger every 1 millisecond
  Timer1.initialize(1000); 
  Timer1.attachInterrupt(check_temperature);
}

void loop() 
{
  // Leave loop empty, as all functionality is handled by interrupts
}

void check_temperature() 
{
  // Reading the voltage from the LM35 temperature sensor
  int sensor_value = analogRead(LM35);

  // Converting the analog reading from LM35 temperature sensor to degree Celsius
  temperature_celsius = (sensor_value * 5.0 / 1024.0) * 100.0; 

  // Print the temperature in serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature_celsius);
  Serial.println(" C");

  // Checking if temperature is below 30 degrees Celsius
  if (temperature_celsius < 30) 
  {
    // if condition true set blink interval to 250 milliseconds
    blink_interval = 250; 
  } 
  else 
  {
    // Set blink interval to 500 milliseconds
    blink_interval = 500; 
  }

  // Call blinkLED function after blinkInterval and converting milliseconds to microseconds
  Timer1.attachInterrupt(blink_led, blink_interval * 1000UL); // corrected conversion to microseconds
}

void blink_led() 
{
  // Toggle the LED state
  digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}
