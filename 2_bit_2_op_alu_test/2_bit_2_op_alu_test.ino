#define AND 0
#define PLUS 1


const int inA_1 = 9;
const int inA_0 = 8;

const int inB_1 = 7;
const int inB_0 = 6;

const int inOp = 5;


String toBinary(int val, int bits) {
  String result;
  result.reserve(bits);
  
  for (int i = 0; i < bits; i++) {
    result += (val & (1 << (bits - 1 - i))) ? '1' : '0';
  }

  return result;
}


void testOperation(int a, int b, int operation) {
  digitalWrite(inA_1, (a >> 1) & 1);
  digitalWrite(inA_0, a&1);
  digitalWrite(inB_1, (b >> 1) & 1);
  digitalWrite(inB_0, b&1);
  digitalWrite(inOp, operation);

  String operationSymbol;
  int res;
  int carryBit;
  if (!operation) {
    operationSymbol = "AND";
    res = a&b;
    carryBit = 0; 
  } else {
    operationSymbol = "+";
    res = a+b;
    carryBit = (res >> 2) & 1; 
  }

  char buf[64];
  sprintf(buf, "Test: A=%s, B=%s, OP=%d\n", toBinary(a, 2).c_str(), toBinary(b, 2).c_str(), operation);
  Serial.print(buf);

  sprintf(buf, "Expected output: CARRY=%d, OUT_1=%d, OUT_0=%d\n\n", carryBit, (res >> 1) & 1, res&1);
  Serial.print(buf);
}


void testAND() {
  for (int a=0; a<4; ++a) {
    for (int b=0; b<4; ++b) {
      testOperation(a, b, AND);
      delay(5000);
    }
  }
}


void testPLUS() {
  for (int a=0; a<4; ++a) {
    for (int b=0; b<4; ++b) {
      testOperation(a, b, PLUS);
      delay(2500);
    }
  }
}


void testALU() {
  Serial.println("Testing AND");
  testAND();

  Serial.println();
 
  Serial.println("Testing PLUS");
  testPLUS();
}


void setup() {
  Serial.begin(9600);
  
  pinMode(inA_1, OUTPUT);
  pinMode(inA_0, OUTPUT);
  pinMode(inB_1, OUTPUT);
  pinMode(inB_0, OUTPUT);
  pinMode(inOp, OUTPUT);
  
  digitalWrite(inA_1, LOW);
  digitalWrite(inA_0, LOW);
  digitalWrite(inB_1, LOW);
  digitalWrite(inB_0, LOW);
  digitalWrite(inOp, LOW);
}


void loop() {
  delay(5000);
  Serial.print("Tesing 2 bit ALU with operations AND and PLUS\n\n");
  testALU();  
}
