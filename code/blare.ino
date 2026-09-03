#include <Adafruit_GFX.h> // graphics library
#include <Adafruit_ST7789.h> // driver for the ST7789 screen
#include <SPI.h> 
#include <WiFi.h>
#include <WiFiServer.h>

#include <notes.h>
#include <ntp.ino> // Include the NTP time function from ntp.ino
#include <formatting.ino>
// Defining pins for the display, change according to your setup!!! Uses the white numbers on the ESP
#define TFT_SCLK 0 // labeled SCL on the screen
#define TFT_MOSI 1 // labeled SDA on the screen
#define TFT_RST 2
#define TFT_DC 3
#define TFT_CS 4
#define TFT_BL 5

#define BUZZER_PIN 8;


const int midi1[480][3] = {
 {G3, 364, 91},
 {A3, 91, 91},
 {B3, 91, 91},
 {B3, 182, 0},
 {A3, 182, 0},
 {G3, 182, 0},
 {E3, 182, 182},
 {E3, 182, 182},
 {A3, 364, 182},
 {G3, 182, 0},
 {Fb3, 121, 242},
 {Fb3, 273, 0},
 {E3, 182, 273},
 {E3, 121, 0},
 {G3, 182, 273},
 {D3, 121, 242},
 {G3, 455, 273},
 {G3, 455, 91},
 {A3, 182, 0},
 {B3, 91, 91},
 {B3, 182, 0},
 {E3, 182, 91},
 {E3, 182, 182},
 {A3, 455, 91},
 {G3, 182, 0},
 {Fb3, 121, 242},
 {Fb3, 273, 91},
 {E3, 121, 152},
 {Fb3, 182, 61},
 {G3, 182, 91},
 {D3, 121, 242},
 {G3, 455, 91},
 {D3, 182, 0},
 {G3, 121, 242},
 {G3, 91, 182},
 {B3, 485, 122},
 {G3, 121, 0},
 {E3, 121, 242},
 {E3, 121, 242},
 {A3, 364, 182},
 {G3, 182, 0},
 {Fb3, 91, 273},
 {Fb3, 121, 0},
 {E3, 364, 0},
 {Fb3, 91, 273},
 {Fb3, 91, 0},
 {G3, 818, 273},
 {D3, 182, 91},
 {G3, 121, 242},
 {G3, 121, 242},
 {B3, 273, 91},
 {G3, 121, 242},
 {E3, 91, 91},
 {A3, 545, 182},
 {G3, 91, 91},
 {G3, 91, 273},
 {Fb3, 364, 91},
 {D3, 91, 273},
 {B3, 91, 273},
 {A3, 91, 273},
 {G3, 636, 636},
 {D3, 91, 91},
 {G3, 121, 242},
 {G3, 91, 273},
 {B3, 545, 0},
 {G3, 182, 0},
 {E3, 121, 242},
 {E3, 121, 242},
 {A3, 545, 0},
 {G3, 182, 0},
 {Fb3, 91, 273},
 {Fb3, 91, 91},
 {Fb3, 91, 91},
 {E3, 121, 242},
 {Fb3, 91, 273},
 {G3, 818, 394},
 {D3, 91, 152},
 {G3, 121, 242},
 {G3, 91, 273},
 {B3, 182, 91},
 {G3, 182, 182},
 {E3, 121, 242},
 {A3, 455, 91},
 {G3, 91, 91},
 {G3, 91, 273},
 {Fb3, 364, 91},
 {E4, 242, 121},
 {B3, 273, 91},
 {A3, 121, 242},
 {G3, 727, 727},
 {G3, 364, 30},
 {A3, 91, 0},
 {B3, 91, 0},
 {B3, 91, 30},
 {E3, 182, 91},
 {E3, 182, 182},
 {A3, 364, 182},
 {G3, 182, 0},
 {Fb3, 121, 152},
 {Fb3, 273, 0},
 {E3, 121, 242},
 {E3, 121, 0},
 {G3, 121, 242},
 {D3, 121, 242},
 {G3, 455, 91},
 {D3, 91, 91},
 {G3, 121, 152},
 {G3, 121, 333},
 {B3, 364, 121},
 {E3, 121, 242},
 {E3, 121, 242},
 {A3, 364, 273},
 {Fb3, 121, 242},
 {Fb3, 91, 273},
 {E3, 121, 242},
 {Fb3, 91, 364},
 {G3, 818, 182},
 {G3, 91, 273},
 {G3, 91, 273},
 {B3, 91, 91},
 {G3, 242, 303},
 {E3, 91, 91},
 {A3, 606, 303},
 {G3, 91, 182},
 {Fb3, 364, 0},
 {D3, 91, 273},
 {B3, 91, 273},
 {A3, 91, 273},
 {G3, 848, 333},
 {D3, 121, 242},
 {G3, 91, 273},
 {G3, 91, 273},
 {B3, 455, 91},
 {G3, 182, 0},
 {E3, 121, 242},
 {E3, 91, 273},
 {A3, 455, 91},
 {G3, 182, 0},
 {Fb3, 91, 273},
 {Fb3, 121, 242},
 {E3, 121, 242},
 {Fb3, 91, 273},
 {G3, 727, 364},
 {D3, 273, 91},
 {G3, 121, 152},
 {G3, 91, 364},
 {B3, 182, 0},
 {G3, 455, 91},
 {E3, 121, 242},
 {A3, 606, 121},
 {G3, 121, 242},
 {Fb3, 242, 121},
 {Fb3, 182, 182},
 {A3, 121, 242},
 {Fb3, 121, 242},
 {G3, 727, 727},
 {G3, 364, 30},
 {A3, 91, 0},
 {B3, 91, 0},
 {B3, 91, 30},
 {E3, 182, 91},
 {E3, 182, 182},
 {A3, 364, 182},
 {G3, 182, 0},
 {Fb3, 121, 152},
 {Fb3, 273, 0},
 {E3, 121, 242},
 {E3, 121, 0},
 {G3, 121, 242},
 {D3, 121, 242},
 {G3, 455, 91},
 {D3, 91, 91},
 {G3, 121, 242},
 {G3, 121, 242},
 {B3, 545, 0},
 {G3, 182, 0},
 {E3, 121, 242},
 {E3, 121, 242},
 {A3, 364, 182},
 {G3, 182, 0},
 {Fb3, 182, 182},
 {D3, 121, 242},
 {B3, 364, 182},
 {A3, 182, 0},
 {G3, 848, 122},
 {D4, 455, 30},
 {G3, 182, 182},
 {G3, 121, 242},
 {G3, 182, 182},
 {E3, 182, 182},
 {A3, 455, 273},
 {G3, 182, 182},
 {Fb3, 273, 0},
 {D3, 182, 273},
 {B3, 364, 182},
 {A3, 182, 0},
 {G3, 727, 545},
 {D3, 91, 91},
 {G3, 182, 91},
 {G3, 182, 182},
 {B3, 364, 182},
 {G3, 182, 0},
 {E3, 182, 91},
 {E3, 182, 273},
 {A3, 364, 182},
 {G3, 182, 0},
 {Fb3, 273, 2091},
 {G3, 121, 333},
 {Db3, 91, 91},
 {Db3, 91, 91},
 {F3, 91, 0},
 {A3, 121, 31},
 {Cb3, 121, 0},
 {G3, 364, 273},
 {Cb3, 242, 0},
 {G3, 636, 333},
 {A3, 545, 3333},
 {G3, 364, 30},
 {A3, 91, 0},
 {B3, 91, 0},
 {B3, 91, 30},
 {E3, 182, 91},
 {E3, 182, 182},
 {A3, 364, 182},
 {G3, 182, 0},
 {Fb3, 121, 152},
 {Fb3, 273, 0},
 {E3, 121, 242},
 {E3, 121, 0},
 {G3, 121, 242},
 {D3, 121, 242},
 {G3, 455, 273},
 {G3, 364, 30},
 {A3, 91, 0},
 {B3, 91, 0},
 {B3, 91, 30},
 {E3, 182, 91},
 {E3, 182, 182},
 {A3, 5545, 818},
 {Fb3, 121, 242},
 {Fb3, 182, 182},
 {E3, 121, 242},
 {E3, 182, 0},
 {Fb3, 182, 0},
 {G3, 121, 242},
 {D3, 121, 242},
 {G3, 182, 0},
};

