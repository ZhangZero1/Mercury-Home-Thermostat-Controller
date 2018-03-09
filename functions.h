// ========================================================================

#include "DHT.h"

#define DHTPIN 13     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "./javascript.h"
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <time.h>


MDNSResponder mdns;

unsigned long wait000 = 0UL, wait001 = 1000UL;
String onOff="false";
String automatic = "false";
String byPass = "";
int pirPin = 14;
int relayPin = 12;
bool activeState = false;

String timestring="";

ESP8266WebServer server(8080);
DHT dht(DHTPIN, DHTTYPE);


void buildWebsite() {
  buildJavascript();
  //Serial.print("\n\njavascript ======" + javaScript+"\n\n\n\n");
  
  webSite = "<!DOCTYPE HTML>\n";
  webSite += "<META name='viewport' content='width=device-width, initial-scale=1'>\n";
  //webSite += "<link rel='stylesheet' href='https://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css'>";
  //webSite += "<script src='https://code.jquery.com/jquery-1.11.3.min.js'></script>";
  //webSite += "<script src='https://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js'></script>";


  webSite += "<head>";
  webSite += " <script src='https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js'></script>";
  webSite += "<style>";
 
  webSite += "   body  {";
  webSite += "    background: #102c59"; // linear-gradient(to bottom, #102c59, #103063); ";
  webSite += "   }";
  webSite += "  #headBox{";
  webSite += "    color: white;";
  webSite += "    font-size: 20px;";
  webSite += "  width: 1000px;";
  webSite += "  height: 200px;";
  webSite += "  }";
  webSite += "  #date{";
  webSite += "    position: absolute;";
  webSite += "    top: 65px;";
  webSite += "    left: 5px;";

  webSite += "  }";
  webSite += "  #time{";
  webSite += "    position: absolute;";
  webSite += "    top: 65px;";
  webSite += "    left: 880px;";
  webSite += "  }";

  
  webSite += "   h3 { ";
  webSite += "    //color: #89cc1e;";
  webSite += "    color: white;";
  webSite += "    font-size: 70px;";
  webSite += "    text-align: center;";
  webSite += "    position: absolute;";
  webSite += "    top: -50px;";
  webSite += "    left: 300px;";
  webSite += "    font-family: 'Constantia';";
  webSite += "    //text-shadow: -4px -4px DarkBlue;";
  webSite += "   }";
  webSite += "   A {";
  webSite += "    color: white;";
  webSite += "   }";
  webSite += "   span{";
  webSite += "    color: white;";
  webSite += "   }";
  webSite += "   ";
  webSite += "   #Temp{";
  webSite += "    font-size: 250px;";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    font-weight: bold;";
  webSite += "   }";
  webSite += "   #Temperature{";
  webSite += "    font-size: 30px;";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    position: relative;";
  webSite += "    top: -290px;";
  webSite += "    left: 5px;   ";
  webSite += "   }";
  webSite += "   #Degree{";
  webSite += "    border: 5px solid white;";
  webSite += "    width: 30px;";
  webSite += "    height: 30px;";
  webSite += "    border-radius: 50%;";
  webSite += "    position: relative;";
  webSite += "    top: -280px;";
  webSite += "    left: 280px; ";
  webSite += "   }";
  webSite += "   #TempBox{";
  webSite += "    text-align:right;";
  webSite += "    position: absolute;";
  webSite += "    width: 210px;";
  webSite += "    height: 175px;";
  webSite += "    top:  150px;";
  webSite += "    left: 50px;";
  webSite += "   }";
  webSite += "   #TempC{";
  webSite += "    text-align:right;";
  webSite += "    font-size: 80px;";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    font-weight: bold;";
  webSite += "    position: relative;";
  webSite += "    top: -50px; ";
  webSite += "   }";
  webSite += "   #TemperatureC{";
  webSite += "    text-align = right;";
  webSite += "    font-size: 30px;";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    position: relative;";
  webSite += "    top: 70px;";
  webSite += "    left: 90px; ";
  webSite += "   }";
  webSite += "   #TempCBox{";
  webSite += "    text-aligh: right;";
  webSite += "    border-radius: 25px;";
  webSite += "    padding: 20px; ";
  webSite += "    width: 200px;";
  webSite += "    height: 90px;";
  webSite += "    background: #182244;";
  webSite += "    border: 2px solid #3c4960;";
  webSite += "    position: absolute;";
  webSite += "    top: 150px;";
  webSite += "    left: 500px; ";
  webSite += "   }";
  webSite += "   #HumidBox{";
  webSite += "    border-radius: 25px;";
  webSite += "    padding: 20px; ";
  webSite += "    width: 200px;";
  webSite += "    height: 90px;";
  webSite += "    position: absolute;";
  webSite += "    background: #182244;";
  webSite += "    border: 2px solid #3c4960;";
  webSite += "    top: 300px;";
  webSite += "    left: 500px; ";
  webSite += "   }";
  webSite += "   #Humidity{";
  webSite += "    font-size: 80px;";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    font-weight: bold;";
  webSite += "    position: relative;";
  webSite += "    top: -15px;";
  webSite += "    left: 0px;  ";
  webSite += "   }";
  webSite += "   #Humid{";
  webSite += "    font-size: 30px;";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    font-weight: bold;";
  webSite += "    position: relative;";
  webSite += "    top: -25px;";
  webSite += "    left: 90px; ";
  webSite += "   }";
  webSite += "   #PIR{";
  webSite += "    font-size: 50px;";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    position: relative;";
  webSite += "    top: -100px;";
  webSite += "   }";
  webSite += "";
  webSite += "   #slider0{";
  webSite += "    position: relative;";
  webSite += "    top: -100px;";
  webSite += "    left: 200px;";
  webSite += "   }    ";
  webSite += "";
  webSite += "   label{";
  webSite += "    color: white;";
  webSite += "    font-size: 30px;";
  webSite += "    position: relative;";
  webSite += "    top: -230px;";
  webSite += "    left: 500px;";
  webSite += "   }";
  webSite += "   #SliderVal0{";
  webSite += "    font-size: 50px;";
  webSite += "    position: relative;";
  webSite += "    top: -170px;";
  webSite += "    left: 320px;";
  webSite += "";
  webSite += "   }";
  webSite += "";
  webSite += "";
  webSite += "   #onoff{";
  webSite += "    font-size: 30px;";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    position: relative;";
  webSite += "    top: -300px;";
  webSite += "    left: -410px;";
  webSite += "    font-weight: bold;";
  webSite += "   }";
  webSite += "   #autoState{";
  webSite += "    font-size: 30px;";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    position: relative;";
  webSite += "    top: -250px;";
  webSite += "    left: -605px;";
  webSite += "    font-weight: bold;";
  webSite += "   }";
  webSite += "";
  webSite += "";
  webSite += "   .label{";
  webSite += "    float:right;";
  webSite += "    font-family: 'KaiTi';";
  webSite += "";
  webSite += "    font-size: 30px;";
  webSite += "";
  webSite += "  ";
  webSite += "   }";
  webSite += "";
  webSite += "   #button {";
  webSite += "     background-color: #182244; ";
  webSite += "     border: none;";
  
 
  webSite += "     color: white;";
  webSite += "     padding: 16px 16px;";
  webSite += "     text-align: center;";
  webSite += "     text-decoration: none;";
  webSite += "     font-size: 20px;";
  webSite += "     width: 120px;";
  webSite += "     height: 80px;";
  webSite += "     position: relative;";
  webSite += "     top: 0px;";
  webSite += "     left: 0px; ";
  webSite += "   }";

  webSite += "   #button:disabled {";
  webSite += "     background-color: #182244; ";
  webSite += "     border: none;";
  
 
  webSite += "     color: grey;";
  webSite += "     padding: 16px 16px;";
  webSite += "     text-align: center;";
  webSite += "     text-decoration: none;";
  webSite += "     font-size: 20px;";
  webSite += "     width: 120px;";
  webSite += "     height: 80px;";
  webSite += "     position: relative;";
  webSite += "     top: 0px;";
  webSite += "     left: 0px; ";
  webSite += "   }";
  
  webSite += "   #button2 {";
  webSite += "     background-color:#182244;";
  webSite += "     border: none;";
  webSite += "     color: white;";
  webSite += "     padding: 16px 16px;";
  webSite += "     text-align: center;";
  webSite += "     text-decoration: none;";
  webSite += "     font-size: 20px;";
  webSite += "     width: 120px;";
  webSite += "     height: 100px;";
  webSite += "     position: relative;";
  webSite += "     top: 210px;";
  webSite += "     left: 0px; ";
  webSite += "   }";
  webSite += "   #buttonBar{";
  webSite += "    border-radius: 25px;";
  webSite += "    padding: 16px; ";
  webSite += "    width: 120px;";
  webSite += "    height: 390px;";
  webSite += "    background: #182244;";
  webSite += "    border: 2px solid #3c4960;";
  webSite += "    position: absolute;";
  webSite += "    top: 150px;";
  webSite += "    left: 800px; ";
  webSite += "   }";
  webSite += "   #visual{";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    font-size: 70px;";
  webSite += "    color: #3c4960;";
  webSite += "    position: relative;";
  webSite += "    top:  35px;";
  webSite += "    left: 25px;";
  webSite += "   }";

  webSite += "   #submitDat{";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    font-size: 35px;";
  webSite += "    background: #182244;";
  webSite += "    border: 2px solid black;";
  webSite += "    color: white;";
  webSite += "    border: 2px solid #182244; ";
  webSite += "    Height: 40;";
  webSite += "    Width: 100;";
  webSite += "    position: relative;";
  webSite += "    top: -150px;";
  webSite += "    left: 25px;";
  webSite += "   }";
  
  webSite += "   #inputArea{";
  webSite += "    width: 100px;";
  webSite += "    Height: 60px;";
  webSite += "    position: relative;";
  webSite += "    font-size: 50px;";
  webSite += "    text-align: center;";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    font-weight: bold;";
  webSite += "    color: white;";
  webSite += "    border: 2px solid #3c4960;";
  webSite += "    background: #25282d;";
  webSite += "    top: -160px;";
  webSite += "    left: 10px;";
  webSite += "   }";
  webSite += "";
  webSite += "   #EVERYTHING{";
  webSite += "    position: absolute;";
  webSite += "    top: 390px;";
  webSite += "    left: 0px;";
  webSite += "   }";
  
  webSite += "   #AC{";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    font-size: 60px;";
  webSite += "    //border: 2px solid black;";
  webSite += "    color: white;";
  webSite += "     ";
  webSite += "    Height: 80;";
  webSite += "    Width: 500;";
  webSite += "    position: absolute;";
  webSite += "    top: 100px;";
  webSite += "    left:100px;";
  webSite += "   }";

  webSite += "  #weatherforcast{";
  webSite += "    position: absolute;";
  webSite += "    width:300px;";
  webSite += "    top: 80px;";
  webSite += "    left: 500px;";
  webSite += "   }";
  webSite += "";
  webSite += "  .icontext{";
  webSite += "    position: relative;";
  webSite += "    top: -15px;";
  webSite += "    left:50px;";
  webSite += "    }";
  webSite += "";
  webSite += "";
  webSite += "  #snowicon{";
  webSite += "   opacity: 0.4;";
  webSite += "    filter: alpha(opacity=40); ";
  webSite += "    position: relative;";
  webSite += "";
  webSite += "   left:60px;";
  webSite += "   }";
  webSite += "";
  webSite += "  ";
  webSite += "   #onoffindicator{";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    font-size: 60px;";
  webSite += "    //border: 2px solid black;";
  webSite += "    color: white;";
  webSite += "     ";
  webSite += "    position: absolute;";
  webSite += "    top: 100px;";
  webSite += "    left:180px;";
  webSite += "   }";

  webSite += "   #onoffindicator:disabled{";
  webSite += "    font-family: 'KaiTi';";
  webSite += "    font-size: 60px;";
  webSite += "    //border: 2px solid black;";
  webSite += "    color: red;";
  webSite += "     ";
  webSite += "    position: absolute;";
  webSite += "    top: 100px;";
  webSite += "    left:180px;";
  webSite += "   }";


  webSite += "</style>";
  webSite += "</head>";

  
  webSite += javaScript;
  webSite += "<BODY onload='process()'>";
  webSite += "<div id ='headBox'>";
  //webSite += "   <span id='date'>"+timestring.substring(0,10)+timestring.substring(19)+  "</span>";
  webSite += "  <h3> AC Controller </h3>";
  //webSite += "   <span id='time'>"+timestring.substring(11,19)+  "</span>";
  webSite += "</div>";
  webSite += "  <div id='TempBox'>";
  webSite += "   <A id='Temp'>NA</A>";
  webSite += "   <span id='Temperature'>Temperature(F)</span>";
  webSite += "   <div id='Degree'></div>";
  webSite += "  </div>";
  webSite += "  <div id='TempCBox'>";
  webSite += "   <span id='TemperatureC'> Temp. C </span>";
  webSite += "   <A id='TempC'>null</A>";
  webSite += "  </div>";
  webSite += "  <div id='HumidBox'>";
  webSite += "   <A id='Humidity'>null</A>";
  webSite += "   <span id = 'Humid'>Humidity</span>   ";
  webSite += "  </div>";
  webSite += "  <div id='buttonBar'>";
  webSite += "   <button ID='button' data-inline='true'  onclick='toggle()' value='false'> ON/OFF</button>";
  webSite += "   <button ID='button2' data-inline='true' onclick='toggle2()' value='false'> Activate Auto Control</button>";
  webSite += "   <A id='visual'>75</A>";
  webSite += "   <input id='inputArea' type='text'></input>";
  //webSite += "   <button ID='submitDat' data-inline='true' value='false'> XXXXXXX</button>";
  webSite += "   <button ID='submitDat' onclick='setVal()'>SET</button>";
  webSite += "  </div>  ";
  webSite += "  <div id='EVERYTHING'>";
  webSite += "<span ID='AC'>AC&nbsp;</span>\n";
  //webSite +=     buildImage();
  webSite += "   <span ID='onoffindicator'>OFF</span></A>";
  webSite += "   <span ID='weatherforcast'>Farmington CT weather</span></A>";
  webSite += "  </div>";
  webSite += "</BODY>\n";
  webSite += "</HTML>\n";
}



