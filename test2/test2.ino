//written by Philipp

//max analogWrite: 250

#define STANDARD_SPEED 200
#define SPEED_ADD 80
#define ROTATE_TIME 200
#define ROTATE_SPEED 90
#define MAX_DISTANCE 15
int MOTOR_DRIVER1 = 27, MOTOR_DRIVER2 = 4, MOTOR_DRIVER3 = 25, MOTOR_DRIVER4 = 26, speed_left, speed_right;

int speed = 100;
int speed_r, speed_l; 
//Line Finder
int LINE_FINDER1 = 34, LINE_FINDER2 = 35, LINE_FINDER3 = 32;
int LINE_LEFT, LINE_RIGHT, LINE_MIDDEL;

//deklarierung der Funktionen
void motor_controll(int left_speed, int right_speed);
void get_distance();
void get_ir_input();
void object_evasion();
	

void setup() {
	//Ultraschall Sensor

	//Line Finder
	pinMode(LINE_FINDER1, INPUT);	
	pinMode(LINE_FINDER2, INPUT);	
	pinMode(LINE_FINDER3, INPUT);	

	//Motor_Driver
	pinMode(MOTOR_DRIVER1, OUTPUT); 
	pinMode(MOTOR_DRIVER2, OUTPUT); 
	pinMode(MOTOR_DRIVER3, OUTPUT); 
	pinMode(MOTOR_DRIVER4, OUTPUT);
}

void loop() {
	get_ir_input();
	
	//if(LINE_LEFT || LINE_RIGHT) speed = 100;
	//else speed = 125;

	if(LINE_LEFT) {
		do {

		} while
	} 
	else if(LINE_RIGHT) {

	}
	else motor_controll(speed*(!LINE_LEFT), speed*(!LINE_RIGHT));

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

void get_ir_input() {
	LINE_MIDDEL = digitalRead(35);
	LINE_LEFT = digitalRead(34);
	LINE_RIGHT = digitalRead(32);
}


