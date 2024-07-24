#include "WiFi.h" 
#include <HTTPClient.h>
const char* ssid = "MYLAPTOP";  // Wifi name
const char* password = "Akhil150";  // Wifi password
const char* uid = "sabareesh";//Account username
const char* passwrd = "2901"; //Account username
String status;
// Google script ID and required credentials
String GOOGLE_SCRIPT_ID = "AKfycby2o6JdU5Y9mMf00nz2MypGCpqfFoVEH4w9N5U-1zaC5T6oUE9jrM5W7CDZtYQe-Avs1Q";//Replace with deployment id
void setup () {
  pinMode(2,OUTPUT);
  delay (1000);
  Serial.begin(115200);
  delay(1000);
  Serial.println ();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush() ;
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay (500);
    Serial.print(".");
  }
}
 
void loop () {
  if (WiFi.status () == WL_CONNECTED) { 
  String url_init = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"; 
  String url_fin = url_init+"uid="+String (uid) + "&passwrd=" + String(passwrd);
  getdata(url_fin);
  //String status=http.getString();
  if(status=="Verified")
  {
    balanc("1");
    crediting("1");
    debiting("2");  
  }
  while(1);
  
  }
}
void crediting(String crdt)
{
String url_init = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"; 
String url_fin = url_init+"crdt="+String (crdt);
getdata(url_fin);

}
void debiting(String dbt)
{
String url_init = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"; 
String url_fin = url_init+"dbt="+String (dbt);
getdata(url_fin);
}
void balanc(String balance){
String url_init = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"; 
String url_fin = url_init+"balance="+String(balance);
getdata(url_fin);

}
void getdata(String pd)
{
 Serial.print ("Making request");
    HTTPClient http;
    http.begin (pd.c_str () );
    http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET () ;
     Serial.print ("HTTP Status Code: ");
    if(httpCode>0){
       Serial.println (httpCode);  
    }else{
      Serial.println("Error on HTTP request");   
    }
    String str=http.getString();
    if(str=="Verified")
    {
      status="Verified";
    }
    else if(str=="Invalid username or password!")
    {
      status="Invalid username or password!";
    }
    Serial.println(str);
    delay(500);
    http.end () ;

}