int pinData = 2;
int pinClock = 3;
int pinEnable = 4;
int pinRow1 = 5;
int pinRow2 = 6;
int pinRow4 = 7;

#define ROWS 7
#define COLS 40

#define PULSETIME 1000

#define TIMESTEP 20

#define NUMCHARS 127

//Number of cols per character
#define CCOLS 8

// Maximum number of characters allowed in the buffer, multiplied by CCOLS
// In this example, 170 characters (140 chars plus 15 spaces at each end for providing a delay)
#define SHIFTLIMIT ((140*8) + (30*8))

int frame[ROWS][COLS+CCOLS];

int font[NUMCHARS][ROWS] = {
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},  
  {0x18, 0x18, 0x18, 0x18, 0x18, 0x0, 0x18},   //!
  {0x28, 0x14, 0x14, 0x0, 0x0, 0x0, 0x0},      //"
  {0x14, 0x14, 0x7f, 0x14, 0x7f, 0x14, 0x14},  //#
  {0x3c, 0x5a, 0x1a, 0x3c, 0x58, 0x5a, 0x3c},  //$
  {0xc3, 0x63, 0x30, 0x18, 0xc, 0xc6, 0xc3},   //%
  {0xc, 0x12, 0x12, 0x4e, 0x31, 0x31, 0xce},   //&
  {0x18, 0x18, 0x18, 0x0, 0x0, 0x0, 0x0},      //'
  {0x30, 0x18, 0xc, 0xc, 0xc, 0x18, 0x30},     //(
  {0xc, 0x18, 0x30, 0x30, 0x30, 0x18, 0xc},    //)
  {0x18, 0xdb, 0xff, 0x7e, 0x3c, 0x7e, 0x66},  //*
  {0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18},  //+
  {0x0, 0x0, 0x0, 0x0, 0xc, 0xe, 0x7},         //,
  {0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0},       //-
  {0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0xc},         //.
  {0x40, 0x60, 0x30, 0x18, 0xc, 0x6, 0x2},     ///
  {0x3c, 0x66, 0xf3, 0xdb, 0xcf, 0x66, 0x3c},  //0
  {0x1c, 0x1c, 0x18, 0x18, 0x18, 0x3c, 0x3c},  //1
  {0x3c, 0x7e, 0x70, 0x38, 0x1c, 0x7e, 0x7e},  //2
  {0x7e, 0x66, 0x30, 0x3c, 0x60, 0x66, 0x3c},  //3
  {0x3c, 0x3e, 0x33, 0xff, 0xff, 0x30, 0x30},  //4
  {0x7e, 0x7e, 0x6, 0x7c, 0x60, 0x76, 0x3c},   //5
  {0x3c, 0x3e, 0x6, 0x7e, 0x66, 0x7e, 0x3c},   //6
  {0x7e, 0x7e, 0x60, 0x30, 0x18, 0xc, 0x6},    //7
  {0x3c, 0x7e, 0x66, 0x3c, 0x66, 0x7e, 0x3c},  //8
  {0x3c, 0x7e, 0x66, 0x7e, 0x60, 0x7e, 0x3c},  //9
  {0x18, 0x18, 0x0, 0x0, 0x0, 0x18, 0x18},     //:
  {0x18, 0x18, 0x0, 0x0, 0x18, 0x1c, 0xe},     //;
  {0x30, 0x18, 0xc, 0x6, 0xc, 0x18, 0x30},     //<
  {0x0, 0xff, 0xff, 0x0, 0xff, 0xff, 0x0},     //=
  {0xc, 0x18, 0x30, 0x60, 0x30, 0x18, 0xc},    //>
  {0x3c, 0x66, 0x60, 0x30, 0x18, 0x0, 0x18},   //?
  {0x7e, 0x81, 0xbd, 0xb5, 0xfd, 0x1, 0x3e},   //@
  {0x18, 0x3c, 0x66, 0xc3, 0xff, 0xc3, 0xc3},  //A
  {0x3e, 0x66, 0x7e, 0x3e, 0x66, 0x7e, 0x3e},  //B
  {0x3c, 0x7e, 0x6, 0x6, 0x6, 0x7e, 0x3c},     //C
  {0x3e, 0x7e, 0x66, 0x66, 0x66, 0x7e, 0x3e},  //D
  {0x7e, 0x7e, 0x6, 0x3e, 0x6, 0x7e, 0x7e},    //E
  {0x7e, 0x7e, 0x6, 0x3e, 0x3e, 0x6, 0x6},     //F
  {0x3c, 0x7e, 0x6, 0x76, 0x46, 0x7e, 0x3c},   //G
  {0x66, 0x66, 0x66, 0x7e, 0x7e, 0x66, 0x66},  //H
  {0x7e, 0x7e, 0x18, 0x18, 0x18, 0x7e, 0x7e},  //I
  {0x7e, 0x7e, 0x30, 0x30, 0x36, 0x3e, 0x1c},  //J
  {0x66, 0x36, 0x3e, 0x1e, 0x3e, 0x36, 0x66},  //K
  {0x6, 0x6, 0x6, 0x6, 0x6, 0x7e, 0x7e},       //L
  {0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3},  //M
  {0xc3, 0xc7, 0xcf, 0xdb, 0xf3, 0xe3, 0xc3},  //N
  {0x3c, 0x7e, 0x66, 0x66, 0x66, 0x7e, 0x3c},  //O
  {0x3e, 0x7e, 0x66, 0x7e, 0x3e, 0x6, 0x6},    //P
  {0x1e, 0x3f, 0x33, 0x3b, 0x33, 0x7f, 0x9e},  //Q
  {0x3e, 0x7e, 0x66, 0x7e, 0x1e, 0x36, 0x66},  //R
  {0x3c, 0x7e, 0x6, 0x7e, 0x60, 0x7e, 0x3c},   //S
  {0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18},  //T
  {0x66, 0x66, 0x66, 0x66, 0x66, 0x7e, 0x3c},  //U
  {0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},  //V
  {0xc3, 0xc3, 0xc3, 0xdb, 0xdb, 0xff, 0x66},  //W
  {0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3},  //X
  {0xc3, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x18},  //Y
  {0x7e, 0x7e, 0x30, 0x18, 0xc, 0x7e, 0x7e},   //Z
  {0x3c, 0x3c, 0xc, 0xc, 0xc, 0x3c, 0x3c},     //[
  {0x2, 0x6, 0xc, 0x18, 0x30, 0x60, 0x40},     //
  {0x3c, 0x3c, 0x30, 0x30, 0x30, 0x3c, 0x3c},  // 
  {0x18, 0x3c, 0x66, 0xc3, 0x0, 0x0, 0x0},     //^
  {0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff},       //_
  {0x4, 0xc, 0x18, 0x10, 0x0, 0x0, 0x0},       //`
  {0x18, 0x3c, 0x66, 0xc3, 0xff, 0xc3, 0xc3},  //A
  {0x3e, 0x66, 0x7e, 0x3e, 0x66, 0x7e, 0x3e},  //B
  {0x3c, 0x7e, 0x6, 0x6, 0x6, 0x7e, 0x3c},     //C
  {0x3e, 0x7e, 0x66, 0x66, 0x66, 0x7e, 0x3e},  //D
  {0x7e, 0x7e, 0x6, 0x3e, 0x6, 0x7e, 0x7e},    //E
  {0x7e, 0x7e, 0x6, 0x3e, 0x3e, 0x6, 0x6},     //F
  {0x3c, 0x7e, 0x6, 0x76, 0x46, 0x7e, 0x3c},   //G
  {0x66, 0x66, 0x66, 0x7e, 0x7e, 0x66, 0x66},  //H
  {0x7e, 0x7e, 0x18, 0x18, 0x18, 0x7e, 0x7e},  //I
  {0x7e, 0x7e, 0x30, 0x30, 0x36, 0x3e, 0x1c},  //J
  {0x66, 0x36, 0x3e, 0x1e, 0x3e, 0x36, 0x66},  //K
  {0x6, 0x6, 0x6, 0x6, 0x6, 0x7e, 0x7e},       //L
  {0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3},  //M
  {0xc3, 0xc7, 0xcf, 0xdb, 0xf3, 0xe3, 0xc3},  //N
  {0x3c, 0x7e, 0x66, 0x66, 0x66, 0x7e, 0x3c},  //O
  {0x3e, 0x7e, 0x66, 0x7e, 0x3e, 0x6, 0x6},    //P
  {0x1e, 0x3f, 0x33, 0x3b, 0x33, 0x7f, 0x9e},  //Q
  {0x3e, 0x7e, 0x66, 0x7e, 0x1e, 0x36, 0x66},  //R
  {0x3c, 0x7e, 0x6, 0x7e, 0x60, 0x7e, 0x3c},   //S
  {0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18},  //T
  {0x66, 0x66, 0x66, 0x66, 0x66, 0x7e, 0x3c},  //U
  {0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},  //V
  {0xc3, 0xc3, 0xc3, 0xdb, 0xdb, 0xff, 0x66},  //W
  {0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3},  //X
  {0xc3, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x18},  //Y
  {0x7e, 0x7e, 0x30, 0x18, 0xc, 0x7e, 0x7e},   //Z
  {0x30, 0x18, 0x18, 0x3c, 0x18, 0x18, 0x30},  //{
  {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},  //|
  {0xc, 0x18, 0x18, 0x3c, 0x18, 0x18, 0xc},    //}
  {0x0, 0x0, 0xcc, 0x7e, 0x33, 0x0, 0x0},      //~
}; 
  
