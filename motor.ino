/* move motor in counter-clockwise direction*/
void motor_move_ccw()
{
 digitalWrite(motor_in1,HIGH);
 digitalWrite(motor_in2,LOW);
}
/* move motor in clockwise direction*/
void motor_move_cw()
{
 digitalWrite(motor_in1,LOW);
 digitalWrite(motor_in2,HIGH);
}
/* initiate motor*/
void motor_init()
{
// set motor pins as output
pinMode(motor_in1,OUTPUT);
pinMode(motor_in2,OUTPUT);
// start with no motion
digitalWrite(motor_in1,LOW);
digitalWrite(motor_in2,LOW);

}
/* stop motor */
void motor_stop()
{
 digitalWrite(motor_in1,LOW);
 digitalWrite(motor_in2,LOW);
}
/* hold motor */
void motor_hold()
{
 digitalWrite(motor_in1,HIGH);
 digitalWrite(motor_in2,HIGH);
}

