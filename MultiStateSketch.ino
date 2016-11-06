/*
 Basic example of a multi-state program (aka finite state machine)
 The state or "mode" which the Esplora is in is defined by
 integer "state", where
 state = 0 : Red light flashes. Button 1 goes to >
 state = 1 : Blue light flashes. Button 1 goes to >
 state = 2 : Repetitively plays a cheerful tone, and
   - Button 1 goes to >
     state = 3: Plays a sad tone and returns back to state = 2 (no button input required)
   - Button 2 goes back to state = 0 
 
 This can be useful if you need your inputs or buttons
 to do more than one function, depending on on its previous
 state it was in.
 
 modes are evaluated by using a while loop
 ( https://www.arduino.cc/en/Reference/While )
 
 Use functions to segment your code into neater blocks
 ( https://www.arduino.cc/en/Reference/FunctionDeclaration )
 
*/

//Global Variables
int state=0;

#include <Esplora.h>



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {  //Press button 1 to switch through different modes
  Function0(); //Scroll down to see what Function1 does
  Function1(); //Scroll down to see what Function2 does
  Function2(); //Scroll down to see what Function3 does
  Function3(); //Only runs when in Function3
}


void Function0(){
  // This loop only runs if state is equal to 0
  // It stops looping when the state is no longer
  // equal to 0.
  while(state==0){
    
    Heartbeat(); //Flashes light red (heartbeat)
    
    //If button 1 is pressed change to state 1.
    if (Esplora.readButton(SWITCH_1)==LOW){
      state=1;
      delay(100);
    }
    
  // if no change in state: this block loops again
  }
}
void Function1(){
  // This loop only runs if state is equal to 1
  // It stops looping when the state is no longer
  // equal to 1.
  while(state==1){
    Breathe();  //This mode makes a blue light glow (breathe)

    //If button 1 is pressed change state to 2.
    if (Esplora.readButton(SWITCH_1)==LOW){
      state=2;
      delay(100);
    }
  }
}

void Function2(){
  // This loop only runs if state is equal to 2
  // It stops looping when the state is no longer
  // equal to 2.
  while(state==2){
    Esplora.writeRGB(255,255,0); //make the light yellow
    
    Chirp(); //This mode makes a cheerful tune (see below)
    delay(1000);
    
    //If button 1 is pressed Function3 plays and brings us back here
    if (Esplora.readButton(SWITCH_1)==LOW){
      state=3; //go to function4
      delay(100);
    }
    //If button 2, jump back to beginning
    else if(Esplora.readButton(SWITCH_2)==LOW){
      state=0; 
    }
    
    // if no change in state: this block loops again
  }
}

void Function3(){
  while(state==3){
    
    Esplora.writeRGB(255,120,0); //Make light orange
    Fail();//This mode makes a sad tune
    
    //Example message:
    Serial.println("Invalid input :(. Try again.");
    
    state=2; //plays once and goes back to Function2 (irrespective of any button input)
    
    //note: since this only plays once, we could do the same by wrapping this in an if statement
    // instead of a while loop
  }
}


/*
  Light Effect Functions
*/

//Red heartbeat flashing
void Heartbeat(){
  Esplora.writeRGB(255,0,0);
  delay(100);
  Esplora.writeRGB(0,0,0);
  delay(100);
  Esplora.writeRGB(255,0,0);
  delay(200);
  Esplora.writeRGB(0,0,0);
  delay(500);
}

//Blue slow glow (like breathing)
void Breathe(){
  for (int i =0; i <256; i++){
    Esplora.writeRGB(0,0,i);
  }
  for (int i =255; i >=0; i--){
    Esplora.writeRGB(0,0,i);
  }
}

/*
  Sound Effect Functions
*/

// Plays a happy tune
void Chirp(){
  for (int i=512; i<=2048; i=i+256){
    Esplora.tone(i);
    delay(100);
  }
  Esplora.noTone();
}

//Plays a sad tune
void Fail(){
  Esplora.tone(380);
  delay(100);
  Esplora.noTone();
  delay(20);
  Esplora.tone(220);
  delay(500);
  Esplora.noTone();
}
