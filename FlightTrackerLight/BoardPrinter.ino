const int alphabetSize = 37;

typedef struct { 
  char letter;
  int ledCount;
  int leds[15];
} letterLEDmapping;

//each letter is defined by indicating leds to be lit up (up to 15). 
//each position is assuming the left grouping of 15 (of 2 possible groupings on the board)
const letterLEDmapping LEDAlphabet[] {
    {'A', 10, {8,14,20,26,33,28,22,16,10,21}},
    {'B', 10, {8,14,20,26,32,33,28,21,16,9}},
    {'C', 6, {28,27,20,14,9,10}},
    {'D', 10, {32,26,20,14,8,9,16,22,28,33}},
    {'E', 11, {34,33,32,26,20,21,22,14,8,9,10}},
    {'F', 8, {8,14,20,26,32,33,34,21}},
    {'G', 9, {34,33,26,20,14,9,16,22,21}},
    {'H', 11, {32,26,20,14,8,34,28,22,16,10,21}},
    {'I', 9, {32,33,34,27,21,15,9,8,10}},
    {'J', 2, {1,2}},
    {'K', 2, {1,2}},
    {'L', 2, {1,2}},
    {'M', 2, {1,2}},
    {'N', 2, {1,2}},
    {'O', 2, {1,2}},
    {'P', 2, {1,2}},
    {'Q', 2, {1,2}},
    {'R', 2, {1,2}},
    {'S', 2, {1,2}},
    {'T', 2, {1,2}},
    {'U', 2, {1,2}},
    {'V', 2, {1,2}},
    {'W', 2, {1,2}},
    {'X', 2, {1,2}},
    {'Y', 2, {1,2}},
    {'Z', 2, {1,2}},
    {'1', 2, {1,2}},
    {'2', 2, {1,2}},
    {'3', 2, {1,2}},
    {'4', 2, {1,2}},
    {'5', 2, {1,2}},
    {'6', 2, {1,2}},
    {'7', 2, {1,2}},
    {'8', 2, {1,2}},
    {'9', 2, {1,2}},
    {'0', 2, {1,2}},
    {'-', 2, {1,2}},
    {'?', 2, {1,2}}
};
    
void wipeboard(){
  for (int i = 0; i< PixelCount; i++){
    strip.SetPixelColor(i,RgbColor(0,0,0)); 
  }
  strip.Show();
}

void boardPrinterSetup(){
 printToBoardUnitTests();
}

void printTwoCharacters(char firstChar, char secondChar, RgbColor colorToPrint){
  //first letter
  if(firstChar != 0){ //note default char value is 0, which is different from '0'. 
    letterLEDmapping toPrint1;
      for (int i=0; i<alphabetSize; i++){
      if(LEDAlphabet[i].letter == firstChar){
        toPrint1 = LEDAlphabet[i];
        break;
      }
      else if (i == (alphabetSize -1)){
        toPrint1 = LEDAlphabet[i]; //do a question mark for unrecgonized charachters
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
        toPrint2 = LEDAlphabet[i]; //do a question mark for unrecgonized charachters
      }
    }

     for(int i=0; i<toPrint2.ledCount; i++){
      strip.SetPixelColor(toPrint2.leds[i]+3,colorToPrint); //+3 to shift to right position
     }
  }
}

void printToBoardUnitTests(){
   printAlphabet();
}

void printAlphabet(){
  RgbColor printColor = RgbColor(70,3,3);
  wipeboard();
  printTwoCharacters(0, LEDAlphabet[0].letter,printColor);
  strip.Show();
  delay (3000);
  
  for (int i=0; i<alphabetSize-1;i++){
    wipeboard();
    printTwoCharacters(LEDAlphabet[i].letter, LEDAlphabet[i+1].letter,printColor);
    strip.Show();
    delay(3000);
  }
  wipeboard();
  printTwoCharacters(LEDAlphabet[alphabetSize-1].letter, 0,printColor);
  strip.Show();
  delay (3000);
  wipeboard();
}
