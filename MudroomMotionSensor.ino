 /*
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - Alex Arent
 *
 * DESCRIPTION
 * Motion Sensor example using HC-SR501. Based on the following MySensors example
 * http://www.mysensors.org/build/motion
 *
 */

// Enable debug prints
#define MY_DEBUG
#define MY_NODE_ID 4
#define MY_RADIO_NRF24

#include <MySensors.h>

#define DIGIAL_INPUT_DOOR_SENSOR 2    
#define DIGITAL_INPUT_MOTION_SENSOR 3
#define CHILD_ID_MOTION_SENSOR 1  
#define CHILD_ID_DOOR_SENSOR 2

// Initialize motion message
MyMessage motionSensor(CHILD_ID_MOTION_SENSOR, V_TRIPPED);
MyMessage doorSensor(CHILD_ID_DOOR_SENSOR, V_TRIPPED);

void setup()
{
	pinMode(DIGITAL_INPUT_MOTION_SENSOR, INPUT_PULLUP);
  pinMode(DIGIAL_INPUT_DOOR_SENSOR, INPUT_PULLUP);
}

void presentation()
{
	// Send the sketch version information to the gateway and Controller
	sendSketchInfo("Mudroom Motion and Door Node", "1.0");

	// Register all sensors to gw (they will be created as child devices)
	present(CHILD_ID_MOTION_SENSOR, S_MOTION);
  present(CHILD_ID_DOOR_SENSOR, S_DOOR);
}

void loop()
{
	//Read both sensor's states
	bool motionSensorState = digitalRead(DIGITAL_INPUT_MOTION_SENSOR) == LOW;
  bool doorSensorState = digitalRead(DIGIAL_INPUT_DOOR_SENSOR) == LOW;
  
  Serial.println("Motion Sensor State");
	Serial.println(motionSensorState);
	send(motionSensor.set(motionSensorState?"1":"0"));  

  Serial.println("Door Sensor State");
  Serial.println(doorSensorState);
  send(motionSensor.set(doorSensorState?"1":"0"));  
  
	// Sleep until interrupt comes in on door or motion sensor
	sleep(digitalPinToInterrupt(DIGITAL_INPUT_MOTION_SENSOR), CHANGE, digitalPinToInterrupt(DIGIAL_INPUT_DOOR_SENSOR), CHANGE,0);
}

