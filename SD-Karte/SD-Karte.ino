// Libraries for SD card
#include <SPI.h>
#include <SD.h>

// Digital pins for rows and columns
const int first_row = 30;
const int first_column = 31;

// Pin for CS
const int cs = 53;

// Amount of rows and columns
const int rows = 8;
const int columns = 8;

// How often each frame repeats
const int frameIterations = 39;

// File with video on SD card
File video;

// Current frame
char frame[rows][columns];

void setup() {
  Serial.begin(9600);
  
  // Iteration over rows and columns to setup matrix
  for (int pin = first_row; pin < rows + columns + first_row; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(cs)) {
    Serial.println("initialization failed while beginning!");
    return;
  }
  video = SD.open("video.txt");
  if (!video) {
    Serial.println("initialization failed while reading video.txt!");
    return;
  }
  Serial.println("initialization done.");
}

void loop() {
  // Iteration over data of video
  while (video.available()) {
    // Read out next frame
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < columns; c++) {
        frame[r][c] = video.read();
      }
      video.read();
    }
    // Repeat each frame to slow down video
    for (int i = 0; i < frameIterations; i++) {
      // Iteration over rows
      for (int r = 0; r < rows; r++) {
        int row = r * 2 + first_row;
        digitalWrite(row, HIGH);
        
        // Iteration over columns to activate
        for (int c = 0; c < columns; c++) {
          int column = c * 2 + first_column;
          if (frame[r][c] == 49) {
            digitalWrite(column, HIGH);
          } else {
            digitalWrite(column, LOW);
          }
        }
        
        // Iteration over columns to deactivate
        for (int c = 0; c < columns; c++) {
          int column = c * 2 + first_column;
          digitalWrite(column, LOW);
        }
        
        digitalWrite(row, LOW);
      }
    }
  }
  video.seek(0);
}
