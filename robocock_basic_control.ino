#define ENCA 52 // YELLOW
#define ENCB 53 // WHITE
#define RPWM_1 2  // front left wheel
#define LPWM_1 3
#define RPWM_2 4  // front right wheel
#define LPWM_2 5
#define RPWM_3 6  // rear left wheel
#define LPWM_3 7
#define RPWM_4 8  // rear right wheel
#define LPWM_4 9
#define N_CONTROL 22 // forward push button
#define S_CONTROL 23 // reverse push button
#define E_CONTROL 24 // left strafe push button
#define W_CONTROL 25 // right strafe push button
#define CL_CONTROL 26 // clockwise push button
#define ACL_CONTROL 27 // anti-clockwise push button

#define SPEED 70 // 0 - 255

int n_state = 0;
int s_state = 0;
int e_state = 0;
int w_state = 0;
int cl_state = 0;
int acl_state = 0;
volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/

void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  pinMode(N_CONTROL, INPUT);
  pinMode(S_CONTROL, INPUT);
  pinMode(E_CONTROL, INPUT);
  pinMode(W_CONTROL, INPUT);
  pinMode(CL_CONTROL, INPUT);
  pinMode(ACL_CONTROL, INPUT);
  
  
  pinMode(RPWM_1,OUTPUT);
  pinMode(LPWM_1, OUTPUT);
  pinMode(RPWM_2,OUTPUT);
  pinMode(LPWM_2, OUTPUT);
  pinMode(RPWM_3,OUTPUT);
  pinMode(LPWM_3, OUTPUT);
  pinMode(RPWM_4,OUTPUT);
  pinMode(LPWM_4, OUTPUT);
}

void loop() {
  n_state = digitalRead(N_CONTROL);
  s_state = digitalRead(S_CONTROL);
  e_state = digitalRead(E_CONTROL);
  w_state = digitalRead(W_CONTROL);
  cl_state = digitalRead(CL_CONTROL);
  acl_state = digitalRead(ACL_CONTROL);
  if(n_state == 1 && s_state == 0 && e_state == 0 && w_state == 0 && cl_state == 0 && acl_state == 0) {  // N
    Nmovement(SPEED);
  } else if(n_state == 0 && s_state == 1 && e_state == 0 && w_state == 0 && cl_state == 0 && acl_state == 0) { // S
    Smovement(SPEED);
  } else if(n_state == 0 && s_state == 0 && e_state == 1 && w_state == 0 && cl_state == 0 && acl_state == 0) { // E
    Emovement(SPEED);
  } else if(n_state == 0 && s_state == 0 && e_state == 0 && w_state == 1 && cl_state == 0 && acl_state == 0) { // W
    Wmovement(SPEED);
  } else if(n_state == 1 && s_state == 0 && e_state == 1 && w_state == 0 && cl_state == 0 && acl_state == 0) { // NE
    NEmovement(SPEED);
  } else if(n_state == 1 && s_state == 0 && e_state == 0 && w_state == 1 && cl_state == 0 && acl_state == 0) { // NW
    NWmovement(SPEED);
  } else if(n_state == 0 && s_state == 1 && e_state == 1 && w_state == 0 && cl_state == 0 && acl_state == 0) { // SE
    SEmovement(SPEED);
  } else if(n_state == 0 && s_state == 1 && e_state == 0 && w_state == 1 && cl_state == 0 && acl_state == 0) {  // SW
    SWmovement(SPEED);
  } else if(n_state == 0 && s_state == 0 && e_state == 0 && w_state == 0 && cl_state == 1 && acl_state == 0) { // CL
    CLmovement(SPEED);
  } else if(n_state == 0 && s_state == 0 && e_state == 0 && w_state == 0 && cl_state == 0 && acl_state == 1) { // ACL
    ACLmovement(SPEED);
  } else {  // Halt
    Hmovement();
  }
  
}

                //direction    pwm    rpwm pin   lpwm pin
void setMotor(int dirVal, int pwmVal, int rpwm, int lpwm){   // pwm = 0 - 255
  if(dirVal > 0){
    analogWrite(rpwm, pwmVal);
    analogWrite(lpwm, 0);
  }
  else if(dirVal < 0){
    analogWrite(lpwm, pwmVal);
    analogWrite(rpwm, 0);
  }
  else{
    analogWrite(rpwm, 0);
    analogWrite(lpwm, 0);
  }
}

// Halt
void Hmovement() { // 1: x; 2: x; 3: x; 4: x
  setMotor(0, 0, RPWM_1, LPWM_1);   // 1
  setMotor(0, 0, RPWM_2, LPWM_2);   // 2
  setMotor(0, 0, RPWM_3, LPWM_3);   // 3
  setMotor(0, 0, RPWM_4, LPWM_4);   // 4
}

