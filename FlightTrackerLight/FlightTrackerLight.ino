#include "Config.h"
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>


#include <ESP8266WiFi.h>
//#include <WiFi.h>
#include <ESP_Mail_Client.h>

//************ GLOBAL VALUES ********************
//Wifi values
const char *ssid     = CONFIG_WIFI_SSID; //pulled from Config file - update to your implementation
const char *password = CONFIG_WIFI_PASSWORD;

//Board values
const uint16_t PixelCount = 46; // the number of pixeles in the strip
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

//IMAP global variables
IMAPSession imap; // The IMAP Session object used for Email reading 
IMAP_Config config;

long lastConnectTime; //used to make sure the imap email listener connection doesn't timeout. 

//********* FUNCTION DEFINITIONS FROM OTHER FILES ********
//boardPrinter function definitions
void printToBoardUnitTests();
void boardPrinterSetup();
void printFourCornerDots(boolean doDelay, RgbColor colorToPrint);
void printScrollMessage(String messageToPrint, RgbColor colorToPrint, boolean printFourCorners, RgbColor dotColors);
void printTwoCharacters(char firstChar, char secondChar, RgbColor colorToPrint);
void wipeBoard();

//*************** FUNCTION DEFINITIONS ***************
void imapCallback(IMAP_Status status); // Callback function to get the Email reading status /
void printSelectedMailboxInfo(SelectedFolderInfo sFolder);
void printPollingStatus(IMAPSession &imap);
void messageParsingUnitTests();
void alertHandleUnitTest(); 
void reboot();
void hw_wdt_disable();


void setup() {

  //set up serial connection
 Serial.begin(115200);
    while (!Serial); // wait for serial attach

    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();

    hw_wdt_disable(); //turn off watchdog (sometimes used for reboot, so may be left on)

 // set board; resets all the neopixels to an off state 
    strip.Begin();
    strip.Show();
    
  

//set up wifi 
    Serial.print("Connecting to wifi");
   // WiFi.disconnect();
   // WiFi.mode(WIFI_STA);
    WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);
    while ( WiFi.status() != WL_CONNECTED ) { 
      printTwoCharacters('I',0,RgbColor(10,10,10)); //indicator LEDs to confirm power and Wifi connection
      strip.Show();
      delay ( 250 );
      Serial.print ( "." );
      wipeBoard();
      strip.Show();
      delay (250);
    }
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

  //set up the imap values
  imap.debug(1); //turn on debug over serial 
  imap.callback(imapCallback); //Set the callback function to get the reading results

  //set up imap session data 
  ESP_Mail_Session session;

  session.server.host_name = CONFIG_IMAP_HOST;
  session.server.port = CONFIG_IMAP_PORT;
  session.login.email = CONFIG_EMAIL_ADRESS;
  session.login.password = CONFIG_EMAIL_PASSWORD;

  //set up the config file. See the examples from the library for details
 /* //config.fetch.set_seen = true;
  config.search.criteria = "";
  config.search.unseen_msg = true; //search unread emails too
  config.storage.saved_path = "/email_data";
  config.storage.type = esp_mail_file_storage_type_none;
  //config.storage.type = esp_mail_file_storage_type_flash;
  config.download.header = true;
  config.download.text = false;
  config.download.html = false;
  config.download.attachment = false;
  config.download.inlineImg = false;
  config.enable.html = false;
  config.enable.text = true;
  config.enable.recent_sort = true; //sort the result by message UID in the ascending order 
  config.enable.download_status = true; //report download status via serial port
  config.limit.search = 5;
  config.limit.msg_size = 512;
  config.limit.attachment_size = 1024 * 1024 * 5;*/

  // Connect to server with the session and config 
    if (!imap.connect(&session, &config))
        return;

  //  printAllMailboxesInfo(imap);
 
   //Open or select the mailbox folder to read or search the message
    if (!imap.selectFolder("Inbox/FlightAware"))
        return;
     printSelectedMailboxInfo(imap.selectedFolder());

    lastConnectTime = millis();
     
}



