// Digital pins for rows and columns
const int first_row = 30;
const int first_column = 31;

// Amount of rows and columns
const int rows = 8;
const int columns = 8;

// Current frame (mirror-inverted)
const char image[rows] = {B10001001,
                          B11001111,
                          B11101001,
                          B11111000,
                          B11111000,
                          B11101001,
                          B11001111,
                          B10001001};

void setup() {
  Serial.begin(9600);
  
  // Iteration over rows and columns to setup matrix
  for (int pin = first_row; pin < rows + columns + first_row; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
}

void loop() {
  // Iteration over rows
  for (int r = 0; r < rows; r++) {
    int row = r * 2 + first_row;
    digitalWrite(row, HIGH);
    
    // Iteration over columns to activate
    for (int c = 0; c < columns; c++) {
      int column = c * 2 + first_column;
      if ((image[r]>>c) & B00000001) {
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