// Forward(North)
void Nmovement(int pwm) { // 1: RPWM; 2: LPWM; 3: RPWM; 4: LPWM
  setMotor(1, pwm, RPWM_1, LPWM_1);   // 1
  setMotor(-1, pwm, RPWM_2, LPWM_2);   // 2
  setMotor(1, pwm, RPWM_3, LPWM_3);   // 3
  setMotor(-1, pwm, RPWM_4, LPWM_4);   // 4
}

// Reverse(South)
void Smovement(int pwm) { // 1: LPWM; 2: RPWM; 3: LPWM; 4: RPWM
  setMotor(-1, pwm, RPWM_1, LPWM_1);   // 1
  setMotor(1, pwm, RPWM_2, LPWM_2);   // 2
  setMotor(-1, pwm, RPWM_3, LPWM_3);   // 3
  setMotor(1, pwm, RPWM_4, LPWM_4);   // 4
}

// Left strafe(West)
void Wmovement(int pwm) { // 1: LPWM; 2: LPWM; 3: RPWM; 4: RPWM
  setMotor(-1, pwm, RPWM_1, LPWM_1);   // 1
  setMotor(-1, pwm, RPWM_2, LPWM_2);   // 2
  setMotor(1, pwm, RPWM_3, LPWM_3);   // 3
  setMotor(1, pwm, RPWM_4, LPWM_4);   // 4
}

// Right strafe(East)
void Emovement(int pwm) { // 1: RPWM; 2: RPWM; 3: LPWM; 4: LPWM
  setMotor(1, pwm, RPWM_1, LPWM_1);   // 1
  setMotor(1, pwm, RPWM_2, LPWM_2);   // 2
  setMotor(-1, pwm, RPWM_3, LPWM_3);   // 3
  setMotor(-1, pwm, RPWM_4, LPWM_4);   // 4
}

// Front left(North-West)
void NWmovement(int pwm) { // 1: x; 2: LPWM; 3: RPWM; 4: x
  setMotor(0, 0, RPWM_1, LPWM_1);   // 1
  setMotor(-1, pwm, RPWM_2, LPWM_2);   // 2
  setMotor(1, pwm, RPWM_3, LPWM_3);   // 3
  setMotor(0, 0, RPWM_4, LPWM_4);   // 4
}

// Front right(North-East)
void NEmovement(int pwm) { // 1: RPWM; 2: x; 3: x; 4: LPWM
  setMotor(1, pwm, RPWM_1, LPWM_1);   // 1
  setMotor(0, 0, RPWM_2, LPWM_2);   // 2
  setMotor(0, 0, RPWM_3, LPWM_3);   // 3
  setMotor(-1, pwm, RPWM_4, LPWM_4);   // 4
}

// Back left(South-West)
void SWmovement(int pwm) { // 1: LPWM; 2: x; 3: x; 4: RPWM
  setMotor(-1, pwm, RPWM_1, LPWM_1);   // 1
  setMotor(0, 0, RPWM_2, LPWM_2);   // 2
  setMotor(0, 0, RPWM_3, LPWM_3);   // 3
  setMotor(1, pwm, RPWM_4, LPWM_4);   // 4
}

// Back right(South-East)
void SEmovement(int pwm) { // 1: x; 2: RPWM; 3: LPWM; 4: x
  setMotor(0, 0, RPWM_1, LPWM_1);   // 1
  setMotor(1, pwm, RPWM_2, LPWM_2);   // 2
  setMotor(-1, pwm, RPWM_3, LPWM_3);   // 3
  setMotor(0, 0, RPWM_4, LPWM_4);   // 4
}

// Clockwise rotation
void CLmovement(int pwm) { // 1: RPWM; 2: RPWM; 3: RPWM; 4: RPWM
  setMotor(1, pwm, RPWM_1, LPWM_1);   // 1
  setMotor(1, pwm, RPWM_2, LPWM_2);   // 2
  setMotor(1, pwm, RPWM_3, LPWM_3);   // 3
  setMotor(1, pwm, RPWM_4, LPWM_4);   // 4
}

// Anti-clockwise rotation
void ACLmovement(int pwm) { // 1: LPWM; 2: LPWM; 3: LPWM; 4: LPWM
  setMotor(-1, pwm, RPWM_1, LPWM_1);   // 1
  setMotor(-1, pwm, RPWM_2, LPWM_2);   // 2
  setMotor(-1, pwm, RPWM_3, LPWM_3);   // 3
  setMotor(-1, pwm, RPWM_4, LPWM_4);   // 4
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}
