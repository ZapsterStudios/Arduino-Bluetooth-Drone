//----------------------------------------------\\
//  Teknifags Projekt: Eksamensprojekt - Drone  \\
//   Periode: Uge 9 (28 Feb) - Uge 17 (25 Apr)  \\
//        Andreas, Jesper og Marcus - 3C        \\
//----------------------------------------------\\

// Dependencies
#include "Servo.h";

/*
 * Class: MotorController
 * ----------------------------
 * Control single drone motor.
 *
 * @returns: class
 */
class MotorController {

    // Public
    public:

        int pos, pin;
        
        float speed = SPEED_HOVER,
        baseSpeed = SPEED_HOVER,
        nextSpeed = SPEED_HOVER;

        Servo * motor;

        MotorController(int position, int pinNum);
        void setup();
        void handle();

};

/*
 * Function: MotorController
 * ----------------------------
 * Initialize the MotorController class.
 *
 * @returns: void
 */
MotorController::MotorController(int position, int pinNum) {
    // Variables
    pos = position;
    pin = pinNum;
}

/*
 * Function: setup
 * ----------------------------
 * Setup motor controller class.
 *
 * @returns: void
 */
void MotorController::setup() {
    // Setup pin mode
    motor = new Servo();
    motor->attach(pin);
    motor->writeMicroseconds(SPEED_MINIMAL);

    pinMode(8, INPUT);
    pinMode(12, OUTPUT);
}

/*
 * Function: handle
 * ----------------------------
 * Handle the motor speed and rotation.
 *
 * @returns: void
 */
void MotorController::handle() {
    // Manage speed
    digitalWrite(12, HIGH);
    speed = constrain(nextSpeed+map(analogRead(0), 0, 1023, 0, 250), SPEED_RANGE_MIN, SPEED_RANGE_MAX);

    // Out speed
    if(DEBUG_CONTROLLER) {
        Serial.print(pos);
        Serial.print(" # ");
        Serial.print(speed);
        Serial.print("   ");

        if(pos == 3) {
            Serial.println("");
        }
    }

    // Write speed
    //if(pos == 0 || pos == 2) {
        motor->writeMicroseconds(speed);
    //} else {
    //    motor->writeMicroseconds(SPEED_MINIMAL);
    //}
}