void loop() {
  //alertHandleUnitTest(); //run unit tests

  //check for reboot
  if(millis() > (24*60*60*1000)){
    Serial.println("24 hours elapsed - rebooting");
    reboot(); 
  }

  //refresh the connection to mail every 10 min to make sure it isn't closed by server
  if((millis() - lastConnectTime)>(3*60*1000)){
    imap.stopListen();
    delay(250);
    imap.listen();
    lastConnectTime = millis();
  }
  
  //Listen for mailbox changes
    if (!imap.listen()){
      printTwoCharacters('?','?',RgbColor(25,5,1)); //print error on screen
      strip.Show();
      return;
    }
   // Serial.println(".");

    //Check the changes
    if (imap.folderChanged())
        printPollingStatus(imap);

    //To stop listen, use imap.stopListen(); and to listen again, call imap.listen()*/
    delay(50);
}



/* Callback function to get the Email reading status */
void imapCallback(IMAP_Status status)
{
   
   //Serial.println("reading email");
   /* Print the current status */
   Serial.println(status.info());
   if (status.success())
   {
       /* Print the result */
       /* Get the message list from the message list data */
       IMAP_MSG_List msgList = imap.data();
       IMAP_MSG_Item msg = msgList.msgItems[0];
       ESP_MAIL_PRINTF("Subject: %s\n", msg.subject);
       String alertText = msg.subject;
       alertText.toUpperCase();
       imap.empty();
       imap.listen();
       handleAlert(alertText);
       //printMessages(msgList.msgItems, imap.headerOnly());
       /* Clear all stored data in IMAPSession object */
       
    }
    
}

void handleAlert(String alertText){
  Serial.println("processing alert text: '"+alertText+"'");
  RgbColor dotColor;
  if(alertText.indexOf("DEPARTED") != -1){
     dotColor = RgbColor(2,2,25);//blue
     
     //play loading symbol
     printFourCornerDots(true, dotColor);
     
     //assume up to first space is flight name/number
     String flightCode = alertText.substring(0,alertText.indexOf(" "));
     printScrollMessage(flightCode, getAirlineColor(flightCode), true, dotColor); 
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(750);
     
     printTwoCharacters('D','P',dotColor); //departed
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(1000);
     wipeBoard();
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(750);
     int pivot = alertText.indexOf("DEPARTED ")+9;
     
     //assume characters after "departed" are airport code
     printScrollMessage(alertText.substring(pivot,alertText.indexOf(" ",pivot)), dotColor, true, dotColor); 

     //clean up well
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(750);
     wipeBoard();
     delay(500);

  }
  else if(alertText.indexOf("ARRIVED") != -1){
     dotColor = RgbColor(5,25,3);//green
     
     //play loading symbol
     printFourCornerDots(true, dotColor);
     
     //assume up to first space is flight name/number
     String flightCode = alertText.substring(0,alertText.indexOf(" "));
     printScrollMessage(flightCode, getAirlineColor(flightCode), true, dotColor); 
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(750);
     
     printTwoCharacters('A','R',dotColor); //arrived
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(1000);
     wipeBoard();
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(750);
     int pivot = alertText.indexOf("ARRIVED AT ")+11;
     
     //assume characters after "arrived at" are airport code
     printScrollMessage(alertText.substring(pivot,alertText.indexOf(" ",pivot)), dotColor, true, dotColor); 

     //clean up well
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(750);
     wipeBoard();
     delay(500);
  }
  else if(alertText.indexOf("FILED") != -1 || alertText.indexOf("CHANGED") != -1){
    dotColor = RgbColor(25,25,1);//yellow
     //play loading symbol
     printFourCornerDots(true, dotColor);
     
     //assume up to first space is flight name/number
     String flightCode = alertText.substring(0,alertText.indexOf(" "));
     printScrollMessage(flightCode, getAirlineColor(flightCode), true, dotColor); 
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(750);
     
     printScrollMessage("CHANGE", dotColor, true, dotColor); 

     //clean up well
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(750);
     wipeBoard();
     delay(500);  
  }
  else if(alertText.indexOf("CANCELLED") != -1){
     dotColor = RgbColor(30,1,1);//red
    //play loading symbol
     printFourCornerDots(true, dotColor);
     
     //assume up to first space is flight name/number
     String flightCode = alertText.substring(0,alertText.indexOf(" "));
     printScrollMessage(flightCode, getAirlineColor(flightCode), true, dotColor); 
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(750);
     
     printScrollMessage("CANCELLED", dotColor, true, dotColor); 

     //clean up well
     printFourCornerDots(false,dotColor);
     strip.Show();
     delay(750);
     wipeBoard();
     delay(500);
  }

}

