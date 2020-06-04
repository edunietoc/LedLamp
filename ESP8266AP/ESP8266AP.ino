#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define REDPIN 16
#define GREENPIN 5
#define BLUEPIN 4


ESP8266WebServer server(80);



const char* ssid = "LEDLamp";
const char* password = "led_lamp";

String getHTML(){

    String htmlPage;
     
    htmlPage += "<!DOCTYPE html>\n";
    htmlPage += "<html lang='en'\n";
    htmlPage += "<head>\n";
    htmlPage +=     "<meta charset='UTF-8'\n";
    htmlPage +=     "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    htmlPage +=     "<title>Document</title>\n";
    htmlPage += "</head>\n";
    htmlPage += "<body>\n";
    htmlPage +=    "<div class='slidecontainer'>\n";
    htmlPage +=        "<p>Red</p>\n";
    htmlPage +=        "<input type='range' min='1' max='255' value='50' class='slider' id='slider_Red' onchange='sendData()'>\n";
    htmlPage +=    "</div>\n";
    htmlPage +=    "<div class='slidecontainer'>\n";
    htmlPage +=        "<p>Green</p> \n";
    htmlPage +=        "<input type='range' min='1' max='255' value='50' class='slider' id='slider_Green' onchange='sendData()'>\n";
    htmlPage +=    "</div>\n";
    htmlPage +=    "<div class='slidecontainer'>\n";
    htmlPage +=        "<p>Blue</p>\n";
    htmlPage +=        "<input type='range' min='1' max='255' value='50' class='slider' id='slider_Blue' onchange='sendData()'>\n";
    htmlPage +=    "</div>\n";
    htmlPage += "</body>\n";
    htmlPage += "<script>\n";
    htmlPage += "let sliderR = document.getElementById('slider_Red');\n";
    htmlPage += "let sliderB = document.getElementById('slider_Blue');\n";
    htmlPage += "let sliderG = document.getElementById('slider_Green');\n";
    htmlPage += "function sendData() {\n";
    htmlPage += "let xhr = new XMLHttpRequest();\n";
    htmlPage += "let rgb = [sliderR.value,sliderG.value,sliderB.value];\n";
    htmlPage += "xhr.open('POST','/data')\n";
    htmlPage +=     "xhr.send(rgb);\n";
    htmlPage +=     "console.log('sent to server',rgb)}\n";
    htmlPage += "</script>\n";
    htmlPage += "</html>";


    return htmlPage;
}

void handle_OnConnect(){
    server.send(200,"text/html",getHTML());
}

void handleData(){
   
    String data = String(server.arg("plain"));
    Serial.print("\n Received data from the page: ");
    Serial.print(data +"\n");
    server.send(200,"text/html","some data");
    setRGB(data);
}

void setRGB(String values){
    int RGB[3];
    int cont = 0;
    String buffer;

    for (int i = 0; i <= values.length(); i++){
        
        if( (values[i] ==',') || (values[i] == NULL) ){
            
            RGB[cont] = buffer.toInt();
            cont++;
            buffer="";
            continue;
            
        }

        if(isDigit(values[i])==true){
          buffer += values[i];
        }
        
    }
    
    Serial.print("\nRed: ");
    Serial.print(RGB[0]+'\n');
    Serial.print("\nGreen: ");
    Serial.print(RGB[1]+'\n');
    Serial.print("\nBlue: ");
    Serial.print(RGB[2]+'\n');

    setLEDColor(RGB);

}

void setLEDColor(int RGB[3]){

analogWrite(REDPIN,RGB[0]);
analogWrite(GREENPIN,RGB[1]);
analogWrite(BLUEPIN,RGB[2]);
delay(10);

}


void setup(){

    Serial.begin(115200);
    delay(5);
    WiFi.softAP(ssid,password);

    while ( WiFi.status() != WL_CONNECTED  ){
        delay(500);
        Serial.print(".");
        
    }
    delay(200);
    Serial.print("\n");
    Serial.printf("Connected to %s \n", ssid);

    server.on("/", handle_OnConnect);
    server.on("/data", handleData);
    server.begin();
    Serial.println("Server started on"); 
    String MyIP = WiFi.softAPIP().toString();
    Serial.println( MyIP );
    
}

void loop(){
    
server.handleClient();


}
