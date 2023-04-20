
int LINE_FINDER1 = 34, LINE_FINDER2 = 35, LINE_FINDER3 = 32;
int LINE_LEFT, LINE_RIGHT, LINE_MIDDEL;


void get_ir_input() {
	Serial.begin(9600);
	LINE_MIDDEL = digitalRead(35);
	LINE_LEFT = digitalRead(34);
	LINE_RIGHT = digitalRead(32);
}


void setup() {
	//Motor_Driver
	pinMode(LINE_FINDER1, INPUT);	
	pinMode(LINE_FINDER2, INPUT);	
	pinMode(LINE_FINDER3, INPUT);
}

void loop() {
	delay(1000);
	get_ir_input();
	Serial.print(LINE_LEFT);
}