void printSelectedMailboxInfo(SelectedFolderInfo sFolder)
{
    /* Show the mailbox info */
    ESP_MAIL_PRINTF("\nInfo of the selected folder\nTotal Messages: %d\n", sFolder.msgCount());
    ESP_MAIL_PRINTF("Predicted next UID: %d\n", sFolder.nextUID());
    for (size_t i = 0; i < sFolder.flagCount(); i++)
        ESP_MAIL_PRINTF("%s%s%s", i == 0 ? "Flags: " : ", ", sFolder.flag(i).c_str(), i == sFolder.flagCount() - 1 ? "\n" : "");
}


void printAllMailboxesInfo(IMAPSession &imap)
{
    /* Declare the folder collection class to get the list of mailbox folders */
    FoldersCollection folders;

    /* Get the mailbox folders */
    if (imap.getFolders(folders))
    {
        for (size_t i = 0; i < folders.size(); i++)
        {
            /* Iterate each folder info using the  folder info item data */
            FolderInfo folderInfo = folders.info(i);
            ESP_MAIL_PRINTF("%s%s%s", i == 0 ? "\nAvailable folders: " : ", ", folderInfo.name, i == folders.size() - 1 ? "\n" : "");
        }
    }
}



void printPollingStatus(IMAPSession &imap)
{
    /* Declare the selected folder info class to get the info of selected mailbox folder */
    SelectedFolderInfo sFolder = imap.selectedFolder();

    /* Show the mailbox info */
    ESP_MAIL_PRINTF("\nMailbox status changed\n----------------------\nTotal Messages: %d\n", sFolder.msgCount());

    if (sFolder.pollingStatus().type == imap_polling_status_type_new_message)
    {

        ESP_MAIL_PRINTF("New message %d, has been addedd, reading message...\n", (int)sFolder.pollingStatus().messageNum);

        //if (sFolder.recentCount() > 0)
        //    ESP_MAIL_PRINTF("\nMesssage count which recent flag set: %d\n", sFolder.recentCount());

        //we need to stop polling before do anything
        imap.stopListen();

        //Get the UID of new message and fetch
        String uid = String(imap.getUID(sFolder.pollingStatus().messageNum));
        config.fetch.uid = uid.c_str();
        MailClient.readMail(&imap, false);
    }
    else if (sFolder.pollingStatus().type == imap_polling_status_type_remove_message)
        ESP_MAIL_PRINTF("Message %d, has been removed\n\n", (int)sFolder.pollingStatus().messageNum);
    else if (sFolder.pollingStatus().type == imap_polling_status_type_fetch_message)
        ESP_MAIL_PRINTF("Message %d, has been fetched with the argument %s\n\n", (int)sFolder.pollingStatus().messageNum, sFolder.pollingStatus().argument.c_str());
}

void alertHandleUnitTest(){
    String testString = "FLE223 has departed YYZ for YVR";
    testString.toUpperCase();
    handleAlert(testString);
    delay(1000);

    testString = "C-GYNO departed YTZ at 08:05PM EST";
    testString.toUpperCase();
    handleAlert(testString);
    delay(1000);

    testString = "WJA705 flight to YVR has been cancelled";
    testString.toUpperCase();
    handleAlert(testString);
    delay(1000);

    testString = "ACA131 flight information has changed";
    testString.toUpperCase();
    handleAlert(testString);
    delay(1000);

    testString = "POE269 arrived at YOW from YTZ";
    testString.toUpperCase();
    handleAlert(testString);
    delay(1000);
}

RgbColor getAirlineColor(String flightCode){
  if(flightCode.startsWith("ACA")){
    return RgbColor(25,1,1); //air canada, deep red
  }
  else if(flightCode.startsWith("WJA")){
    return RgbColor (4,20,20); //westject, turqoise
  }
  else if(flightCode.startsWith("POE")){
    return RgbColor (1,7,31); //porter, deep blue
  }
  else if(flightCode.startsWith("FLE")){
    return RgbColor(31,3,26); //flair - purple
  }
  else{
    return RgbColor (15,15,15);//other - white
  }
}

//workaround for a bug where subsequent emails aren't noticed
void resetIMAP(){
  if (imap.folderChanged())
        imap.empty(); 
}


void reboot() {
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while (1) {} //force an infinite loop to tigger watchdog
}


void hw_wdt_disable(){
  *((volatile uint32_t*) 0x60000900) &= ~(1); // Hardware WDT OFF
}

/*
void hw_wdt_enable(){
  *((volatile uint32_t*) 0x60000900) |= 1; // Hardware WDT ON
}*/
