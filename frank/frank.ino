//written by Philipp

//max analogWrite: 250

#define SPEED 220

//Motor Driver
int MOTOR_DRIVER1 = 27, MOTOR_DRIVER2 = 4, MOTOR_DRIVER3 = 25, MOTOR_DRIVER4 = 26, speed_left, speed_right;


//Ultraschall Sensor
int US_TRIGGER1 = 18, US_ECHO1 = 39;
long US_DURATION, US_DISTANCE;
 
//Line Finder
int LINE_FINDER1 = 34, LINE_FINDER2 = 35, LINE_FINDER3 = 36;
int LINE_LEFT, LINE_RIGHT, LINE_MIDDEL;

int count;

//deklarierung der Funktionen
void motor_controll(int left_speed, int right_speed);
void get_distance();
void get_ir_input();

//todo
void object_evasion();
	

void setup() {
	//Ultraschall Sensor
	Serial.begin (9600);
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

/*
	move for x seconds:
		motor_controll(l, r);
		delay(x);
*/ 

void loop() {

	get_distance();
	get_ir_input();
	
/*	
	if(US_DISTANCE < 40) {
		object_avasion();
	}
*/
	if(!LINE_MIDDEL) {
		if(LINE_RIGHT) {
			speed_right += 60;
			speed_left = 180;
		} 
		if(LINE_LEFT) {
			speed_left += 60;
			speed_right = 180;
		}
		motor_controll(speed_left, speed_right);
	}

	motor_controll(SPEED, SPEED);
	
	delay(40);
}

//nimmt left_speed und rigth_speed als input, stellt die jeweiligen pins ein
void motor_controll(int left_speed, int right_speed) {
	if(left_speed > 0) {

		analogWrite(MOTOR_DRIVER2, 0);
		analogWrite(MOTOR_DRIVER1, left_speed); 

	} else {

		analogWrite(MOTOR_DRIVER1, 0);
		analogWrite(MOTOR_DRIVER2, left_speed);
 
	}

	if(right_speed > 0) {

		analogWrite(MOTOR_DRIVER4, 0); 
		analogWrite(MOTOR_DRIVER3, right_speed); 
	
	} else {

		analogWrite(MOTOR_DRIVER3, 0);
		analogWrite(MOTOR_DRIVER4, right_speed); 
	}
}

//triggers den Ultraschall sensor und schreibt die Distanz in den US_DISZANCE Wert
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
	LINE_RIGHT = digitalRead(36);
}

void object_evasion() {
	
}
