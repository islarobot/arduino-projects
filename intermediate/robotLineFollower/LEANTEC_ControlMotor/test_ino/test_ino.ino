// Motor A
int ENA = 11;
int IN1 = 8;
int IN2 = 9;

// Motor B
int ENB = 11;
int IN3 = 8;
int IN4 = 9;

void setup ()
{
 // Declaramos todos los pines como salidas
 pinMode (ENA, OUTPUT);
 //pinMode (ENB, OUTPUT);
 pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);
 //pinMode (IN3, OUTPUT);
 //pinMode (IN4, OUTPUT);
}

void Adelante ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 //digitalWrite (IN3, HIGH);
 //digitalWrite (IN4, LOW);
 //analogWrite (ENB, 255); //Velocidad motor B
}

void Atras ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 128); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 128); //Velocidad motor B
}


void Derecha ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 200); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 100); //Velocidad motor A
}

void Izquierda ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 50); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 150); //Velocidad motor A
}

void Parar ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Velocidad motor A
}

void loop ()
{
 Adelante ();
 delay (2000);
 //Atras ();
 //delay (3000);
 //Derecha ();
 //delay (2000);
 //Izquierda ();
 //delay (2000);
 Parar ();
 delay (2000);
}

