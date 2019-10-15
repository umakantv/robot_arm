#include <AFMotor.h>
#include <math.h>

AF_DCMotor motor_1(1);
AF_DCMotor motor_2(2);
AF_DCMotor motor_3(3);

struct Motor_Data {
    int sign;
    int current;
    

    // Motor_Data(int s) {
    //     sign = s;
    // }
    
    void readCurrent() {
        current = map(analogRead(sign), 0, 1023, 0, 280);
    }
};

struct State {
    float theta;  // motor 1 angle
    float height;
    float radius;
    float alpha;  // motor 2 angle
    float beta;  // motor 3 angle

    void update_angles(float the, float alp, float bet) {
        theta = the;
        alpha = alp;
        beta = bet;
    }

    void update_coord(float h, float r) {
        height = h;
        radius = r;
    }

    bool find_angles(int a, int b) {
        float r = radius;
        float h = height;
        alpha = atan(r/h) + asin((h*h + r*r + a*a - b*b) / (2* a * pow(h*h + r*r, 0.5)));

        beta = alpha + asin((h-a* sin(alpha))/b);
        
        if(isnan(alpha) || isnan(beta)) return 0;
        
        alpha = alpha * 180 / 3.1415;
        beta = beta * 180 / 3.1415;
        return 1;
    }
    void find_coord(float arm1, float arm2) {
        height = arm1*sin(alpha) + arm2*sin(beta-alpha);
        radius = arm1*cos(alpha) + arm2*cos(beta-alpha);
    }
};

struct Robot {
    float arm1 = 18.0;
    float arm2 = 17.0;
    bool    result = false, // true if goal possible
            flag = true;    // true if goal is achieved
    State goal, current;
    int cmds[3] = {BRAKE, BRAKE, BRAKE};

    Motor_Data motor1, motor2, motor3;

    Robot(float h, float r, float theta) {
        goal.radius = r;
        goal.height = h;
        goal.theta = theta;
        if(goal.find_angles(arm1, arm2)) result = true;
        else result = false;
        
        motor1.sign = A8;
        motor2.sign = A9;
        motor3.sign = A10;
    }

    void overrideGoal(float a, float b, float t) {
       result = true;
       goal.alpha = a;
       goal.beta = b;
       goal.theta = t;
    }

    void update_stuff() {
//         motor1.readCurrent();
//         motor2.readCurrent();
//         motor3.readCurrent();
        
        motor1.current = map(analogRead(A8), 0, 1023, 0, 280);
        motor2.current = map(analogRead(A9), 0, 1023, 0, 280);
        motor3.current = map(analogRead(A10), 0, 1023, 0, 280);

        current.update_angles(map(motor1.current, 42, 171, 0, 360), motor2.current-30, motor3.current-30);
    }

    bool check() {
        update_stuff();
        bool f1 = false, f2 = false, f0 = false;
        if( current.alpha > goal.alpha + 3 || current.alpha < goal.alpha - 3 ) {
            flag = false;
            motor_2.setSpeed(200);
            if (current.alpha > goal.alpha ) {
                cmds[1] = BACKWARD;
                Serial.print("Will move Motor 2 Backwards\n");
            } else {
                cmds[1] = FORWARD;
                Serial.print("Will move Motor 2 Forwards\n");
            }
        } else {
            motor_2.setSpeed(0);
            
            cmds[1] = BRAKE;
            f1 = true;
        }
        if( current.beta > goal.beta + 3 || current.beta < goal.beta - 3  ) {
            flag = false;
            motor_3.setSpeed(200);
            if (current.beta > goal.beta ) {
                cmds[2] = BACKWARD;
                Serial.print("Will move Motor 3 Backwards\n");
            } else {
                cmds[2] = FORWARD;
                Serial.print("Will move Motor 3 Forwards\n");
            }
        } else {
            motor_3.setSpeed(0);
            cmds[2] = BRAKE;
            f2 = true;
        }
        
        if( current.theta > goal.theta + 3 || current.theta < goal.theta - 3 ) {
            flag = false;
            motor_1.setSpeed(200);
            if (current.theta > goal.theta ) {
                cmds[0] = BACKWARD;
                Serial.print("Will move Motor 1 Backwards\n");
            } else {
                cmds[0] = FORWARD;
                Serial.print("Will move Motor 1 Forward\n");
            }
        } else {
            motor_1.setSpeed(0);
            cmds[0] = BRAKE;
            f0 = true;
        }
        if(f0 && f1 && f2) flag = true;
        return flag;
    }
    void perform() {
        motor_1.run(cmds[0]);
        motor_2.run(cmds[1]);
        motor_3.run(cmds[2]);
    }
};

Robot rob(10, 5, 20);


void setup() {
  Serial.begin(9600);
  rob.overrideGoal(3, 3, 3);


  // turn on motor #1
  motor_1.setSpeed(200);
  motor_1.run(RELEASE);
  motor_2.setSpeed(200);
  motor_2.run(RELEASE);
  motor_3.setSpeed(200);
  motor_3.run(RELEASE);
}


void print_debug_output() {
  Serial.print("Goal:");
    Serial.print("\t alpha: ");
    Serial.print(rob.goal.alpha);
    Serial.print("\t beta: ");
    Serial.print(rob.goal.beta);
    Serial.print("\t theta: ");
    Serial.print(rob.goal.theta);
    Serial.print("\n");

    
        
//    int x1 = (map(analogRead(A8), 0, 1023, 0, 280)%40)*3;
//    int x2 = map(analogRead(A9), 0, 1023, 0, 280)-30;
//    int x3 = map(analogRead(A10), 0, 1023, 0, 280)-30;

      rob.update_stuff();

     Serial.print("Current: ");
     Serial.print("\t alpha: ");
     Serial.print(rob.current.alpha);
     Serial.print("\t beta: ");
     Serial.print(rob.current.beta);
     Serial.print("\t theta: ");
     Serial.print(rob.current.theta);
     Serial.print("\n");
}

void loop() {
//     readInt(num);
//     if ( verify(num)) angle2 = num;

      print_debug_output();
       
    if(rob.result != false) {
        // Goal is possible
        if(!rob.check()) rob.perform();
    } else {
        // Goal not possible
        Serial.print("Goal is not possible! Try Smaller coordinates\n");
    }  

//    delay(500);
}
