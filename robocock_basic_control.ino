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

// parameters
#define SPEED 70 // 0 - 255
#define RAMP_INT 1000  // ramp interval in ms

enum Movement { Nm, Sm, Em, Wm, NWm, NEm, SWm, SEm, CLm, ACLm, Hm };

int ramp_state = 0;   // 0 prepares for ramp up(H -> !H); 1 prepares for ramp down(!H -> H)
Movement move_state = Hm; 

int n_state = 0;
int s_state = 0;
int e_state = 0;
int w_state = 0;
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
  if(n_state == 1 && s_state == 0 && e_state == 0 && w_state == 0) {  // N
    move_state = Nm;
    accel();
    Nmovement(SPEED);
  } else if(n_state == 0 && s_state == 1 && e_state == 0 && w_state == 0) { // S
    move_state = Sm;
    accel();
    Smovement(SPEED);
  } else if(n_state == 0 && s_state == 0 && e_state == 1 && w_state == 0) { // E
    move_state = Em;
    accel();
    Emovement(SPEED);
  } else if(n_state == 0 && s_state == 0 && e_state == 0 && w_state == 1) { // W
    move_state = Wm;
    accel();
    Wmovement(SPEED);
  } else if(n_state == 1 && s_state == 0 && e_state == 1 && w_state == 0) { // NE
    move_state = NEm;
    accel();
    NEmovement(SPEED);
  } else if(n_state == 1 && s_state == 0 && e_state == 0 && w_state == 1) { // NW
    move_state = NWm;
    accel();
    NWmovement(SPEED);
  } else if(n_state == 0 && s_state == 1 && e_state == 1 && w_state == 0) { // SE
    move_state = SEm;
    accel();
    SEmovement(SPEED);
  } else if(n_state == 0 && s_state == 1 && e_state == 0 && w_state == 1) {  // SW
    move_state = SWm;
    accel();
    SWmovement(SPEED);
  } else if(n_state == 1 && s_state == 1 && e_state == 1 && w_state == 0) { // CL
    move_state = CLm;
    accel();
    CLmovement(SPEED);
  } else if(n_state == 1 && s_state == 1 && e_state == 0 && w_state == 1) { // ACL
    move_state = ACLm;
    accel();
    ACLmovement(SPEED);
  } else {  // Halt
    decel();
    Hmovement();
    move_state = Hm;
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

void accel() {
  if(ramp_state == 0) {
    switch(move_state) {
      case Nm :
        for(int i = 0; i < SPEED; i++) {
          Nmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case Sm :
        for(int i = 0; i < SPEED; i++) {
          Smovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case Em :
        for(int i = 0; i < SPEED; i++) {
          Emovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case Wm :
        for(int i = 0; i < SPEED; i++) {
          Wmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case NWm :
        for(int i = 0; i < SPEED; i++) {
          NWmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case NEm :
        for(int i = 0; i < SPEED; i++) {
          NEmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case SWm :
        for(int i = 0; i < SPEED; i++) {
          SWmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case SEm :
        for(int i = 0; i < SPEED; i++) {
          SEmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case CLm :
        for(int i = 0; i < SPEED; i++) {
          CLmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case ACLm :
        for(int i = 0; i < SPEED; i++) {
          ACLmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
    }
    ramp_state = 1;
  }
}

void decel() {
  if(ramp_state == 1) {
    switch(move_state) {
      case Nm :
        for(int i = SPEED; i > 0; i--) {
          Nmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case Sm :
        for(int i = SPEED; i > 0; i--) {
          Smovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case Em :
        for(int i = SPEED; i > 0; i--) {
          Emovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case Wm :
        for(int i = SPEED; i > 0; i--) {
          Wmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case NWm :
        for(int i = SPEED; i > 0; i--) {
          NWmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case NEm :
        for(int i = SPEED; i > 0; i--) {
          NEmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case SWm :
        for(int i = SPEED; i > 0; i--) {
          SWmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case SEm :
        for(int i = SPEED; i > 0; i--) {
          SEmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case CLm :
        for(int i = SPEED; i > 0; i--) {
          CLmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
      case ACLm :
        for(int i = SPEED; i > 0; i--) {
          ACLmovement(i);
          delay(RAMP_INT/SPEED);
        }
        break;
    }
    ramp_state = 0;
  }
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