void setup() {
  //initialise the pins. All output
  pinMode(pinData, OUTPUT);
  pinMode(pinClock, OUTPUT);
  pinMode(pinEnable, OUTPUT);
  pinMode(pinRow1, OUTPUT);
  pinMode(pinRow2, OUTPUT);
  pinMode(pinRow4, OUTPUT);
}

void selectRow(int row){
  //Select the given row
  digitalWrite(pinRow1, row & 1);
  digitalWrite(pinRow2, row & 2);
  digitalWrite(pinRow4, row & 4);
}

void pulseRow(int pulseTimeUS){
  
  digitalWrite(pinEnable, LOW);
  delayMicroseconds(pulseTimeUS);
  digitalWrite(pinEnable, HIGH);  
  
}

void rowOut(int *rowData){
  int i;
  //Loop over all columns
  for (i = 0; i<= COLS-1; i++){
    //Set data pin high
    digitalWrite(pinData, *rowData++);
    //Pulse clock
    delayMicroseconds(2);    
    digitalWrite(pinClock, HIGH);
    delayMicroseconds(2);
    digitalWrite(pinClock, LOW);    
  }
}

void rowOutShift(int *rowData, int shift){

  int loopLimit, loopStart;
  
  if (shift<=0){
    int s;
    //Set data pinlow to shift out extra data
    digitalWrite(pinData, LOW);    
    for (s = 0; s<= -shift-1; s++){
      //Pulse clock
      delayMicroseconds(2);    
      digitalWrite(pinClock, HIGH);
      delayMicroseconds(2);
      digitalWrite(pinClock, LOW);    
    } 
    loopLimit = COLS-1+shift;
    loopStart = 0;
  }
  else{
    loopLimit = COLS-1;
    loopStart = shift;
  }
  int i;
  //Loop over all columns

  rowData+=loopStart;

  for (i = loopStart; i<= loopLimit; i++){
    //Set data pin
    digitalWrite(pinData, *rowData++);
    //Pulse clock
    delayMicroseconds(2);    
    digitalWrite(pinClock, HIGH);
    delayMicroseconds(2);
    digitalWrite(pinClock, LOW);    
  }
  
  if (shift > 0){
    digitalWrite(pinData, LOW);   
     int s; 
    for (s = 0; s<= shift-1; s++){
      digitalWrite(pinData, *rowData++);      
      //Pulse clock

      delayMicroseconds(2);    
      digitalWrite(pinClock, HIGH);
      delayMicroseconds(2);
      digitalWrite(pinClock, LOW);    
    } 
  }
}

unsigned long lastTime = 0;

char *text = "         This is a test message that I would like to scroll across the screen. To change text at run time, set text to point to a different string.         ";

void generateFrame(int scroll){
  char *textPos = text;
  textPos += scroll / (CCOLS+1);
  scroll = scroll % (CCOLS+1);
  int row, col;
  for (row = 0; row<= ROWS-1; row++){  
    for (col = 0; col<= COLS+CCOLS-1; col++){
      frame[row][col] = font[textPos[col/(CCOLS+1)]][row]&(1<<(col%(CCOLS+1)));
    }
  }
}

int shift = 0;

void textLoop(){
  if (millis()-TIMESTEP > lastTime){
    //shift
    shift++;
    if (shift > SHIFTLIMIT){
      shift = 0;
    }
    generateFrame(shift);
    lastTime = millis();
  }
  
  int row;
  for(row = 0; row <= ROWS-1; row++){
    selectRow(ROWS-1-row);
    rowOutShift(frame[row], shift%(CCOLS+1));
    pulseRow(PULSETIME);
  }
}



void loop() {
  textLoop();
}
