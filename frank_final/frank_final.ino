//written by Philipp

//max analogWrite: 250

#define STANDARD_SPEED 150
#define SPEED_ADD 80
#define ROTATE_TIME 250
#define ROTATE_SPEED 130
#define MAX_DISTANCE 30
#define RIGHT_ADD 50

int MOTOR_DRIVER1 = 27, MOTOR_DRIVER2 = 4, MOTOR_DRIVER3 = 25, MOTOR_DRIVER4 = 26, speed_left, speed_right;


//Ultraschall Sensor
int US_TRIGGER1 = 18, US_ECHO1 = 5;
long US_DURATION, US_DISTANCE;
 
//Line Finder
int LINE_FINDER1 = 34, LINE_FINDER2 = 35, LINE_FINDER3 = 32;
int LINE_LEFT, LINE_RIGHT, LINE_MIDDEL;

//deklarierung der Funktionen
void motor_controll(int left_speed, int right_speed);
void get_distance();
void get_ir_input();
void object_evasion();
void SIEG();
	

void setup() {
	//Ultraschall Sensor
	pinMode(US_TRIGGER1, OUTPUT);
	pinMode(US_ECHO1, INPUT);

	//Motor_Driver
	pinMode(MOTOR_DRIVER1, OUTPUT); 
	pinMode(MOTOR_DRIVER2, OUTPUT); 
	pinMode(MOTOR_DRIVER3, OUTPUT); 
	pinMode(MOTOR_DRIVER4, OUTPUT);
	
	//Line Finder
	pinMode(LINE_FINDER1, INPUT);	
	pinMode(LINE_FINDER2, INPUT);	
	pinMode(LINE_FINDER3, INPUT);	

}

void loop() {
	//get sensor data
	get_distance();
	get_ir_input();
	
	if(US_DISTANCE < MAX_DISTANCE) {
		object_evasion();
		//obj();
	}

	//object_evasion();
	//delay(2000);

/*
	if(!LINE_MIDDEL) {
		if(LINE_RIGHT) {
			motor_controll(STANDARD_SPEED, 0);
		}
		if(LINE_LEFT) {
			motor_controll(0, STANDARD_SPEED);
		}
	}*/

	//checks if the middle sensor is on the line
	if(LINE_RIGHT || LINE_LEFT) {
		if(LINE_RIGHT) {
			//maybe 0 for l speed
			motor_controll(STANDARD_SPEED, -STANDARD_SPEED);
			//while(!LINE_MIDDEL) get_ir_input();
			//motor_controll(0, STANDARD_SPEED);
		} 
		if(LINE_LEFT) {
		
			//maybe 0 for r speed
			motor_controll(-STANDARD_SPEED, STANDARD_SPEED);
			//while(!LINE_MIDDEL) get_ir_input();
			//motor_controll(STANDARD_SPEED, 0);
		}
	} else motor_controll(STANDARD_SPEED, STANDARD_SPEED);
}

//nimmt left_speed und rigth_speed als input, stellt die jeweiligen pins ein
void motor_controll(int left_speed, int right_speed) {
	if(left_speed > 0) {

		analogWrite(MOTOR_DRIVER2, 0);
		analogWrite(MOTOR_DRIVER1, left_speed); 

	} else {

		analogWrite(MOTOR_DRIVER1, 0);
		analogWrite(MOTOR_DRIVER2, abs(left_speed));
 
	}

	if(right_speed > 0) {

		analogWrite(MOTOR_DRIVER3, 0); 
		analogWrite(MOTOR_DRIVER4, right_speed); 
	
	} else {

		analogWrite(MOTOR_DRIVER4, 0);
		analogWrite(MOTOR_DRIVER3, abs(right_speed)); 
	}
}

//triggers den Ultraschall sensor und schreibt die Distanz in den US_DISTANCE Wert fix für den nicht funktionierenden us sensor: manual lesen und merken dass man 1,7 V zu wenig hat
void get_distance() {
	digitalWrite(US_TRIGGER1, HIGH);
	delay(10);
	
	digitalWrite(US_TRIGGER1, LOW);

	US_DURATION = pulseIn(US_ECHO1, HIGH);
	US_DISTANCE = (US_DURATION / 2) * 0.03432;
}

void get_ir_input() {
	LINE_MIDDEL = digitalRead(35);
	LINE_LEFT = digitalRead(34);
	LINE_RIGHT = digitalRead(32);
}

//measures distance to object and distance in 0,5 seconds, rotates and drives for a calculatet amount of time
void object_evasion() {
	get_distance();

	int previous_distance = US_DISTANCE;

	delay(100);

	get_distance();

	float cm_per_sec = (previous_distance - US_DISTANCE) * 10;

	//rotate l
	motor_controll(-ROTATE_SPEED, ROTATE_SPEED+RIGHT_ADD);
	delay(ROTATE_TIME);

	//drive for x delay
	motor_controll(STANDARD_SPEED, STANDARD_SPEED);
	//delay(ROTATE_TIME*4.5);
	delay(1000 * (US_DISTANCE / cm_per_sec)*2);	

	//rotate r
	motor_controll(ROTATE_SPEED, -(ROTATE_SPEED+RIGHT_ADD));
	delay(ROTATE_TIME*1.5);
	
	while(!LINE_MIDDEL || !LINE_RIGHT || !LINE_LEFT) {
		get_ir_input();
		motor_controll(STANDARD_SPEED/2, STANDARD_SPEED/2);
	} 

	while(!LINE_MIDDEL) {
		get_ir_input();
		motor_controll(STANDARD_SPEED/2, -(STANDARD_SPEED/2));
	}
	motor_controll(STANDARD_SPEED, STANDARD_SPEED);
}

void obj() {
    motor_controll(ROTATE_SPEED, -ROTATE_SPEED);
    delay(ROTATE_TIME);
    motor_controll(STANDARD_SPEED, STANDARD_SPEED);
    delay((US_DISTANCE * 10) / STANDARD_SPEED); // Move distance away from object
    motor_controll(-ROTATE_SPEED, ROTATE_SPEED);
    delay(ROTATE_TIME);
    motor_controll(STANDARD_SPEED, STANDARD_SPEED);
    delay((US_DISTANCE * 10) / STANDARD_SPEED);
}

void SIEG() {
	get_distance();

	int previous_distance = US_DISTANCE;

	delay(100);

	get_distance();

	float cm_per_sec = (previous_distance - US_DISTANCE) * 10;

	//rotate l
	motor_controll(-ROTATE_SPEED, ROTATE_SPEED+RIGHT_ADD);
	delay(ROTATE_TIME);

	//drive for x delay
	motor_controll(STANDARD_SPEED, STANDARD_SPEED);
	delay(300);
	//delay(1000 * (US_DISTANCE / cm_per_sec));	

	//rotate r
	motor_controll(ROTATE_SPEED, -(ROTATE_SPEED+RIGHT_ADD));
	delay(ROTATE_TIME*2);

	//drive for x delay
	motor_controll(STANDARD_SPEED, STANDARD_SPEED);
	delay(300);
	//delay(1000 * (US_DISTANCE / cm_per_sec));

	//rotate l
	motor_controll(-ROTATE_SPEED, ROTATE_SPEED);
	delay(ROTATE_TIME);

	//motor_controll(STANDARD_SPEED, STANDARD_SPEED);
}

