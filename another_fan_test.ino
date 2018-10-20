int NbTopsFan;      //Varibles used for RPM calculations
int CalculateRMP;           //the rmp calculated
int hallsensor = 2; //The pin location of the RPM sensor??? no it's not
               
typedef struct{                  //Defines the structure for multiple fans and their dividers
  char fantype;
  unsigned int fandiv;
}fanspec;

fanspec fanspace[3]={{0,1},{1,2},{2,8}}; //Definitions of the fans

char fan = 1;   //This is the varible used to select the fan and it's divider, set 1 for unipole hall effect sensor 
               //and 2 for bipole hall effect sensor 

void rpm ()      //This is the function that the interupt calls 
{ 
 NbTopsFan++; 
}

const long intervals = 124;
long currentTime;
long previousTime = 0;

boolean enabled = false;

int fanVal;
int lastFanVal = 0;

void setup() {
  Serial.begin(115200);
  attachInterrupt(0, rpm, RISING);
}

void loop() {
    //FAN STUFF-------------------------------------------------------------
    currentTime = millis();

    if(enabled == false){
     NbTopsFan = 0;  //Set NbTops to 0 ready for calculations
     sei();   //Enables interrupts
     enabled = true;
    }

   if(currentTime - previousTime >= intervals){
     previousTime = currentTime;
     cli();   //Disable interrupts
     enabled = false;
     CalculateRMP = ((NbTopsFan * 480)/fanspace[fan].fandiv);
     if(CalculateRMP > 3600)
      CalculateRMP = 3600;
      
     fanVal = map(CalculateRMP, 0, 3600, 0, 123);
     if(fanVal > lastFanVal + 3 || fanVal < lastFanVal - 3){
      MIDIMessage(174, 1, fanVal);
      lastFanVal = fanVal;
     }
   }
}


void MIDIMessage(byte command, byte data1, byte data2) //pass values out through standard Midi Command
{
   Serial.write(command);
   Serial.write(data1);
   Serial.write(data2);
}
