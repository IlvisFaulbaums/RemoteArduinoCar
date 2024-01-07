#include <Servo.h>
#include <IRremote.h>
double buttonState = 0;
double lastButtonState = 0;   // previous state of the button
const int signalDelay = 400;
const int IR_PIN = 11;  // Pin to which the IR receiver is connected
String command = "";
IRrecv irrecv(IR_PIN);
decode_results results;

Servo servo1;  // create servo object to control a servo on pin 9
Servo servo2;  // create servo object to control a servo on pin 10

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();  // Start the infrared receiver
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10); // attaches the servo on pin 10 to the servo object
}

void loop() {
  if (irrecv.decode(&results)) {
    buttonState = results.value;
    Serial.println(buttonState);
    if (buttonState != lastButtonState) {
      if (buttonState == 88 || buttonState == 65624) {

        Serial.println("uz priekshu");
        command = 6;
        delay(signalDelay); // small delay to prevent reading errors
      } else if (buttonState == 89 || buttonState == 65625) {

        Serial.println("atpakalj");
        command = 4;
        delay(signalDelay); // small delay to prevent reading errors
      } else if (buttonState ==  90 || buttonState == 65626) {

        Serial.println("pa kreisi");
        command = 2;
        delay(signalDelay); // small delay to prevent reading errors
      } else if (buttonState == 91 || buttonState == 65627) {

        Serial.println("pa labi");
        command = 8;
        delay(signalDelay); // small delay to prevent reading errors
      } else {
        command = "0";
      }


      irrecv.resume(); // Receive the next value



      //    }
      // if (Serial.available() > 0) {
      // Read the incoming string from Serial
      //  String command = Serial.readStringUntil('\n');
      Serial.println(command);
      // Perform actions based on the received command
      interpretCommand(command);
      // }
    }
  }
}
////////////IET UZ IISTAA UNO
void interpretCommand(String receivedCommand) {
  // Perform actions based on the received command
  //
  if (receivedCommand == "4") {
    // Turn left
    servo1.attach(10);
    servo2.attach(9);
    uzPrieksu();
  } else if (receivedCommand == "6") {
    // Turn right
    servo2.attach(10);
    servo1.attach(9);
    atpakalj(); //iet!!!!!!!
  } else if (receivedCommand == "8") {
    // Go further


    servo1.attach(9);
    servo2.attach(10);
    paLabi();
  } else if (receivedCommand == "2") {
    // Go back

    servo2.attach(9);
    servo1.attach(10);
    paKreisi();
    //    paLabi();
  }
  else {
    servo1.detach();
    servo2.detach();
  }
}

void uzPrieksu() {
  // Implement the left turn logic for your specific servo setup
  // For example:
  servo1.write(0);  // Set servo1 to the leftmost position
  servo2.write(180);  // Set servo2 to the leftmost position
}

void atpakalj() {
  // Implement the right turn logic for your specific servo setup
  // For example:
  servo1.write(0);  // Set servo1 to the rightmost position
  servo2.write(180);  // Set servo2 to the rightmost position
}

void paLabi() {
  // Implement the go further logic for your specific servo setup
  // For example:
  servo1.write(180);  // Set servo1 to the center position
  servo2.write(180);  // Set servo2 to the center position
}

void paKreisi() {
  // Implement the go back logic for your specific servo setup
  // For example:
  servo1.write(0);  // Set servo1 to the center position
  servo2.write(0);  // Set servo2 to the center position
  //  delay(500);        // Introduce a delay to simulate going back
}
