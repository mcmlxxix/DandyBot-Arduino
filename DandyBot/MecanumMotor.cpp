// 
// 
// 

#include "MecanumMotor.h"

MecanumMotor::MecanumMotor(int pwmPin, int forwardPin, int backwardPin) {
	PWMPin = pwmPin;
	ForwardPin = forwardPin;
	BackwardPin = backwardPin;
    pinMode(pwmPin, OUTPUT);      // sets the digital pin as output
    pinMode(forwardPin, OUTPUT);      // sets the digital pin as output
    pinMode(backwardPin, OUTPUT);      // sets the digital pin as output
    pinMode(StandbyPin, OUTPUT);
}

void MecanumMotor::MoveForward(int speed) {
    if (movingForward)
        return;
    //Logger::Log("moving tank forward");
    digitalWrite(PWMPin, HIGH);
    digitalWrite(ForwardPin, HIGH);
    digitalWrite(BackwardPin, LOW);
    digitalWrite(StandbyPin, HIGH);
    movingForward = true;
}

void MecanumMotor::MoveBackward(int speed) {
    if (movingBackward)
        return;
    //Logger::Log("moving tank backward");
    digitalWrite(PWMPin, HIGH);
    digitalWrite(ForwardPin, LOW);
    digitalWrite(BackwardPin, HIGH);
    digitalWrite(StandbyPin, HIGH);
    movingBackward = true;
}

void MecanumMotor::MoveStop(bool forceStop) {
    if (!forceStop && !movingForward && !movingBackward)
        return;
    //Logger::Log("stopping tank");
    digitalWrite(PWMPin, LOW);
    digitalWrite(ForwardPin, LOW);
    digitalWrite(BackwardPin, LOW);
    digitalWrite(StandbyPin, LOW);

    movingForward = false;
    movingBackward = false;
}


