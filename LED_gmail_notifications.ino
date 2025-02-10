#include <Arduino.h>

// ------ WiFi Includes ------
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

// ------ ESP_Mail_Client ------
#include <ESP_Mail_Client.h>

// ------ NeoPixel Includes ------
#include <Adafruit_NeoPixel.h>

// ---------- User Config ----------
// Replace with your actual WiFi and Gmail credentials.
#define WIFI_SSID       "WIFI_SSID_HERE"
#define WIFI_PASSWORD   "WIFI_PASSWORD_HERE"

// Gmail IMAP server settings
#define IMAP_HOST       "imap.gmail.com"
#define IMAP_PORT       993
#define GMAIL_ADDRESS   "EMAIL_ADDRESS_HERE"
#define GMAIL_PASSWORD  "GMAIL_APP_SPECIFIC_PASSWORD_HERE"

// ------ NeoPixel (WS2812B) Settings ------
#define LED_PIN   D4   // or GPIO2, etc. Adjust as needed
#define NUM_LEDS  64   // 8x8 matrix
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// ------ Simple 8x8 "Gmail" icon (hex = 0xRRGGBB) ------
static uint32_t gmailIcon[NUM_LEDS] = {
  // Row 1
  0x990030, 0x990030, 0x000000, 0x000000, 0x000000, 0x000000, 0xFFC20E, 0xFFC20E,
  // Row 2
  0x990030, 0x990030, 0xED1C24, 0x000000, 0x000000, 0xED1C24, 0xFFC20E, 0xFFC20E,
  // Row 3
  0x990030, 0x990030, 0xED1C24, 0xED1C24, 0xED1C24, 0xED1C24, 0xFFC20E, 0xFFC20E,
  // Row 4
  0x4D6DF3, 0x990030, 0xED1C24, 0xED1C24, 0xED1C24, 0xED1C24, 0xFFC20E, 0x22B14C,
  // Row 5
  0x4D6DF3, 0x4D6DF3, 0xED1C24, 0xED1C24, 0xED1C24, 0xED1C24, 0x22B14C, 0x22B14C,
  // Row 6
  0x4D6DF3, 0x4D6DF3, 0x000000, 0xED1C24, 0xED1C24, 0x000000, 0x22B14C, 0x22B14C,
  // Row 7
  0x4D6DF3, 0x4D6DF3, 0x000000, 0x000000, 0x000000, 0x000000, 0x22B14C, 0x22B14C,
  // Row 8
  0x4D6DF3, 0x4D6DF3, 0x000000, 0x000000, 0x000000, 0x000000, 0x22B14C, 0x22B14C
};

// ------ IMAP objects ------
IMAPSession imap;         // the IMAP session
Session_Config config;    // login/connection parameters
IMAP_Data imap_data;      // internal IMAP data settings

// ------ Function Prototypes ------
void connectWiFi();
void showGmailIcon();
void clearMatrix();
void imapCallback(IMAP_Status status);

// ---------------------------------

void setup()
{
  Serial.begin(115200);
  delay(1000);

  connectWiFi();

  // NeoPixel init
  strip.begin();
  strip.show(); // turn off all LEDs

  // Enable debug output (0 = none, 1 = basic)
  imap.debug(1);

  // Set a callback so we can see status or do something after fetch
  imap.callback(imapCallback);

  // Configure mail session
  config.server.host_name   = IMAP_HOST;
  config.server.port        = IMAP_PORT;
  config.login.email        = GMAIL_ADDRESS;
  config.login.password     = GMAIL_PASSWORD;
  // If SSL/TLS verification fails, optionally disable it:
  // config.server.cert_verify = false;

  // Connect to Gmail IMAP
  if (!imap.connect(&config, &imap_data))
  {
    Serial.printf("Failed to connect: %s\n", imap.errorReason().c_str());
    return;
  }

  // If credentials are good, we should be authenticated
  if (imap.isAuthenticated())
    Serial.println("IMAP login successful.");
  else
    Serial.println("IMAP connected, but not authenticated.");

  // Select the "INBOX" so we can listen for new emails
  if (!imap.selectFolder("INBOX"))
  {
    Serial.println("Failed to select INBOX.");
    return;
  }

  // Now we are set to listen for changes in loop().
}

void loop()
{
  // Listen for mailbox changes (IDLE/NOOP).
  // Returns true if successfully listening, false if there's an error.
  if (!imap.listen()) {
    // If there's a connection error, you might reconnect or handle it here.
    return;
  }

  // Has the folder status changed? (e.g. new mail arrived)
  if (imap.folderChanged())
  {
    // We can see what changed
    SelectedFolderInfo folderInfo = imap.selectedFolder();

    if (folderInfo.pollingStatus().type == imap_polling_status_type_new_message)
    {
      Serial.println("==> New Email Arrived!");

      // Stop listening while we handle the new message
      imap.stopListen();

      // Optionally, read or fetch the message here. For now, just show icon:
      showGmailIcon();

      // Wait 10 seconds. Modify this to change how long the gMail icon is displayed
      delay(10000);

      // Clear the matrix to make the icon go away
      clearMatrix();

      // Re-listen for new mail
      imap.listen();
    }
  }
}

// Connect to WiFi
void connectWiFi()
{
  Serial.printf("Connecting to WiFi: %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("\nWiFi connected. IP: %s\n", WiFi.localIP().toString().c_str());
}

// Light up the 8x8 matrix with the Gmail icon
void showGmailIcon()
{
  for (int i = 0; i < NUM_LEDS; i++)
    strip.setPixelColor(i, gmailIcon[i]);

  strip.show();
}

// Clear the matrix (all off)
void clearMatrix()
{
  for (int i = 0; i < NUM_LEDS; i++)
    strip.setPixelColor(i, 0x000000);

  strip.show();
}

// Minimal callback just to see final statuses, if needed
void imapCallback(IMAP_Status status)
{
  Serial.println(status.info());

  // If reading/fetching was successful, we can optionally do more here.
  // For example, read the fetched messages, etc.
}
