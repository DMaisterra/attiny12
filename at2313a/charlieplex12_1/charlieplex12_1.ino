
//at tiny 2313
// INT0 (D 4) PD2  6|    |
// INT1 (D 5) PD3  7|    |
//      (D 6) PD4  8|    |
//     *(D 7) PD5  9|    |
//            GND 10|    |

#define PIN_CONFIG 0
#define PIN_STATE 1
 
#define LED_COUNT 9


int A = 7;
int B = 6;
int C = 5;
int D = 4;


//void setup1() {
//   pinMode(out0,OUTPUT);
//   pinMode(out1,OUTPUT);
//   pinMode(out2,INPUT);
//   digitalWrite(out0,HIGH);
//   digitalWrite(out1,LOW);
//}


 
int matrix[LED_COUNT][2][4] = {
// PIN_CONFIG --- PIN_STATE
// A B C D    --- A B C D
{ { OUTPUT, OUTPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // AB 0
{ { OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // BA 1
{ { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // BC 2
{ { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // CB 3
{ { OUTPUT, INPUT, OUTPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // AC 4
{ { OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // CA 5
{ { OUTPUT, INPUT, INPUT, OUTPUT }, { HIGH, LOW, LOW, LOW } }, // AD 6
{ { OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // DA 7
{ { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, HIGH, LOW, LOW } }; // BD 8
/*
{ { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // DB 9
{ { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, HIGH, LOW } }, // CD 10
{ { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } } // DC 11
};*/
 
void turnOn( int led ) {
pinMode( A, matrix[led][PIN_CONFIG][0] );
pinMode( B, matrix[led][PIN_CONFIG][1] );
pinMode( C, matrix[led][PIN_CONFIG][2] );
pinMode( D, matrix[led][PIN_CONFIG][3] );
digitalWrite( A, matrix[led][PIN_STATE][0] );
digitalWrite( B, matrix[led][PIN_STATE][1] );
digitalWrite( C, matrix[led][PIN_STATE][2] );
digitalWrite( D, matrix[led][PIN_STATE][3] );
}
 
void setup() {}
 
void loop() {
for( int l = 0; l < LED_COUNT; l++ ) {
turnOn( l );
delay( 1000 / LED_COUNT );
}
}

