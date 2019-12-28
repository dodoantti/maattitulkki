/* MaattiTulkki is a software made to run a 2 relay board with Arduino which is
 * connected to a computer running MaattiWare http://maattiware.sourceforge.net/
 * via parallel port.
 *
 * Original hardware implementation specified in MaattiWare is fine for running
 * low voltage vending machines, but in this usecase relays had to be connected
 * to 230V logic, so relay board with optical isolation was needed.
 *
 * Hardware used is Arduino Nano clone and cheap chinese 2 relay board.
 * Relay board wouldn't work with serial signal, so arduino is used to
 * run the relay board according to signals from MaattiWare.
 *
 * GNU GPLv3
 *
 * Code by Antti Kallunki, 2018 */


// Configuting input and output pins
// Pins 5-8 are physical D2-D5 on Arduino Nano board
#define MACHINE1_INPUT 5
#define MACHINE2_INPUT 6
#define MACHINE1_OUTPUT 7
#define MACHINE2_OUTPUT 8


void setup() {

    // Setting input & output pins ready
    pinMode(MACHINE1_INPUT, INPUT);
    pinMode(MACHINE2_INPUT, INPUT);
    pinMode(MACHINE1_OUTPUT, OUTPUT);
    pinMode(MACHINE2_OUTPUT, OUTPUT);
    digitalWrite(MACHINE1_OUTPUT, HIGH);
    digitalWrite(MACHINE2_OUTPUT, HIGH);

    // Serial communication for debugging
    Serial.begin(9600);

    // Sending boot message over serial
    Serial.println("MaattiTulkki is now running!");
    // Parallel port gives random signal during bootup, 
    // delay to wait for MaattiWare to boot up.
    // No delay == fuckton of free drinks during boot
    delay(22000);
}


void loop() {
  Serial.println(".");
    // statements to set output to low for 300 milliseconds if input goes high
    if(digitalRead(MACHINE1_INPUT) == HIGH) {
        Serial.println("Relay connected for machine 1!");
        digitalWrite(MACHINE1_OUTPUT, LOW);
        delay(100);
        digitalWrite(MACHINE1_OUTPUT, HIGH);
        delay(500);                             // Delay to reduce dual signals due errors
    } else {
        digitalWrite(MACHINE1_OUTPUT, HIGH);
    }

    if(digitalRead(MACHINE2_INPUT) == HIGH) {
        Serial.println("Relay connected for machine 2!");
        digitalWrite(MACHINE2_OUTPUT, LOW);
        delay(100);
        digitalWrite(MACHINE2_OUTPUT, HIGH);
        delay(500);                             // Delay to reduce dual signals due errors
    } else {
        digitalWrite(MACHINE2_OUTPUT, HIGH);
    }

    // yield to reset watchdog timer
    yield();
}
