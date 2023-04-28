#define colorClkPin   7
#define colorLatchPin 6
#define colorEnable   5
#define dataPinR 2
#define dataPinB 3
#define dataPinG 4

#define anodeEnablePin 8

int anodeSelectPins[] = {13, 12, 11};

int layer = 7;
uint64_t datR = 1;
uint64_t datG = 1;
uint64_t datB = 1;



int GLayout[] = { 
  0, 1, 2, 3, 4, 5, 6, 7, 
  15, 14, 13, 12, 11, 10, 9, 8, 
  16, 17, 18, 19, 20, 21, 22, 23, 
  31, 30, 29, 28, 27, 26, 25, 24, 
  32, 33, 34, 35, 36, 37, 38, 39, 
  47, 46, 45, 44, 43, 42, 41, 40, 
  48, 49, 50, 51, 52, 53, 54, 55, 
  63, 62, 61, 60, 59, 58, 57, 56  
};

int RBLayout[] = {              //Layout for Red and Blue
  16, 17, 18, 19, 0, 1, 2, 3,
  20, 21, 22, 23, 4, 5, 6, 7,
  27, 26, 25, 24, 11, 10, 9, 8,
  31, 30, 29, 28, 15, 14, 13, 12,
  52, 53, 54, 55, 36, 37, 38, 39,
  48, 49, 50, 51, 32, 33, 34, 35,
  59, 58, 57, 56, 43, 42, 41, 40,
  63, 62, 61, 60, 47, 46, 45, 44
};


void setup() {
  Serial.begin(115200);
  
  pinMode(colorClkPin, OUTPUT);
  pinMode(colorLatchPin, OUTPUT);
  pinMode(colorEnable, OUTPUT);
  pinMode(dataPinR, OUTPUT);
  pinMode(dataPinG, OUTPUT);
  pinMode(dataPinB, OUTPUT);
  digitalWrite(colorEnable, LOW);
  digitalWrite(colorLatchPin, LOW);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(anodeEnablePin, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(anodeSelectPins[i], OUTPUT);
  }

  digitalWrite(anodeEnablePin, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}

void loop() {
  // This has to be here for some reason...
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(anodeEnablePin, HIGH);
  
  digitalWrite(colorEnable, HIGH);

  for (int i = 0; i < 3; i++) {
    digitalWrite(anodeSelectPins[i], (layer & (1 << i)) ? HIGH : LOW);
  }

  SingleLayerManipulation(datR, datG, datB);
 

  digitalWrite(colorEnable, LOW);
  
  digitalWrite(colorLatchPin, LOW);
  delay(1000);
  digitalWrite(colorLatchPin, HIGH);

  datG = datG << 1;
  if (datG == 0) {
    datG = 1;
  }
 // dat2 = dat2 << 1;
 // if (dat2 == 0) {
  //  dat2 = 0x0001;
 // }
  // dat3 = dat3 << 1;
  // if (dat3 == 0) {
  //   dat3 = 0x0001;
  //   layer = (layer + 1) % 8; 
  // }
}

     //Function to output green to the cube
void SingleLayerManipulation(uint64_t R, uint64_t G, uint64_t B){
   
  for (int i = 0; i < 64; i++) {
    
    //Serial.print((uint32_t)((1 << GLayout[i])),HEX);
    //Serial.println((uint32_t)((1 << GLayout[i]) & 0xFFFFFFFF00000000),HEX);
    
    //digitalWrite(dataPinR, R & 1 << RBLayout[i]);
    digitalWrite(dataPinG, (G & ((uint64_t)1 << GLayout[i])));
    
    //digitalWrite(dataPinB, B & 1 << RBLayout[i]);
    
    digitalWrite(colorClkPin, HIGH);
    digitalWrite(colorClkPin, LOW);
    
    sprintBin(((uint64_t)1 << GLayout[i]));
  }
}

void sprintBin(uint64_t b) {
  for (int i = 0; i < 64; i++) {
    Serial.print((b & ((uint64_t)1 << i)) ? "1" : "0");
  }
  Serial.println();
}