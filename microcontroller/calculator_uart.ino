String input = "";

bool isNumber(String value) {
  if (value.length() == 0) {
    return false;
  }

  int startIndex = 0;

  if (value.charAt(0) == '-') {
    if (value.length() == 1) {
      return false;
    }
    startIndex = 1;
  }

  for (int i = startIndex; i < value.length(); i++) {
    if (!isDigit(value.charAt(i))) {
      return false;
    }
  }

  return true;
}

bool parseExpression(String expression, long &a, long &b, char &op) {
  expression.replace(" ", "");

  int operatorIndex = -1;

  for (int i = 1; i < expression.length(); i++) {
    char c = expression.charAt(i);

    if (c == '+' || c == '-' || c == '*' || c == '/') {
      operatorIndex = i;
      op = c;
      break;
    }
  }

  if (operatorIndex == -1) {
    return false;
  }

  String left = expression.substring(0, operatorIndex);
  String right = expression.substring(operatorIndex + 1);

  if (!isNumber(left) || !isNumber(right)) {
    return false;
  }

  a = left.toInt();
  b = right.toInt();

  return true;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    input.trim();

    long a = 0;
    long b = 0;
    long result = 0;
    char op;

    if (!parseExpression(input, a, b, op)) {
      Serial.println("Fehler: Ungueltige Eingabe");
      return;
    }

    if (op == '+') {
      result = a + b;
    } else if (op == '-') {
      result = a - b;
    } else if (op == '*') {
      result = a * b;
    } else if (op == '/') {
      if (b == 0) {
        Serial.println("Fehler: Division durch 0");
        return;
      }
      result = a / b;
    } else {
      Serial.println("Fehler: Unbekannter Operator");
      return;
    }

    Serial.println(result);
  }
}