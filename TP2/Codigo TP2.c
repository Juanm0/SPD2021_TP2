/*
Alumnos:
Juan Navarro
Pablo Hernandez
Ramiro Mazzola
Div 1G
*/
#include <Keypad.h>
#include <LiquidCrystal.h>

#define FIL 4
#define COL 4

#define BOTON_M1 1
#define BOTON_M2 2
#define NO_BOTON 0



char tecladoMatriz[FIL][COL] = {
{'1', '2', '3', '+'},
{'4', '5', '6', '-'},
{'7', '8', '9', '*'},
{'A', '0', '=', '/'}
};

byte pinFila[FIL] = {12, 11, 10, 9};
byte pinCol[COL] = {A1, A2, A3, A4};

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
Keypad TECLADO = Keypad(makeKeymap(tecladoMatriz), pinFila, pinCol, FIL, COL);
//todas las teclas cargadas
String num1;
String num2;
String num3;
int total;
int movimiento;
char op;
int op1;
int op2;
int contIgual=0;
int botonAntes = NO_BOTON;
int M1;
int M2=0;
bool valorActual = false;
bool siguiente = false;
bool finaly = false;
bool flagNum1 = false;
bool flagNum2 = false;
bool flagTotal = false;

void setup(){
    lcd.begin(16,2);
    lcd.setCursor(0,0);
}

void loop(){
  int botonAhora = leerBoton();
    char teclaPresionada = TECLADO.getKey();//devuelve las teclas que le cargamos
    if (teclaPresionada != NO_KEY && (teclaPresionada=='1'||teclaPresionada=='2'||
        teclaPresionada=='3'||teclaPresionada=='4'||teclaPresionada=='5'||teclaPresionada=='6'||
        teclaPresionada=='7'||teclaPresionada=='8'||teclaPresionada=='9'||teclaPresionada=='0'))
      //valida que la tecla que se presiona no sea un nokey y se fija si es 9-0
    {
      if (valorActual != true)
      {
        num1 = num1 + teclaPresionada;//suma un char a un string
        movimiento = num1.length();//devuelve el tamaño del string en int
        lcd.setCursor(0,0);
        lcd.print(num1);
        op1 = num1.toInt();
        flagNum1 = true;
      }
      else
      {
        num2 = num2 + teclaPresionada;
        lcd.setCursor(movimiento+3, 0);
        lcd.print(num2);
        op2 = num2.toInt();
        finaly = true;//Bandera sirve hacer '='
        flagNum1 = false;
        flagNum2 = true;
      }
    }

    else if (valorActual == false && teclaPresionada != NO_KEY && (teclaPresionada == '/' ||
            teclaPresionada == '*' || teclaPresionada == '-' || teclaPresionada == '+'))
    {
      if (valorActual == false)
      {
        valorActual = true;
        op = teclaPresionada;//'+' , '-' , '*' y '/'
        lcd.setCursor(movimiento+1,0);
        lcd.print(op);
      }
    }
    else if (teclaPresionada != NO_KEY && teclaPresionada == 'A'){

      	op1 = op1*(-1);//ACÁ SE INVIERTE EL NUMERO
        lcd.setCursor(0,0);
        if(op1 > 0)
        {
          lcd.print('+');
        }
        lcd.print(op1);
      }
  else if (finaly == true && teclaPresionada != NO_KEY && teclaPresionada == '='){//aca
     total = calcularTotal(op, op1,op2);
    num3=String(total);
    lcd.clear();
    lcd.setCursor(16,1);
    lcd.autoscroll();
    if(total==' '){
      lcd.setCursor(14,0);
      lcd.print("Sintax Error");
    }else if(num3.length()>4){
      lcd.print("No hay memoria");
    }else{
      lcd.print('=');
      lcd.setCursor(17,1);
      lcd.print(total);
      flagNum1 = false;
      flagNum2 = false;
      flagTotal = true;
    }
    lcd.noAutoscroll();//Desactiva que scroll de derecha a izquierda
  }
  if(botonAhora != NO_BOTON && botonAhora != botonAntes)
  {
    switch(botonAhora)
    {
      case BOTON_M1:
      if(flagNum1 == true){
        M1 = op1;
      }
      if(flagTotal == true)
      {
        if(total == ' '){
          M1 = 0;
        }
        else{
          M1 = total;
        }
      }
      if(flagNum2 == true){
        M1 = op2;
      }
      lcd.setCursor(0,1);
      lcd.print("M1");
      M2 = M2 + M1;

        break;

      case BOTON_M2:
      lcd.clear();
      lcd.setCursor(16,1);
      lcd.autoscroll();
      lcd.print("M2=");
      lcd.setCursor(19,1);
      lcd.print(M2);
      lcd.noAutoscroll();
        break;
    }
  }
  botonAntes = botonAhora;
  if(teclaPresionada == '=')
    {
      contIgual++;
      if(contIgual==2){
        lcd.clear();
        contIgual=0;
        valorActual = false;
        finaly = false;
        num1 = "";
        num2 = "";
        total = 0;
        op = ' ';
      }
    }
}//FIN DEL LOOP

int calcularTotal (char op, int op1, int num2){//Recibe la operacion que hay que realizar
int resultado;//y el num1 y num2. Y calcula dicha operacion. Retorna el resultado.
  switch(op)
      {
        case '+':
    	resultado = suma(op1,num2);
        break;

        case '-':
          resultado = resta(op1, num2);
        break;

        case '*':
         resultado = multiplicacion(op1, num2);
        break;

        case '/':
          resultado = division(op1, num2);
        break;
      }
  return resultado;
}
int suma (int num1, int num2){ //realiza la suma de 2 numeros
int resultado;//Recibe el operando 1 y el operando 2 y devuelve el resultado de su suma
   if(num1==0){
           resultado = 0 + num2;
          }
          else{
            resultado = num1 + num2;
          }
  return resultado;
}
int resta (int num1, int num2){ // realiza la resta de 2 numeros
int resultado;//Recibe el operando 1 y el operando 2 y devuelve el resultado de su resta
  if(num1==0){
          resultado = 0 - num2;
        }
        else{
          resultado = num1 - num2;
        }
  return resultado;
}
int multiplicacion(int num1, int num2){ // realiza la multiplicacion de 2 numeros
int resultado;//Recibe el operando 1 y el operando 2 y devuelve el resultado de su producto
  resultado = num1 * num2;
  return resultado;
}
int division(int num1, int num2){ //realiza la division entre 2 numeros
float resultado;//Recibe el operando 1 y el operando 2 y devuelve el resultado de su division
  if(num2==0){
          resultado = ' ';
          }else{
          resultado = (float) num1 / num2;
          }
return resultado;//total
}
int leerBoton()//Funcion que devuelve el boton que precionas
{
  int valorA0 = analogRead(A0);

  if(valorA0 > 502 && valorA0 < 522)//Por el +-5%
    return BOTON_M1;

  if(valorA0 > 672 && valorA0 < 692)
    return BOTON_M2;

  return NO_BOTON;
}
