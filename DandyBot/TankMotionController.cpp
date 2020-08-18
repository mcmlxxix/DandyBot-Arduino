// Generic tank motion interface
// 
// 

#include "TankMotionController.h"
#include "AnalogMovement.h"
#include "DigitalMovement.h"
#include "controllerEnums.h"
#include "Logger.h"

bool TankMotionController::Init(int leftForwardPin, int leftBackwardPin, int rightForwardPin, int rightBackwardPin) {
    LeftForwardPin = leftForwardPin;
    LeftBackwardPin = leftBackwardPin;
    RightForwardPin = rightForwardPin;
    RightBackwardPin = rightBackwardPin;
    pinMode(LeftForwardPin, OUTPUT);      // sets the digital pin as output
    pinMode(LeftBackwardPin, OUTPUT);      // sets the digital pin as output
    pinMode(RightForwardPin, OUTPUT);      // sets the digital pin as output
    pinMode(RightBackwardPin, OUTPUT);      // sets the digital pin as output}
    return true;
}

void TankMotionController::MoveForward() {
    if (movingForward)
        return;
    //Logger::Log("moving tank forward");
    digitalWrite(LeftForwardPin, HIGH);
    digitalWrite(LeftBackwardPin, LOW);
    digitalWrite(RightForwardPin, HIGH);
    digitalWrite(RightBackwardPin, LOW);
    movingForward = true;
}

void TankMotionController::MoveBackward() {
    if (movingBackward)
        return;
    //Logger::Log("moving tank backward");
    digitalWrite(LeftForwardPin, LOW);
    digitalWrite(LeftBackwardPin, HIGH);
    digitalWrite(RightForwardPin, LOW);
    digitalWrite(RightBackwardPin, HIGH);
    movingBackward = true;
}

void TankMotionController::MoveStop(bool forceStop) {
    if (!forceStop && !turningLeft && !turningRight && !movingForward && !movingBackward)
        return;
    //Logger::Log("stopping tank");
    digitalWrite(LeftForwardPin, LOW);
    digitalWrite(LeftBackwardPin, LOW);
    digitalWrite(RightForwardPin, LOW);
    digitalWrite(RightBackwardPin, LOW);

    turningLeft = false;
    turningRight = false;
    movingForward = false;
    movingBackward = false;
}

void TankMotionController::TurnLeft() {
    if (turningLeft)
        return;
    //Logger::Log("turning tank Left");
    digitalWrite(LeftForwardPin, LOW);
    digitalWrite(LeftBackwardPin, HIGH);
    digitalWrite(RightForwardPin, HIGH);
    digitalWrite(RightBackwardPin, LOW);
    turningLeft = true;
}

void TankMotionController::TurnRight() {
    if (turningRight)
        return;
    //Logger::Log("turning tank Right");
    digitalWrite(LeftForwardPin, HIGH);
    digitalWrite(LeftBackwardPin, LOW);
    digitalWrite(RightForwardPin, LOW);
    digitalWrite(RightBackwardPin, HIGH);
    turningRight = true;
}

void TankMotionController::DigitalMove(DigitalMovement movement) {
    switch (movement.GetDirection()) {
    case -1:
        MoveStop(false);
        break;
    case UP:
        MoveForward();
        break;
    case DOWN:
        MoveBackward();
        break;
    case LEFT:
        TurnLeft();
        break;
    case RIGHT:
        TurnRight();
        break;
    }
}

void TankMotionController::AnalogMove(AnalogMovement movement) {
    double powerX = movement.GetAnalogX();
    double powerY = movement.GetAnalogY();
    if (powerY < 0) {
        analogWrite(LeftForwardPin, LOW);
        digitalWrite(LeftBackwardPin, -powerY);
        analogWrite(RightForwardPin, LOW);
        digitalWrite(RightBackwardPin, -powerY);
    }
    else if(powerY > 0) {
        analogWrite(LeftForwardPin, powerY);
        digitalWrite(LeftBackwardPin, LOW);
        analogWrite(RightForwardPin, powerY);
        digitalWrite(RightBackwardPin, LOW);
    }
    //if (powerX < 0) {
    //    analogWrite(LeftForwardPin, powerY);
    //    digitalWrite(LeftBackwardPin, LOW);
    //    analogWrite(RightForwardPin, powerY);
    //    digitalWrite(RightBackwardPin, LOW);
    //}
    //else if (powerX > 0) {
    //    analogWrite(LeftForwardPin, powerY);
    //    digitalWrite(LeftBackwardPin, LOW);
    //    analogWrite(RightForwardPin, powerY);
    //    digitalWrite(RightBackwardPin, LOW);
    //}
}

