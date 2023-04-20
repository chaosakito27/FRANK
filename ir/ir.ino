
int LINE_MIDDEL, LINE_LEFT, LINE_RIGHT;


void get_ir_input() {
	LINE_MIDDEL = digitalRead(35);
	LINE_LEFT = digitalRead(34);
	LINE_RIGHT = digitalRead(32);
}



void setup() {
	Serial.begin(9600);

	pinMode(35, INPUT);
	pinMode(34, INPUT);
	pinMode(32, INPUT);
}

void loop() {

	get_ir_input();
	Serial.print(LINE_MIDDEL);
	Serial.print(" Line m\n");

	delay(2000);
}
