#include <Arduino.h>
//#include <SPI.h>
//#include <Adafruit_GPS.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
  #include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"
//#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

//#include <Adafruit_GPS.h>
#include <Wire.h>
#include <SoftwareSerial.h>
//#include "BLUETOOTH_W_RANGEFINDERGPS"

#define EZ1pin 7               // Trinket GPIO #1   

 #define FACTORYRESET_ENABLE         1
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
    #define MODE_LED_BEHAVIOUR          "MODE"
/*=========================================================================*/

// Create the bluefruit object, either software serial...uncomment these lines

SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                      BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);


 
// Connect display via  i2c, default address #0 (A0-A2 not jumpered)
//Adafruit_LiquidCrystal lcd(0);
 
// These values are for calculating a mathematical median for a number of samples as
// suggested by Maxbotix instead of a mathematical average
int8_t arraysize = 9; // quantity of values to find the median (sample size). Needs to be an odd number

//declare an array to store the samples. not necessary to zero the array values here, it just makes the code clearer
uint16_t rangevalue[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};

//uint16_t copyvalue[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint16_t modE;        // calculated median distance


int rangefinder_flag = 0;

// If using software serial, keep this line enaSeriald
// (you can change the pin numbers to match your wiring):
//SoftwareSerial mySerial(3, 2);

// If using hardware serial (e.g. Arduino Mega), comment out the
// above SoftwareSerial line, and enaSerial this line instead
// (you can change the Serial number to match your wiring):

//HardwareSerial mySerial = Serial1;


//Adafruit_GPS GPS(&mySerial);


// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences. 
//#define GPSECHO  false

// this keeps track of whether we're using the interrupt
// off by default!
//boolean usingInterrupt = false;
//void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

/**************************************************************************/
/*!
    @brief  Sets up the HW an the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
void blue_setup(void)
{
  while (!Serial);  // required for Flora & Micro
  delay(500);

  //Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit Command Mode Example"));
  Serial.println(F("---------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  /*if ( FACTORYRESET_ENABLE )
  {
     //Perform a factory reset to make sure everything is in a known state 
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }*/

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  /*Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  //ble.info();
/*
  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in UART mode"));
  Serial.println(F("Then Enter characters to send to Bluefruit"));
  Serial.println();*/

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while (! ble.isConnected()) {
    Serial.println(F("******************************"));
      delay(500);
  }
  delay(2000);

  // LED Activity command is only supported from 0.6.6
  /*if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("******************************"));
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
    Serial.println(F("******************************"));
  }*/
}


bool blue_send(String range)
{
  // Check for user input
  char inputs[BUFSIZE+1];

  // Check for incoming characters from Bluefruit
  //ble.println("AT+BLEUARTRX");
    //ble.print("AT+BLEUARTTX=");
    /*Serial.println(range);
    Serial.println(GPS.latitude,4);
    Serial.println(GPS.longitude,4);*/
    bluefruitSS.listen();

    //if (Serial.available()){
    //ble.listen();
    uint32_t timer2 = millis();
    while (millis()- timer2 < 100){
    //while (ble.available()) {
      Serial.print("WE DID THE INTERRUPT");
    ble.print("AT+BLEUARTTX=");
    ble.print("LMerge:");ble.println(range);// ble.print("/n");
    delay(50);
    ble.print("AT+BLEUARTTX=");ble.println("\\n");
      if (! ble.waitForOK() ) {
      Serial.println(F("Failed to send?"));
    }
   // }
    //Serial.print(ble.available());
    }
    /*else{
      Serial.print("1.7676767");
    }*/
    //Serial.println(bluefruitSS.available());
    //mySerial.listen();
     return true;
}

/*bool blue_read(int range , Adafruit_GPS GPS)
{
  // Check for user input
  char inputs[BUFSIZE+1];


  // Check for incoming characters from Bluefruit
  //ble.println("AT+BLEUARTRX");
  ble.readline();
  // Some data was found, its in the buffer
  //Serial.print(F("[Recv] ")); 
  if (strcmp(ble.buffer, "GO") == 1) {
  //Serial.println(ble.buffer);
  //ble.waitForOK();
    return true
  
}*/

