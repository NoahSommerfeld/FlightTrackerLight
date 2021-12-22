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



//*************** FUNCTION DEFINITIONS ***************
void imapCallback(IMAP_Status status); // Callback function to get the Email reading status /
void printSelectedMailboxInfo(SelectedFolderInfo sFolder);
void printPollingStatus(IMAPSession &imap);


void setup() {


//set up serial connection
 Serial.begin(115200);
    while (!Serial); // wait for serial attach

    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();


 // set board; resets all the neopixels to an off state 
    strip.Begin();
    strip.Show();

    
//set up wifi 
    Serial.print("Connecting to wifi");
   // WiFi.disconnect();
   // WiFi.mode(WIFI_STA);
    WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);
  //  updateBoard(RgbColor(0,0,0));
    while ( WiFi.status() != WL_CONNECTED ) { 
      strip.SetPixelColor(5,RgbColor(10,10,10)); //indicator LED to confirm power and Wifi connection
      strip.Show();
      delay ( 250 );
      Serial.print ( "." );
      strip.SetPixelColor(5,RgbColor(0,0,0));
      strip.Show();
      delay (250);
    }
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  //  updateBoard(RgbColor(0,0,0));

  //set up the imap values
  imap.debug(1); //turn on debug over serial 
  imap.callback(imapCallback); //Set the callback function to get the reading results



  //set up imap session data 
  ESP_Mail_Session session;

  /*
  session.server.host_name = IMAP_HOST.c_str();
  session.server.port = IMAP_PORT;
  session.login.email = IMAP_EMAIL.c_str();
  session.login.password = IMAP_PASSWORD.c_str(); */
  
  session.server.host_name = CONFIG_IMAP_HOST;
  session.server.port = CONFIG_IMAP_PORT;
  session.login.email = CONFIG_EMAIL_ADRESS;
  session.login.password = CONFIG_EMAIL_PASSWORD;


  //set up the config file. See the examples from the library for details
 // IMAP_Config config;
  //config.fetch.set_seen = true;
  config.search.criteria = "";
  config.search.unseen_msg = true; //search unread emails too
  config.storage.saved_path = "/email_data";
  //config.storage.type = esp_mail_file_storage_type_none;
  config.storage.type = esp_mail_file_storage_type_flash;
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
  config.limit.attachment_size = 1024 * 1024 * 5;

  Serial.println("NOAH - config values set");
  /* Connect to server with the session and config */
    if (!imap.connect(&session, &config))
        return;
 Serial.println("connected");

    printAllMailboxesInfo(imap);
 
    /* Open or select the mailbox folder to read or search the message */
    if (!imap.selectFolder("Inbox/FlightAware"))
        return;
         Serial.println("found folder");
     printSelectedMailboxInfo(imap.selectedFolder());
  //imap.empty();
}

void loop() {
  // Start of loop indicator
      strip.SetPixelColor(10,RgbColor(10,10,60)); 
      strip.Show();
      delay ( 250 );
      strip.SetPixelColor(10,RgbColor(0,0,0));
      strip.Show();
      delay (250);


  //Listen for mailbox changes
    if (!imap.listen())
        return;

    //Check the changes
    if (imap.folderChanged())
        printPollingStatus(imap);

    //To stop listen, use imap.stopListen(); and to listen again, call imap.listen()
      
}



/* Callback function to get the Email reading status */
void imapCallback(IMAP_Status status)
{
   
   Serial.println("reading email");
   /* Print the current status */
   Serial.println(status.info());
   if (status.success())
   {
       /* Print the result */
       /* Get the message list from the message list data */
       IMAP_MSG_List msgList = imap.data();
       IMAP_MSG_Item msg = msgList.msgItems[0];
        ESP_MAIL_PRINTF("Subject: %s\n", msg.subject);
       //printMessages(msgList.msgItems, imap.headerOnly());
       /* Clear all stored data in IMAPSession object */
      Serial.println("success");
       imap.empty();
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