
#include "Max7219.h"
#include "RestAPI.h"


const char* ssid = "your wifi ssid here";
const char* password = "your wifi password here";

const char* host = "crix-api-endpoint.upbit.com";
String upbit_xrp = "/v1/crix/candles/minutes/60?code=CRIX.UPBIT.KRW-XRP";


#define key_price "tradePrice"
#define key_opening "openingPrice"


Max7219 segment = Max7219();
RestAPI restAPI = RestAPI(ssid,password);

void setup()
{
    Serial.begin(115200);
    segment.initSegment();
    restAPI.connectWiFi();

}
void loop()
{
    if(restAPI.connectAvailable())
    {
        String response = restAPI.callAPISSL(host, upbit_xrp, 443);
        int price = restAPI.responseParser(response,key_price).toInt();
        int opening = restAPI.responseParser(response,key_opening).toInt();

        segment.displayNumber(price,4,1);
        segment.displayChangeRate(opening,price,8,5);
    }
    else
    {
        restAPI.connectWiFi();
    }
    
    delay(1000);
}