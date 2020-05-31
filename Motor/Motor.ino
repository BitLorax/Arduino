#define KEY 4
#define PWM 3
int i = 0;
void setup() {
    Serial.begin(9600);
    pinMode(PWM,OUTPUT);
    pinMode(KEY,INPUT);
    analogWrite(PWM,0);
}

void loop() {
    // put your main code here, to run repeatedly:
    if(digitalRead(KEY))  
    {   
        delay(10);
        if(digitalRead(KEY))
        { 
            //I2C_Write_Cmd(ADD,0xFFF0);
            Serial.println(i);
            analogWrite(PWM,i);
            i = i + 10;
            if(i >= 130)
            {
                i = 0;
            }
        }
        while(digitalRead(KEY));        
    }
}