String millis2time() {
  String Time = "";
  unsigned long ss;
  byte mm, hh;
  ss = millis() / 1000;
  hh = ss / 3600;
  mm = (ss - hh * 3600) / 60;
  ss = (ss - hh * 3600) - mm * 60;
  if (hh < 10)Time += "0";
  Time += (String)hh + ":";
  if (mm < 10)Time += "0";
  Time += (String)mm + ":";
  if (ss < 10)Time += "0";
  Time += (String)ss;
  return Time;
}

/*
float tempSample[3] = {-1,-1,-1};

int getLength(float dat[]){
  if(sizeof(dat) == 0){
    return 0;
  }
  return sizeof(dat)/sizeof(dat[0]);
}

*/


/*
float getAverageTemp(){
  float total = 0;
  for(int i= 0; i<getLength(tempSample); i++){
    if(tempSample[i] >= 0){
      total += tempSample[i];
    }else{
      return total/(i+1);
    }
  }
  return total/getLength(tempSample);
}
*/

/*
void setTempSet(float f){
  for(int i= 0; i<getLength(tempSample); i++){
    if(i+1 != getLength(tempSample)){
      tempSample[i] = tempSample[i+1];
    }
    if(tempSample[i] < 0){
      tempSample[i] = f;
      return;
    }
  }
  tempSample[getLength(tempSample)-1] = f;
}
*/


