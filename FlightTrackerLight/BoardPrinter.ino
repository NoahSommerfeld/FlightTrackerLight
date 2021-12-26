
const int alphabetSize = 38;
const int scrollspeed = 900; //speed between scrolling letters, in milliseconds

typedef struct { 
  char letter;
  int ledCount;
  int leds[15];
} letterLEDmapping;

//each letter is defined by indicating leds to be lit up (up to 15). 
//each position is assuming the left grouping of 15 (of 2 possible groupings on the board)
const letterLEDmapping LEDAlphabet[] {
    {'?', 7, {22,33,34,28,22,21,9}},
    {'A', 10, {8,14,20,26,33,28,22,16,10,21}},
    {'B', 10, {8,14,20,26,32,33,28,21,16,9}},
    {'C', 7, {34,33,20,14,9,10,26}},
    {'D', 10, {32,26,20,14,8,9,16,22,28,33}},
    {'E', 11, {34,33,32,26,20,21,22,14,8,9,10}},
    {'F', 8, {8,14,20,26,32,33,34,21}},
    {'G', 9, {34,33,26,20,14,9,16,22,21}},
    {'H', 11, {32,26,20,14,8,34,28,22,16,10,21}},
    {'I', 4, {9,15,21,33}}, //lower case
    {'J', 6, {34,28,22,16,9,14}},
    {'K', 9, {32,26,20,14,8,34,27,15,10}},
    {'L', 7, {32,26,20,14,8,9,10}},
    {'M', 12, {8,14,20,26,32,27,21,34,28,22,16,10}},
    {'N', 11, {32,26,20,14,8,34,28,22,16,10,21}},
    {'O', 8, {33,26,20,14,9,16,22,28}},
    {'P', 8, {8,14,20,26,32,33,28,21}},
    {'Q', 9, {33,26,20,15,22,28,21,16,10}},
    {'R', 10, {32,26,20,14,8,33,28,21,16,10}},
    {'S', 9, {34,33,32,26,21,16,9,8,10}},
    {'T', 7, {32,33,34,27,21,15,9}},
    {'U', 9, {26,20,14,8,9,10,16,22,28}},
    {'V', 7, {26,20,14,9,16,22,28}},
    {'W', 12, {32,26,20,14,8,15,21,10,16,22,28,34}},
    {'X', 9, {32,26,21,14,8,10,16,28,34}},
    {'Y', 9, {32,26,20,15,21,9,22,28,34}},
    {'Z', 9, {32,33,34,28,21,14,8,9,10}},
    {'1', 6, {26,33,27,21,15,9}},
    {'2', 11, {32,33,34,28,22,21,20,14,8,9,10}},
    {'3', 11, {32,33,34,28,22,21,20,16,10,9,8}},
    {'4', 9, {32,26,20,21,22,28,34,16,10}},
    {'5', 9, {34,33,32,26,20,21,16,9,8}},
    {'6', 12, {34,33,32,26,20,14,8,9,10,16,22,21}},
    {'7', 7, {32,33,34,28,22,16,10}},
    {'8', 14, {34,33,32,26,20,21,22,28,14,8,9,10,16,22}},
    {'9', 10, {34,33,32,26,20,21,22,28,16,10}},
    {'0', 8, {33,26,20,14,9,16,22,28}},
    {'-', 3, {20,21,22}}
};
    
void wipeBoard(){
  for (int i = 0; i< PixelCount; i++){
    strip.SetPixelColor(i,RgbColor(0,0,0)); 
  }
  strip.Show();
}

void printFourCornerDots(boolean doDelay, RgbColor colorToPrint){
  int printDelay = 0;
  if(doDelay){
    printDelay = scrollspeed;
  }
  strip.SetPixelColor(0,colorToPrint); 
  strip.Show();
  delay(printDelay);
  strip.SetPixelColor(42,colorToPrint);
  strip.Show(); 
  delay(printDelay);
  strip.SetPixelColor(45,colorToPrint); 
  strip.Show();
  delay(printDelay);
  strip.SetPixelColor(3,colorToPrint); 
  strip.Show();
  delay(printDelay);
}


void printScrollMessage(String messageToPrint, RgbColor colorToPrint, boolean printFourCorners, RgbColor dotColors){
  if (messageToPrint.length() < 2){
    return; //shouldn't happen...
  }
  
  wipeBoard();
  printTwoCharacters(0,messageToPrint.charAt(0), colorToPrint);
  if(printFourCorners){printFourCornerDots(false, dotColors);}
  strip.Show();
  delay (scrollspeed); 

  for (int i=0; i<messageToPrint.length()-1; i++){
    wipeBoard();
    printTwoCharacters(messageToPrint.charAt(i),messageToPrint.charAt(i+1), colorToPrint);
    if(printFourCorners){printFourCornerDots(false, dotColors);}
    strip.Show();
    delay (scrollspeed); 
  }
    wipeBoard();
    printTwoCharacters(messageToPrint.charAt(messageToPrint.length()-1),0, colorToPrint);
    if(printFourCorners){printFourCornerDots(false, dotColors);}
    strip.Show();
    delay (scrollspeed); 
    wipeBoard();
}

void printTwoCharacters(char firstChar, char secondChar, RgbColor colorToPrint){
  Serial.print("printing: '");
  if(firstChar != 0){
    Serial.print(String(firstChar));
  }else{
     Serial.print(" ");
  }
   if(secondChar != 0){
    Serial.print(String(secondChar));
  }else{
     Serial.print(" ");
  }
  Serial.println("'");
  
  //first letter
  if(firstChar != 0){ //note default char value is 0, which is different from '0'. 
    letterLEDmapping toPrint1;
      for (int i=0; i<alphabetSize; i++){
      if(LEDAlphabet[i].letter == firstChar){
        toPrint1 = LEDAlphabet[i];
        break;
      }
      else if (i == (alphabetSize -1)){
        toPrint1 = LEDAlphabet[0]; //do a question mark for unrecgonized characters
      }
    }

  for(int i=0; i<toPrint1.ledCount; i++){
    strip.SetPixelColor(toPrint1.leds[i],colorToPrint);
  }
  }

  //second letter
  if(secondChar != 0){
    letterLEDmapping toPrint2;
      for (int i=0; i<alphabetSize; i++){
      if(LEDAlphabet[i].letter == secondChar){
        toPrint2 = LEDAlphabet[i];
        break;
      }
      else if (i == (alphabetSize -1)){
        toPrint2 = LEDAlphabet[0]; //do a question mark for unrecgonized characters
      }
    }

     for(int i=0; i<toPrint2.ledCount; i++){
      strip.SetPixelColor(toPrint2.leds[i]+3,colorToPrint); //+3 to shift to right position
     }
  }
}

void printToBoardUnitTests(){
  // printAlphabet();
  printFourCornerDots(true, RgbColor(5,5,40));
  printScrollMessage("MERRY-CHRISTMAS-NOAH",RgbColor(40,5,5),true, RgbColor(5,5,40));
}

void printAlphabet(){
  RgbColor printColor = RgbColor(70,3,3);
  wipeBoard();
  printTwoCharacters(0, LEDAlphabet[0].letter,printColor);
  strip.Show();
  delay (3000);
  
  for (int i=0; i<alphabetSize-1;i++){
    wipeBoard();
    printTwoCharacters(LEDAlphabet[i].letter, LEDAlphabet[i+1].letter,printColor);
    strip.Show();
    delay(3000);
  }
  wipeBoard();
  printTwoCharacters(LEDAlphabet[alphabetSize-1].letter, 0,printColor);
  strip.Show();
  delay (3000);
  wipeBoard();
}
