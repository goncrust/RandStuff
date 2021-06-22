
int a = 46;
int b = 48;
int c = 50;
int d = 52;

bool a_h = false;
bool b_h = false;
bool c_h = false;
bool d_h = false;

int counter = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (counter == 16) counter = 0;

  if (counter == 0) {
     a_h = false;
     b_h = false;
     c_h = false;
     d_h = false;
  } else if (counter == 1) {
     a_h = true;
     b_h = false;
     c_h = false;
     d_h = false;
  } else if (counter == 2) {
     a_h = false;
     b_h = true;
     c_h = false;
     d_h = false;
  } else if (counter == 3) {
     a_h = true;
     b_h = true;
     c_h = false;
     d_h = false;
  } else if (counter == 4) {
     a_h = false;
     b_h = false;
     c_h = true;
     d_h = false;
  } else if (counter == 5) {
     a_h = true;
     b_h = false;
     c_h = true;
     d_h = false;
  } else if (counter == 6) {
     a_h = false;
     b_h = true;
     c_h = true;
     d_h = false;
  } else if (counter == 7) {
     a_h = true;
     b_h = true;
     c_h = true;
     d_h = false;
  } else if (counter == 8) {
     a_h = false;
     b_h = false;
     c_h = false;
     d_h = true;
  } else if (counter == 9) {
     a_h = true;
     b_h = false;
     c_h = false;
     d_h = true;
  } else if (counter == 10) {
     a_h = false;
     b_h = true;
     c_h = false;
     d_h = true;
  } else if (counter == 11) {
     a_h = true;
     b_h = true;
     c_h = false;
     d_h = true;
  } else if (counter == 12) {
     a_h = false;
     b_h = false;
     c_h = true;
     d_h = true;
  } else if (counter == 13) {
     a_h = true;
     b_h = false;
     c_h = true;
     d_h = true;
  } else if (counter == 14) {
     a_h = false;
     b_h = true;
     c_h = true;
     d_h = true;
  } else if (counter == 15) {
     a_h = true;
     b_h = true;
     c_h = true;
     d_h = true;
  }

  if (d_h) {
    digitalWrite(a, HIGH);
  } else {
    digitalWrite(a, LOW);
  }
  
  if (c_h) {
    digitalWrite(b, HIGH);
  } else {
    digitalWrite(b, LOW);
  }
  
  if (b_h) {
    digitalWrite(c, HIGH);
  } else {
    digitalWrite(c, LOW);
  }
  
  if (a_h) {
    digitalWrite(d, HIGH);
  } else {
    digitalWrite(d, LOW);
  }

  counter++;

  delay(500);
}
