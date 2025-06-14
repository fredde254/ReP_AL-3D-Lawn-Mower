
void Motor_Action_Go_Mowing_Speed() {

  // No Mag speed adjustment active just go full speed
  if (MAG_Speed_Adjustment == 0) Motor_Action_Go_Full_Speed();

  // Adjust wheel speed according to the MAG level
  if (MAG_Speed_Adjustment == 1) {
    if (MAG_Now >= Slow_Speed_MAG) {
      Motor_Action_Go_Full_Speed();
    }

    if (MAG_Now < Slow_Speed_MAG)  {
      Motor_Action_Go_Slow_Speed();
    }
  }
}

void Motor_Action_Go_Full_Speed()     {

  // Full straighgt speed no motr speed ramp up.
  if (Ramp_Motor_ON == 0) {
#if defined(ROBOT_MOWER)
    analogWrite(ENAPin, PWM_MaxSpeed_RH);                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
    analogWrite(ENBPin, PWM_MaxSpeed_LH);                       // Anaolgwirte sends PWM signals Speed = 0-255  (255 is max speed)
#endif


Serial.print(F("Wheel:FULL|"));
  }

  // If Ramp up is achieved just go full speed
  if ((Ramp_Motor_ON == 1) && (Full_Speed_Achieved == 1)) {

#if defined(ROBOT_MOWER)
    analogWrite(ENAPin, PWM_MaxSpeed_RH);                              // Ramp up the motor speed
    analogWrite(ENBPin, PWM_MaxSpeed_LH);                              // Ramp up the motor speed
#endif

Serial.print(F("Wheel:R-FULL|"));
  }

  // Ramp motor option
  if ((Ramp_Motor_ON == 1) && (Full_Speed_Achieved == 0)) {

    Serial.print(F("|WRamp: "));

    int Motor_Step = 150;

    while (Motor_Step > 1) {

#if defined(ROBOT_MOWER)
      analogWrite(ENAPin, (PWM_MaxSpeed_RH - Motor_Step));                       // Ramp up the motor speed
      analogWrite(ENBPin, (PWM_MaxSpeed_LH - Motor_Step));                       // Ramp up the motor speed
#endif

delay(60);
      //Serial.print(F("Step: "));
      //Serial.println(Motor_Step);
      Motor_Step = Motor_Step - 10;
    }

    Serial.print(F("Wheel:S-FULL|"));
    Full_Speed_Achieved = 1;
  }


}

void Motor_Action_Go_Slow_Speed()     {
#if defined(ROBOT_MOWER)
  analogWrite(ENAPin,  PWM_Slow_Speed_RH);                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
  analogWrite(ENBPin,  PWM_Slow_Speed_LH);                       // Anaolgwirte sends PWM signals Speed = 0-255  (255 is max speed)
#endif


Serial.print(F("Wheel:SLOW|"));
}

void Motor_Action_GoFullSpeed_Out_Garage()     {
  //Speeds can be changed to give the mower a slight curve when exiting the Garage.

  PWM_MaxSpeed_LH = PWM_MaxSpeed_LH + 20;
  if (PWM_MaxSpeed_LH > 255)  PWM_MaxSpeed_LH = 255;
  if (PWM_MaxSpeed_RH > 255)  PWM_MaxSpeed_RH = 255;

#if defined(ROBOT_MOWER)
  analogWrite(ENAPin, PWM_MaxSpeed_RH);                                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
  analogWrite(ENBPin, PWM_MaxSpeed_LH);
#endif

Serial.print(F("Wheel:FULL|"));
}


void SetPins_ToGoForwards()     {                                 // Motor Bridge pins are set for both motors to move forwards.

#if defined(ROBOT_MOWER)
  digitalWrite(IN1Pin, LOW);                                      // Motor Birdge pins are set to high or low to set the direction of movement
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
#endif

Serial.print(F("Wheel:For|"));
}


void SetPins_ToGoBackwards()      {                               // Motor Bridge pins are set for both motors to move Backwards
#if defined(ROBOT_MOWER)
  digitalWrite(IN1Pin, HIGH);                                     // Motor 1
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);                                     // Motor 2
  digitalWrite(IN4Pin, LOW);
#endif

Serial.print(F("Wheel:Rev|"));
  delay(20);
}


