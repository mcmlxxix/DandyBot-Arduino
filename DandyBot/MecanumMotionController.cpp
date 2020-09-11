// 
// 
// 

#include "MecanumMotor.h"
#include "MecanumMotionController.h"

// Generic tank motion interface
// 
// 

#include "AnalogMovement.h"
#include "DigitalMovement.h"
#include "controllerEnums.h"
#include "Logger.h"

bool MecanumMotionController::Init(MecanumMotor *leftFrontMotor, MecanumMotor *rightFrontMotor, MecanumMotor *leftRearMotor, MecanumMotor *rightRearMotor) {
    LeftFrontMotor = leftFrontMotor;
    RightFrontMotor = rightFrontMotor;
    LeftRearMotor = leftRearMotor;
    RightRearMotor = rightRearMotor;
    return true;
}

void MecanumMotionController::MoveForward() {
    if (movingForward)
        return;
    //Logger::Log("moving tank forward");
    LeftFrontMotor->MoveForward(1);
    RightFrontMotor->MoveForward(1);
    LeftRearMotor->MoveForward(1);
    RightRearMotor->MoveForward(1);
    movingForward = true;
}

void MecanumMotionController::MoveBackward() {
    if (movingBackward)
        return;
    //Logger::Log("moving tank backward");
    LeftFrontMotor->MoveBackward(1);
    RightFrontMotor->MoveBackward(1);
    LeftRearMotor->MoveBackward(1);
    RightRearMotor->MoveBackward(1);
    movingBackward = true;
}

void MecanumMotionController::MoveStop(bool forceStop) {
    if (!forceStop && !turningLeft && !turningRight && !movingForward && !movingBackward)
        return;
    //Logger::Log("stopping tank");
    LeftFrontMotor->MoveStop(false);
    RightFrontMotor->MoveStop(false);
    LeftRearMotor->MoveStop(false);
    RightRearMotor->MoveStop(false);

    turningLeft = false;
    turningRight = false;
    movingForward = false;
    movingBackward = false;
}

void MecanumMotionController::TurnLeft() {
    if (turningLeft)
        return;
    //Logger::Log("turning tank Left");
    LeftFrontMotor->MoveBackward(1);
    RightFrontMotor->MoveForward(1);
    LeftRearMotor->MoveBackward(1);
    RightRearMotor->MoveForward(1);
    turningLeft = true;
}

void MecanumMotionController::TurnRight() {
    if (turningRight)
        return;
    //Logger::Log("turning tank Right");
    LeftFrontMotor->MoveForward(1);
    RightFrontMotor->MoveBackward(1);
    LeftRearMotor->MoveForward(1);
    RightRearMotor->MoveBackward(1);
    turningRight = true;
}

void MecanumMotionController::DigitalMove(DigitalMovement movement) {
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

void MecanumMotionController::AnalogMove(AnalogMovement movement) {
    double powerX = movement.GetAnalogX();
    double powerY = movement.GetAnalogY();
    if (powerY < 0) {
        //analogWrite(LeftForwardPin, LOW);
        //digitalWrite(LeftBackwardPin, -powerY);
        //analogWrite(RightForwardPin, LOW);
        //digitalWrite(RightBackwardPin, -powerY);
    }
    else if (powerY > 0) {
        //analogWrite(LeftForwardPin, powerY);
        //digitalWrite(LeftBackwardPin, LOW);
        //analogWrite(RightForwardPin, powerY);
        //digitalWrite(RightBackwardPin, LOW);
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


