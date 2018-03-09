/*  ArduinoIDE 1.6.12 compiled on Linux Mint 17.3
    Sketch uses 245,617 bytes (23%) of program storage space. Maximum is 1,044,464 bytes.
    Global variables use 37,048 bytes (45%) of dynamic memory, leaving 44,804 bytes for local variables. Maximum is 81,920 bytes.
*/

#include "./functions.h"
#include <Streaming.h>                  // http://arduiniana.org/libraries/streaming/


const char* ssid     = "USERNAME";       // ERASE prior to publishing
const char* password = "PASSWORD";    //   "" ditto



const char* www_username = "admin";
const char* www_password = "ae";

int onCounter = 0;
int offCounter = 0;
int timezone = -5;
int dst = 1;

void setup() {
  //pinMode(LED, OUTPUT);
  Serial.begin(19200); delay(100);
  Serial << (F("... Attempting to log into router... \r\n"));

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  WiFi.mode(WIFI_STA);

  Serial << (F("\n\nBOOTING ESP8266 ..."));
  Serial << (F("Connected to ")) << ssid << endl;
  Serial << (F("Station IP address: ")) << WiFi.localIP() << endl;

  configTime(timezone * 3600, dst*3600, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
  Serial.print(".");
    delay(1000);
  }
  
  server.on("/", [](){
    if(!server.authenticate(www_username, www_password)){
      return server.requestAuthentication();
    }
    handleWebsite();
  });
    //server.on("/",          handleWebsite);
    server.on("/xml",       handleXML);
    server.on("/setesp", handleESPval);
    server.on("/setbuttonval", handleonOff);
    server.on("/setbuttonval2", handleAuto);
  
  server.begin();

    dht.begin();
    delay(50);
    digitalWrite(relayPin, LOW);
    delay(3000);
    digitalWrite(relayPin, HIGH);
    delay(3000);
}

void loop() {
  server.handleClient();
  time_t now  = time(nullptr);
  timestring = ctime(&now);
  Serial.println(ctime(&now));
  delay(1100);
  
  if(automatic == "true"){
    int t = getTemp();
    if(t == -1){
      // do not adjust anything
    }else{
     
      if( t > (ESPval+1)){
         offCounter = 0;
         onCounter += 1;
         if(onCounter >= 10){
             activeState = true;
             onCounter =0;
         }
  
      }
      else if (t< (ESPval-1)){
        offCounter += 1;
         onCounter = 0;
         if(offCounter >= 10){
             activeState = false;
             offCounter =0;
         }
      }
    }
  }else if (automatic == "false"){
    if(onOff == "true"){
      activeState = activeState == false;
      onOff = "false";  
    }
  }
   
  
  if (activeState){
    digitalWrite(relayPin, LOW);
    delay(200);
    }
  else{ 
    digitalWrite(relayPin, HIGH);
    delay(200);
  }
}
  
/*
 * 
 *
 *-- connects to a NIST Daytime server to get the current date and time

TZ=-5       -- my time zone is Eastern Standard Time
year=0      -- global year
month=0     -- global month
day=0       -- global day
hour=0      -- global hour
minute=0    -- global minute
second=0    -- global second

function getDayTime()
   local tt=0
   
   local conn=net.createConnection(net.TCP,0) 
   conn:connect(13,"time.nist.gov")
   
   -- on connection event handler
   conn:on("connection", 
      function(conn, payload)
         --print("Connected...")
      end -- function
   ) -- end of on "connecttion" event handler
         
   -- on receive event handler         
   conn:on("receive",
      function(conn,payload) 
        --print(payload)
        --1234567890123456789012345678901234567890123456789 
        -- JJJJJ YR-MO-DA HH:MM:SS TT L H msADV UTC(NIST) *
        if string.sub(payload,39,47)=="UTC(NIST)" then
           year=tonumber(string.sub(payload,8,9))+2000
           month=tonumber(string.sub(payload,11,12))
           day=tonumber(string.sub(payload,14,15))
           hour=tonumber(string.sub(payload,17,18))
           minute=tonumber(string.sub(payload,20,21))
           second=tonumber(string.sub(payload,23,24))
           tt=tonumber(string.sub(payload,26,27))

           hour=hour+TZ    -- convert from UTC to local time
         
           if ((tt>1) and (tt<51)) or ((tt==51) and (hour>1)) or ((tt==1) and (hour<2)) then
              hour=hour+1  -- daylight savings time currently in effect, add one hour
           end
         
           hour=hour%24
        end -- if string.sub(payload,39,47)=="UTC(NIST)" then
      end -- function
   ) -- end of on "receive" event handler

   -- on disconnect event handler           
   conn:on("disconnection", 
      function(conn,payload) 
         --print("Disconnected...")
         conn=nil
         payload=nil
      end -- function
   )  -- end of on "disconnecttion" event handler
end -- function getDayTime()

-- Execution starts here...
print("\ncontacting NIST server...")
getDayTime() -- contact the NIST daytime server for the current time and date
tmr.alarm(5,500,0,        -- after a half second...
   function()
     if year~=0 then
        print(string.format("%02d:%02d:%02d  %02d/%02d/%04d",hour,minute,second,month,day,year))
     else
        print("Unable to get time and date from the NIST server.")
     end
   end
)
 * 
 * 
 * /
 */

