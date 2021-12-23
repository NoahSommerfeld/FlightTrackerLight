
//function definitions
void printToBoardUnitTests();

typedef struct { 
  char letter;
  int ledCount;
  int leds[15];
} letterLEDmapping;

const letterLEDmapping LEDAlphabet[] {
    {'A', 3, {1,2,3}},
    {'B', 3, {3,4,5}}
};

//Array of structs called the 'alphabet'

//define a struct containing character and an array of ints


void boardPrinterSetup(){
 //void loadStruct(); 
}

void printToBoardUnitTests(){
    String testString = "FLE223 has departed YYZ for YVR";
    testString.toUpperCase();
    printToBoard(testString);
    delay(1000);

    testString = "C-GYNO departed YTZ at 08:05PM EST";
    testString.toUpperCase();
    printToBoard(testString);
    delay(1000);

    testString = "WJA705 flight to YVR has been cancelled";
    testString.toUpperCase();
    printToBoard(testString);
    delay(1000);

    testString = "ACA131 flight information has changed";
    testString.toUpperCase();
    printToBoard(testString);
    delay(1000);

    testString = "POE269 arrived at YOW from YTZ";
    testString.toUpperCase();
    printToBoard(testString);
    delay(1000);
}
