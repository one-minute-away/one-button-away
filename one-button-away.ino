#include <Bridge.h>
//#include <CapacitiveSensor.h>
//#include <HttpClient.h>
#include <Console.h>

String base_url = "https://one-minute-away-api.herokuapp.com";
String user = "575ca0ccf20d8b030050d391";
String token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI1NzVjYTBjY2YyMGQ4YjAzMDA1MGQzOTEiLCJpYXQiOjE0NjU2ODgyNjh9.OP0vYbERkRtlNcJ3rLoT2Pab1ntufV3hg1FRdjqHLpM";
String savedRouteID = "575ca1a9f20d8b030050d392";
String curl_command = "curl -X POST -H \"token: eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI1NzVjYTBjY2YyMGQ4YjAzMDA1MGQzOTEiLCJpYXQiOjE0NjU2ODgyNjh9.OP0vYbERkRtlNcJ3rLoT2Pab1ntufV3hg1FRdjqHLpM\" -H \"Content-Type: application/json\" -H \"Cache-Control: no-cache\" -d '{ \"savedRouteId\":\"575ca1a9f20d8b030050d392\", \"leadTime\":\"5\"}' \"http://one-minute-away-api.herokuapp.com/user/575ca0ccf20d8b030050d391/alert\"";

// LED Setup
int red = 9;
int white = 10;
int green = 11;
int val = 0;


void setup() {
        Serial.begin(9600);
        Bridge.begin();
        Console.begin();


        //Setup LED Pins
        pinMode(red, OUTPUT);
        pinMode(white, OUTPUT);
        pinMode(green, OUTPUT);


//  // Starup Light Show
        digitalWrite(green, HIGH);
        digitalWrite(red, HIGH);
        digitalWrite(white, HIGH);
        delay(1000);
        digitalWrite(green, LOW);
        digitalWrite(red, LOW);
        digitalWrite(white, LOW);

}

void loop() {

        val = digitalRead(3); // read input value
        if (val == HIGH) {   // check if the input is HIGH (button released)
                digitalWrite(red, LOW); // turn LED OFF
        } else {

                digitalWrite(red, HIGH); // turn LED ON
                String httpcode;
                httpcode = createAlert();
                //Serial.write(httpcode);
        }
}
//
String createAlert()
{
        String httpcode;
        Serial.write("Startign curl");
        Process p;
        p.runShellCommand(curl_command);
        while (p.available())
        {
                char c = p.read();
                httpcode = httpcode + c;
                Serial.write(c);
                Console.println(c);
        }
        p.close();
        return httpcode;
}
