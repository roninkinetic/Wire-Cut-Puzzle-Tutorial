// all Ardunio is C++ programming language.
// this is the header section where we declare what Header files to include.
// headers are pre-written bits of code that you can reference and use inside the app you are building
// headers files provide access to all of the arduino accessories using each's pre-written C++ header file.
// it is possible you don't need any headers at all


// this is an array of integer. we want to set the max value to however many digital pins there are on the control board, plus 1.
// arrays "index" start at 0, so when set to wireValue[14], the array is accessed as wireValue[0] to wireValue[13].
// adding +1 to our maximum number of digital pins lets us map it directly pin # to pin #. this will make more sense in the setup() function
int wireValue[14];

// this is a representation of 1 second in milliseconds and is used for the countdown timer "tick"
const unsigned long refreshInterval = 1L * 1000L; // delay between updates, in milliseconds
// this is the fresh rate used in timing
unsigned long lastRefreshTime = 0;

int timerCount = 90*60; // 90 minutes * 60 seconds

int timerRamp = 1;
int brokenWireCount = 0;

boolean countdownReached = false;
boolean displayTriggered = false;

// if we create them on the fly later in functions, it will result in a "memory leak".
// a memory leak is where we keep allocating space in memory for a variable, and run out of memory over time.
// this is a fatal flaw in many, many, many programs.
// so by creating it here as a "global declaration", it will only ever use 1 place in memory, where we will continually write new values as we need them


// setup is the first function that runs
void setup() {
   Serial.begin(115200);
   // now lets setup digital pins. this is assuming the wires to cut are wired to this digital pins.
   // to setup wire cuts, a wire simply has to connect any digital pin to the ground, and they can all share a common ground.
   // we want to set the digital pins to PULLUP mode. then we will read the pin and store its current value to an array of pin values
   pinMode(1, INPUT_PULLUP);
   wireValue[1] = digitalRead(1);
   pinMode(2, INPUT_PULLUP);
   wireValue[2] = digitalRead(2);
   pinMode(3, INPUT_PULLUP);
   wireValue[3] = digitalRead(3);
   pinMode(4, INPUT_PULLUP);
   wireValue[4] = digitalRead(4);
   pinMode(5, INPUT_PULLUP);
   wireValue[5] = digitalRead(5);
   pinMode(6, INPUT_PULLUP);
   wireValue[6] = digitalRead(6);
   pinMode(7, INPUT_PULLUP);
   wireValue[7] = digitalRead(7);
   pinMode(8, INPUT_PULLUP);
   wireValue[8] = digitalRead(8);

  // that's it for initializing the pins
  // if there is a display to setup, the code goes here  

} // end of setup()

void loop() {
  // scan wires on 1 second intervals
  // as long as there's time left
  if(timerCount > 0)
  {
    if (millis() - lastRefreshTime > refreshInterval) {
      lastRefreshTime += refreshInterval;
      scanWires();
    }
  }

  // self explanatory, trigger the failure animation if it has not fired already.
  if(countdownReached && !displayTriggered)
  {
    triggerDisplay();
  }  
}


// this is where we do all of the heavy lifting on the wires
void scanWires()
{
  // expand this section for the wires cut that accelerate the timer
  wireValue[4] = digitalRead(4);
  Serial.print(wireValue[4]);  
  wireValue[5] = digitalRead(5);
  Serial.println(wireValue[5]); 

  // set our counts to the initial values
  timerRamp = 1;
  brokenWireCount = 0;

  // expand this section also for the wires cut that accelerate the timer
  if(wireValue[4] == 1)
  {
      brokenWireCount++;
  }
  if(wireValue[5] == 1)
  {
      brokenWireCount++;
  }

  // so far only the first 2 bumps in time are set.
  // this section is expanded with case 3, case 4, etc and you can tune your curve with timerRamp = #.
  switch(brokenWireCount) {
    case 1:
      timerRamp = 10;
      break;
    case 2:
      timerRamp = 100;
      break;
    default:
      timerRamp = 1;
  }
  
  tickTimer();
  Serial.println(timerCount);
} // end of scanWires()

// decrements the timerRamp from the timerCount, called at the end of scanWires()
void tickTimer()
{
  timerCount -= timerRamp; 
  if(timerCount <= 0)
  {
    countdownReached = true;
  }
} // end of tickTimer()

// animations, etc, when countdown timer is reached
void triggerDisplay() {
  displayTriggered = true;
  // animation for triggered event goes here
  Serial.println("Failure Event Triggered");
} // end of triggerDisplay()