void Motor_Action_Stop_Motors()  {                                     // Motor Bridge pins are set for both motors to stop
#if defined(ROBOT_MOWER)
  digitalWrite(ENAPin, 0);
  digitalWrite(IN1Pin, LOW);                                    //Motor 1
  digitalWrite(IN2Pin, LOW);
  digitalWrite(ENBPin, 0);                                      //Motor 2
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);
#endif

Serial.print(F("Wheel:0FF|"));

  Full_Speed_Achieved = 0;
}


void SetPins_ToTurnLeft()       {                              // Pins are set so that Motors drive in opposite directions
#if defined(ROBOT_MOWER)
  digitalWrite(IN1Pin, LOW);                                   // Motor 1
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, HIGH);                                  // Motor 2
  digitalWrite(IN4Pin, LOW);
#endif

Serial.print(F("Wheel:TL_|"));
}


void SetPins_ToTurnRight() {                                    // Pins are set so that Motors drive in opposite directions
#if defined(ROBOT_MOWER)
  digitalWrite(IN1Pin, HIGH);                                   // Motor 1
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, LOW);                                    //Motor 2
  digitalWrite(IN4Pin, HIGH);
#endif

Serial.print(F("Wheel:R|"));
}


// USed to turn the mower at a set speed.
void Motor_Action_Turn_Speed() {
#if defined(ROBOT_MOWER)
  analogWrite(ENAPin, (PWM_MaxSpeed_RH - Turn_Adjust) );                                  // Change the 0 value to 10 or 20 to recuce the speed
  analogWrite(ENBPin, (PWM_MaxSpeed_LH - Turn_Adjust) );                                  // Change the 0 value to 10 or 20 to recuce the speed
#endif

}


// Turns the mowing blades on
void Motor_Action_Spin_Blades()  {

  if (Robot_Type == 1) {
    if (Cutting_Blades_Activate == 1) {                                       // Blades are turn ON in settings and will spin!
      delay(20);
      digitalWrite(R_EN, HIGH);
      digitalWrite(L_EN, HIGH);
      delay(20);
      analogWrite(RPWM, PWM_Blade_Speed);
      delay(20);
      Serial.print(F("Blades:ON_|"));
    }

    if (Cutting_Blades_Activate == 0) {                                     // Blades are turn off in settings and will not spin!
      void StopSpinBlades();

    }
  }
}


void Motor_Action_Stop_Spin_Blades()  {

  if (Robot_Type == 1) {
    delay(20);
    digitalWrite(R_EN, LOW);
    digitalWrite(L_EN, LOW);
    delay(20);
    Serial.print(F("Blades:0FF|"));
  }
}


//Steers the Mower depending on the PID input from the Algorythm
void Motor_Action_Dynamic_PWM_Steering() {
#if defined(ROBOT_MOWER)
  analogWrite(ENAPin, PWM_Right);                             // ENA low = Right Swerve   ENB low = Left Swerve
  analogWrite(ENBPin, PWM_Left);
#endif

Serial.print(F("PWM_R:"));
  Serial.print(PWM_Right);
  Serial.print(F("|"));
  Serial.print(F("PWM_L:"));
  Serial.print(PWM_Left);
  Serial.print(F("|"));
}



void Set_Mecanum_Forwards_Left_Front() {
  }

void Set_Mecanum_Backwards_Left_Front() {
  }

void Set_Mecanum_Forwards_Right_Front() {
  }

void Set_Mecanum_Backwards_Right_Front() {
  }


void Set_Mecanum_Forwards_Left_Rear() {
  }

void Set_Mecanum_Backwards_Left_Rear() {
  }

void Set_Mecanum_Forwards_Right_Rear() {
  }

void Set_Mecanum_Backwards_Right_Rear() {
  }

void Full_Speed_Mecanum_Left_Rear() {
  }

void Full_Speed_Mecanum_Right_Rear() {
  }

void Full_Speed_Mecanum_Left_Front() {
  }

void Full_Speed_Mecanum_Right_Front() {
  }

void Mecanum_Side_Movement_Left() {
  }


void Mecanum_Side_Movement_Right() {
  }

void Mecanum_Diagonal_Movement_Left() {
  }


void Mecanum_Diagonal_Movement_Right() {
  }

void Mecanum_Rear_Steer_Right() {
  }


void Mecanum_Rear_Steer_Left() {
  }