// Fix setColRowStart() by exposing it via a subclass
class MyST7789 : public Adafruit_ST7789 {
public:
  MyST7789(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk, int8_t rst)
    : Adafruit_ST7789(cs, dc, mosi, sclk, rst) {}
  void setOffsets(uint8_t col, uint8_t row) {
    _colstart = _colstart2 = col;
    _rowstart = _rowstart2 = row;
  }
};

MyST7789 tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


unsigned long epochTime = 0; // Variable to store the epoch time

unsigned long currentMillis = 0; // Variable to store the current time in milliseconds

unsigned long lastUpdatedMillis = 0; // Variable to store the last update time in milliseconds
unsigned long lastUpdateTime = 0; // Variable to store the last update time


int alarmHour = 7; // Set the alarm hour (24-hour format)
int alarmMinute = 30; // Set the alarm minute

boolean alarmTriggered = false; // Flag to indicate if the alarm has been triggered


void setup() {
  Serial.begin(115200); // lets the board talk to your computer

  pinMode(TFT_BL, OUTPUT); // Set the backlight pin mode, or just wire it to 3.3V
  digitalWrite(TFT_BL, LOW); // Turns the backlight ON, for some reason this screen is active Low, so setting it to LOW is really HIGH

  tft.init(76, 284); // Our panel size (portrait)
  tft.setOffsets(82, 18); // Offsets for the weird resolution
  tft.invertDisplay(false); // Invert the colors (This display is flipped from normal)
  tft.setRotation(1); // Landscape, if it's upside down use 3!

  tft.fillScreen(ST77XX_BLACK); // clear the screen

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(6);
  tft.setCursor(0,0); // Where the text is drawn, 0,0 is top left
  tft.print("00:00:00"); // Show whatever you want! Draws from the top left of the text/number/shape 


  WiFi.begin("SSID", "PASSWORD"); // Connect to WiFi, change to your network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  epochTime = getNtpTime(); // Get the current epoch time from the NTP server
  lastUpdateTime = epochTime; // Initialize the last update time
  lastUpdatedMillis = millis(); // Initialize the last update time in milliseconds
  currentMillis = millis(); // Initialize the current time in milliseconds

  WiFiServer server(80); // Start a web server on port 80
  server.begin(); // Begin listening for connections

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body>";
    html += "<h1>ESP32 Alarm Clock</h1>";
    html += "<p>Current Time: " + String(epochTime) + "</p>";
    html += "<button onclick=\"location.href='/updateTime'\">Update Time</button><br>";
    html += "<form action=\"/setAlarm\" method=\"POST\">";
    html += "<label for=\"hour\">Hour (0-23):</label>";
    html += "<input type=\"number\" id=\"hour\" name=\"hour\" min=\"0\" max=\"23\" required><br>";
    html += "<label for=\"minute\">Minute (0-59):</label>";
    html += "<input type=\"number\" id=\"minute\" name=\"minute\" min=\"0\" max=\"59\" required><br>";
    html += "<input type=\"submit\" value=\"Set Alarm\">";
    html += "</form>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/setAlarm", HTTP_POST, [](AsyncWebServerRequest *request){
    if (request->hasParam("hour", true) && request->hasParam("minute", true)) {
      alarmHour = request->getParam("hour", true)->value().toInt();
      alarmMinute = request->getParam("minute", true)->value().toInt();
      String response = "Alarm set for " + String(alarmHour) + ":" + String(alarmMinute);
      request->send(200, "text/plain", response);
    } else {
      request->send(400, "text/plain", "Invalid parameters");
    }
  });
  server.on("/updateTime", HTTP_GET, [](AsyncWebServerRequest *request){
    epochTime = getNtpTime(); // Update the epoch time from the NTP server
    lastUpdateTime = epochTime; // Update the last update time
    lastUpdatedMillis = millis(); // Update the last update time in milliseconds
    currentMillis = millis(); // Update the current time in milliseconds
    request->sendHeader("Location", "/"); // Redirect back to the main page
    request->send(302, "text/plain", "Time updated");
  });

  server.on("/newTone", HTTP_POST, [](AsyncWebServerRequest *request){
    if (request->hasParam("tones", true) && request->hasParam("durations", true) && request->hasParam("wait", true)) {
      //I don't know if this is properly cast, but we'll see
      tones = request->getParam("tones", true)->value().toIntArray();
      durarions = request->getParam("durations", true)->value().toIntArray();
      wait = request->getParam("wait", true)->value().toIntArray();

      notes = new int[ARRAY_LEN(tones)][3]; // Allocate memory for the notes array

      for (int i = 0; i < ARRAY_LEN(tones); i++) {
        notes[i][0] = tones[i];
        notes[i][1] = durations[i];
        notes[i][2] = wait[i];
      }

      midi = notes; // Assign the new notes array to the midi variable

      String response = "Tone set to " + String(tones);
      Serial.println(response);
      request->send(200, "text/plain", response);
    } else {
      request->send(400, "text/plain", "Invalid parameters");
    }
  });
}





