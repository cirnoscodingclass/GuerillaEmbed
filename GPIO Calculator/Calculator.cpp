#include <mbed.h>   
#include <string>  
#include <iostream> 
#include <sstream>  
#include <TextLCD.h> // Includes functions to interact with LCD

//Initalize GPIO
TextLCD LCD(PA_0, PA_1, PA_4, PB_0, PC_1, PC_0);

//Initalize the GPIO (Keypad)
DigitalOut ROW1 (PA_6);
DigitalOut ROW2 (PA_7);
DigitalOut ROW3 (PB_6);
DigitalOut ROW4 (PC_7);

//Digital inputs for the keypad, read as 1 due to Pull-up
DigitalIn COL1 (PA_9, PullUp);
DigitalIn COL2 (PA_8, PullUp);
DigitalIn COL3 (PB_10, PullUp);
DigitalIn COL4 (PB_4, PullUp);

//Array map for  4x4 keypad
unsigned char key_map [4][4] = {    
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'},
        };

int col_checker (void) {
    if (COL1 == 0) { // 0 is button press
        return 0;  // returns the column chosen from 0-3
    } else if (COL2 == 0) {
        return 1;
    } else if (COL3 == 0) {
        return 2;
    } else if (COL4 == 0) {
        return 3;
    } else {
        return 0xFF; // return nothing
    }
}

// Checks if ROW1-4 is pressed 
unsigned char key_checker(void) {
       int row = 0;
       int col = 0;  
       for ( row = 0; row <= 4; row++) {
         ROW1 = 1;
         ROW2 = 1;
         ROW3 = 1;
         ROW4 = 1;  
        if(row == 0) {
            ROW1 = 0; 
            col = col_checker();  //checks corressponding column 
            if(col < 4)  
                return key_map[row][col]; // Returns row 0 with varying columns
        } else if(row == 1) {
            ROW2 = 0;
            col = col_checker();
            if (col < 4)
                return key_map[row][col];
        } else if (row == 2) {
            ROW3 = 0;
            col = col_checker();
            if (col <4)
                return key_map[row][col];
        } else if (row == 3) {
            ROW4 = 0;
            col = col_checker();
            if(col <4)
                return key_map[row][col];
        }
    }
    return 0xFF;      
}

//Calling external ARM ASM programs for operations
extern "C" int add(int a, int b);   //Addition
extern "C" int subtract(int a, int b);   //Subtraction
extern "C" int multiply(int a, int b);   //Multiplication
extern "C" int divide(int a, int b);  //Division

//User input for matmatical operation
int operation (int a, int b) {
    int result = 0;
    unsigned char key;  //Keypad character holder
    string choice;  //characters stored inside string
    LCD.cls();
    LCD.printf("SELECT OPERATION"); 
    while (result == 0 ){
        key = key_checker();
        if( key != 0xFF) {
            wait (0.2);
        key = key_checker();
            if (key != 0xFF)
            choice += key;
            if (key == '#'){ // # starts loop
                if (choice == "A#") {
                    result = add(a,b);  
                } else if (choice == "B#") {
                    result = subtract(a,b);  
                } else if (choice == "C#") {
                    result = multiply(a,b);  
                } else if (choice == "D#") {
                    result = divide(a,b); 
                } else
                    LCD.printf("ERROR"); // invalid input entered
                    wait(0.2);
                    LCD.cls();
                    choice.erase(); // Erases values and resets loop
            }
        }
    }
    return result;
}

//  Converts string to integer
int convert (string b){
    int newNum=0;
    stringstream buffer; 
    buffer << b;      // String input
    buffer >> newNum; // Integer output
    return newNum;    // Returns as an integer
}

// User input value,
int InputVal (int a) {
      string pass;
      unsigned char key;
      int input = 0;
      while (input == 0) {  // Runs until input is entered
      key = key_checker(); 
        if (key != '#'){
            if (key != 0xFF) {  // If key_checker returns a value other than 0xFF
            wait(0.2);
            key = key_checker();
            if(key != 0xFF) {
                pass += key;
            }
        }
    } else if (key == '#') {
                    LCD.cls();
                    input = convert(pass);  // Turns string to integer
                    pass.erase();   // Clears value and resets
    }
}

    return input; // Returns inputs
}


int main(){
    int Input1 = 0;  //First input
    int Input2 = 0; //Second input
    int result = 0;

    while (true) {
        LCD.printf("Num1:");
        if (Input1 == 0) { //first numer entered
            Input1 = InputVal (1); //Returns first number input
            LCD.printf("%04i \n", Input1);
            wait(2);
            LCD.printf("Num2:");
        } else if (Input2 >0 && Input1 > 0){ // both numbers are stored
            result = operation(Input1, Input2); //User selects an opeation 
            LCD.printf("Answer: %06i", result);
            wait (3);
            LCD.cls();
            Input1 = 0;  
            Input2 = 0; 
        } else if (Input1 > 0) { 
            Input2 = InputVal (2); //Returns second  input
            LCD.printf("%04i \n", Input2);
            wait(2);
        }
    }
}