int getTemp(){
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  return f;
  //setTempSet(f);
  //return getAverageTemp();
}

float getTempC(){
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  return t;
}

int getHumid(){
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  return h;

}


String temp(){
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return "null";
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" &#8451 *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  return byPass+"Humidity is : "+ h + "%, Temperature is: " + t+ " &#8451;, Temperature is: " + f+"&#8457;   ";
  
}

String pir(){
  if(digitalRead(pirPin) == HIGH){
     return "Person Detected"; 
  }else if(digitalRead(pirPin) == LOW){
    return "No People Detected"; 
  }else{
    return "failed";
  }
}


void buildXML() {
  XML = "<?xml version='1.0'?>";
  XML += "<xml>";
  XML+="<response>";
  XML+=getTemp();
  XML+="</response>";// poossibly add second xml tag response here
  XML+="<response>";
  XML+=pir();
  XML+="</response>";// poossibly add second xml tag response here
  XML+="<response>";
  XML+=getTempC();
  XML+="</response>";
  XML+="<response>";
  XML+=getHumid();
  XML+="</response>";
  XML+="<target>";
  XML+= ESPval;
  XML+= "</target>";

  
  XML += "<truth>";
  XML += activeState?"ON":"OFF";
  XML += "</truth>";
  XML += "<truth>";
  XML += automatic;
  XML += "</truth>";
  XML += "<millistime>";
  XML += millis2time();
  XML += "</millistime>";
  XML += "</xml>";
}

void handleWebsite() {
  buildWebsite();
  server.send(200, "text/html", webSite);
}

void handleXML() {
  buildXML();
  server.send(200, "text/xml", XML);
}

void handleESPval() {
  ESPval = server.arg("val").toInt();
  buildXML();
  server.send(200, "text/xml", XML);
}

void handleonOff() {
  onOff = server.arg("val");  
  buildXML();
  server.send(200, "text/xml", XML);

}

void handleAuto() {
  automatic = server.arg("val");  
  buildXML();
  server.send(200, "text/xml", XML);
}