void loop() {

    if (epochTime - lastUpdateTime > 1800) { //update time every half hour
        epochTime = getNtpTime();
        lastUpdateTime = epochTime; // Update the last update time
        currentMillis = millis(); // Reset the current time in milliseconds
        lastUpdatedMillis = currentMillis; // Update the last update time in milliseconds
    }

    // Calculate the current epoch time based on the last update and elapsed time
    currentMillis = millis();
    unsigned long elapsedMillis = currentMillis - lastUpdatedMillis;

    unsigned long currentEpoch = lastUpdateTime + (elapsedMillis / 1000); // Calculate the current epoch time

    

    // Display the time on the TFT screen
    tft.fillScreen(ST77XX_BLACK); // Clear the screen
    tft.setCursor(0, 0);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(6);
    tft.printf("%s", getFormattedTime(currentEpoch).c_str()); // Print time in HH:MM:SS format
    tft.setTextSize(2);
    tft.setCursor(0, 60);
    tft.printf("%s %s", getDayOfWeek(currentEpoch).c_str(), getFormattedDate(currentEpoch).c_str()); // Print date in MM/DD/YYYY format

    if (hours == alarmHour && minutes == alarmMinute && !alarmTriggered) {
        alarmTriggered = true; // Set the flag to indicate the alarm has been triggered
        playMidi(BUZZER_PIN, notes, ARRAY_LEN(notes));
        alarmTriggered = false; // Reset the flag after the alarm has been triggered
    }

    server.handleClient(); // Handle incoming client requests
    delay(0); 
}