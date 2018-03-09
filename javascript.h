#include "images.h"

String webSite, javaScript, XML;
float ESPval =75;

void buildJavascript() {
  javaScript = "<SCRIPT>\n";
  javaScript += "xmlHttp=createXmlHttpObject();\n";
  javaScript += "function createXmlHttpObject(){\n";
  javaScript += "  if(window.XMLHttpRequest){\n";
  javaScript += "    xmlHttp=new XMLHttpRequest();\n";
  javaScript += "  }else{\n";
  javaScript += "    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\n";
  javaScript += "  }\n";
  javaScript += "  return xmlHttp;\n";
  javaScript += "}\n";



  javaScript += "function gettingJSON(){\n";
  javaScript += "   $.getJSON(\"http://api.openweathermap.org/data/2.5/weather?zip=06032,us&APPID=a92d7e05177198c0431625461fb6b127\",function(json){\n";
  javaScript += "      var l = JSON.stringify(json);\n";
  javaScript += "      var dir = ['N','NNE','NE','ENE','E','ESE','SE','SSE','S','SSW','SW','WSW','W','WNW','NW','NNW','N']; \n";
  javaScript += "      var t = JSON.parse(l);\n";
  javaScript += "      var deg = t.wind.deg ;\n"; 
  javaScript += "      var w = t.weather[0].description;\n";
  javaScript += "      deg = deg%360; \n";
  javaScript += "      var index = Math.round(deg/22.5); \n";
  javaScript += "      var CompassDir = dir[index]; \n";
  javaScript += "      var icon = 'http://openweathermap.org/img/w/'+t.weather[0].icon+'.png';\n";
  javaScript += "      if (CompassDir =='undefined'){CompassDir = 'No Direct'};\n";
  javaScript += "      var s = 'Current weather for Farmington CT: <BR>';\n";
  javaScript += "      s += '<img src=\"' +icon+'\">'; \n";
  javaScript += "     s +='<span class =\"icontext\">' + w+'</span>';\n";
  javaScript += "      s += '<BR> Temp: '+ (((t.main.temp)-273.15)*9/5+32).toFixed(2)+'&#8457 &emsp;   Humidity:'+t.main.humidity +'%';\n";
  javaScript += "      s += '<BR> Wind: '+CompassDir+'&emsp;' + ((t.wind.speed)/1609.34*3600).toFixed(2)+'&nbsp; mile/hr ';\n";
  javaScript += "      document.getElementById('weatherforcast').innerHTML= s;\n";
  javaScript += "    });\n";
  javaScript += "}\n\n";

  javaScript += "function process(){\n";
  javaScript += "gettingJSON();";
  javaScript += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  javaScript += "    xmlHttp.onreadystatechange=function(){\n";
  javaScript += "      if(xmlHttp.readyState==4&&xmlHttp.status==200){\n";
  javaScript += "        xmlDoc=xmlHttp.responseXML;\n";
  javaScript += "        xmlmsg = xmlDoc.getElementsByTagName('response')[0].firstChild.nodeValue;\n";
  javaScript += "       if(parseInt(xmlmsg) != -1) {";
  javaScript += "        document.getElementById('Temp').innerHTML=xmlmsg;}\n";
  javaScript += "        xmlmsg = xmlmsg=xmlDoc.getElementsByTagName('target')[0].firstChild.nodeValue;\n";
  javaScript += "        xmlmsg = parseInt(xmlmsg);";
  javaScript += "        document.getElementById('visual').innerHTML=xmlmsg;\n";
  javaScript += "        xmlmsg = xmlDoc.getElementsByTagName('response')[2].firstChild.nodeValue;\n";
  javaScript += "       if(parseInt(xmlmsg) != -1) {";
  javaScript += "        document.getElementById('TempC').innerHTML=xmlmsg;}\n";
  javaScript += "        xmlmsg = xmlDoc.getElementsByTagName('response')[3].firstChild.nodeValue;\n";
  javaScript += "       if(parseInt(xmlmsg) != -1){ ";
  javaScript += "        document.getElementById('Humidity').innerHTML=xmlmsg+'%';}\n";
  javaScript += "        xmlmsg = xmlDoc.getElementsByTagName('truth')[1].firstChild.nodeValue;\n";
  javaScript += "       temp = 'error 101010';";
  javaScript += "        if(xmlmsg == 'true'){";
  javaScript += "            temp = 'ON';";
  javaScript += "            document.getElementById('button2').innerHTML='Deactivate Auto Control';\n";
  javaScript += "            document.getElementById('button').disabled = true;";
  javaScript += "}";
  javaScript += "        if(xmlmsg == 'false'){";
  javaScript += "            temp = 'OFF';";
  javaScript += "            document.getElementById('button2').innerHTML='Activate Auto Control';\n";
  javaScript += "            document.getElementById('button').disabled = false;";
  javaScript += "}";
  javaScript += "        xmlmsg = xmlDoc.getElementsByTagName('truth')[0].firstChild.nodeValue;\n";
  javaScript += "          document.getElementById('onoffindicator').innerHTML=xmlmsg;\n";
  javaScript += "          document.getElementById('button').value=xmlDoc.getElementsByTagName('truth')[0].firstChild.nodeValue;\n";
  javaScript += "      }\n";
  javaScript += "    }\n";
  javaScript += "    xmlHttp.open('PUT','xml',true);\n";
  javaScript += "    xmlHttp.send(null);\n";
  javaScript += "  }\n";
  javaScript += "  setTimeout('process()',2000);\n";
  javaScript += "}\n";
  
  javaScript += "function handleServerResponse(){\n";
  javaScript += " if(xmlHttp.readyState==4 && xmlHttp.status==200){\n";
  javaScript += "   xmlResponse=xmlHttp.responseXML;\n";
  javaScript += "   xmldoc = xmlResponse.getElementsByTagName('response');\n";
  javaScript += "   message = xmldoc[0].firstChild.nodeValue;\n";
  javaScript += "   document.getElementById('Temp').innerHTML=message;\n";
  javaScript += " }\n";
  javaScript += "}\n";
  
  javaScript += "function setVal(){\n";
  javaScript += "bv=document.getElementById('inputArea').value;\n";
  javaScript += "  if(parseInt(bv)<=90 && parseInt(bv)>=40&&(xmlHttp.readyState==0||xmlHttp.readyState==4)){\n";
  javaScript += "    xmlHttp.open('PUT','setesp?val='+bv,true);\n";
  javaScript += "    xmlHttp.send(null);\n";
  javaScript += "  }\n";
  javaScript += "}\n";

  javaScript += "function toggle(){\n";
  javaScript += "bv=document.getElementById('button').value;\n";
  javaScript += "if (bv=='true') bv='false';\n";
  javaScript += "else bv='true';\n";
  javaScript += "document.getElementById('button').value=true;\n";
  javaScript += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  javaScript += "    xmlHttp.open('PUT','setbuttonval?val='+bv,true);\n";
  javaScript += "    xmlHttp.send(null);\n";
  javaScript += "  }\n";
   javaScript += "}\n";


  javaScript += "function toggle2(){\n";
  javaScript += "bv=document.getElementById('button2').value;\n";
  javaScript += "if (bv=='true') { \n";
  javaScript += "bv='false';\n";
  javaScript += "}\n";
  javaScript += "else { \n";
  javaScript += "bv='true';\n";
  javaScript += "}\n";
  javaScript += "document.getElementById('button2').value=bv;\n";
  javaScript += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  javaScript += "    xmlHttp.open('PUT','setbuttonval2?val='+bv,true);\n";
  javaScript += "    xmlHttp.send(null);\n";
  javaScript += "  }\n";
  javaScript += "}\n";

  javaScript += "</SCRIPT>\n";
}