/**************************************************************************/
/*!
    @brief  Checks for user input (via the Serial Monitor)
*/
/**************************************************************************/


void setup() {
  modE = 2;
  pinMode(EZ1pin, INPUT); // Set ultrasonic sensor pin as input
  delay(500);
 // lcd.begin(16, 2);       // set up the LCD number of rows and columns: 
  //lcd.setBacklight(HIGH); // Set backlight on (HIGH on, LOW off)

  noInterrupts();           // disaSerial all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 6250;            // compare match register 16MHz/256/10Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enaSerial timer compare interrupt
  interrupts();             // enaSerial all interrupts

  Serial.begin(115200);
  Serial.println("Adafruit Generic Range and GPS library basic test!");


  blue_setup();
  interrupts();
  delay(1000);

}

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it


uint32_t timer = millis();

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
 // Serial.begin(9600); //Baud rate for raspberry is 115200 was 9600

//modE is the average of rangefinder values
//sometimes we'll get a previous cycles modE, but honestly cars cant move so fast that a megaertz difference will
//throw off precision of a megaHertz precision, Cars dont cover distance so fast. 
  if(rangefinder_flag != 1){
    rangefinder_flag = 1;
}

 
}



 
void loop() {

  while (! ble.isConnected()) {
    Serial.println(F("******************************"));
      delay(50);
  }
  int16_t pulse;  // number of pulses from sensor
  int i=0;
 
  while( i < arraysize ){                    
    pulse = pulseIn(EZ1pin, HIGH);  // read in time for pin to transition
    rangevalue[i]=pulse/58;         // pulses to centimeters (use 147 for inches)
    if( rangevalue[i] < 645 && rangevalue[i] >= 15 ) i++;  // ensure no values out of range
    delay(10);                      // wait between samples
    i++;
    
  }
  i = 0;
  isort(rangevalue,arraysize);        // sort samples
  modE = mode(rangevalue,arraysize);  // get median
  //Serial.println("in loop");
  if(rangefinder_flag == 1){
    Serial.print("RANGEFINDER ");

     if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
    //Check if the value is less than 5.5meters
    if (modE < 200){
      //Serial.println("BAD");
      
        blue_send("BAD");
      Serial.println("SENT BLE DATA");
    }
    else{
      blue_send("GOOD");
      
    }
    
    Serial.println(modE);
    rangefinder_flag = 0;
    }
    else{
  
      Serial.println("NOFIX");
      //no_fix_flag = 1;
      delay(20);
    }

  i = 0;
  /*while(i < arraysize){
    copyvalue[i] = rangevalue[i];
  }*/
  //rangefinder_flag = 0;
  delay(100);
}
 
// Sorting function (Author: Bill Gentles, Nov. 12, 2010)
void isort(uint16_t *a, int8_t n){
  for (int i = 1; i < n; ++i)  {
    uint16_t j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--) {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}


// Mode function, returning the mode or median.
uint16_t mode(uint16_t *x,int n){
  int i = 0;
  int count = 0;
  int maxCount = 0;
  uint16_t mode = 0;
  int bimodal;
  int prevCount = 0;
  while(i<(n-1)){
    prevCount=count;
    count=0;
    while( x[i]==x[i+1] ) {
      count++;
      i++;
    }
    if( count > prevCount & count > maxCount) {
      mode=x[i];
      maxCount=count;
      bimodal=0;
    }
    if( count == 0 ) {
      i++;
    }
    if( count == maxCount ) {      //If the dataset has 2 or more modes.
      bimodal=1;
    }
    if( mode==0 || bimodal==1 ) {  // Return the median if there is no mode.
      mode=x[(n/2)];
    }
    return mode;
  }
}
