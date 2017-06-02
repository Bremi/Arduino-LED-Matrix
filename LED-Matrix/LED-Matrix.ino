// Libraries for SD card
#include <SPI.h>
#include <SD.h>

// Digital pins for rows and columns
const int first_row = 30;
const int first_column = 31;

// Amount of rows and columns
const int rows = 8;
const int columns = 8;

// File with video on SD card
File video;

void setup() {
  Serial.begin(9600); // DEBUG
  // Iteration over rows and columns to setup matrix
  for (int pin = first_row; pin < rows + columns + first_row; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  // Setup SD card
  SD.begin(53);
  video = SD.open("video.txt");
}

void loop() {
  // Iteration over data of video
  while (video.available());
    // Iteration over rows
    for (int r = 0; r < rows; r++) {
      int row = r * 2 + first_row;
      digitalWrite(row, HIGH);
  
      // Iteration over columns
      for (int c = 0; c < columns; c++) {
        int column = c * 2 + first_column;
        if (strcmp(video.read(), "1")) {
          digitalWrite(column, HIGH);
          Serial.print("1");
        } else {
          digitalWrite(column, LOW);
          Serial.print("0");
        }
      }
  
      // Iteration over columns
      for (int c = 0; c < columns; c++) {
        int column = c * 2 + first_column;
        digitalWrite(column, LOW);
      }
  
      digitalWrite(row, LOW);
      Serial.println();
    }
  }
  video.seek(0);
}
