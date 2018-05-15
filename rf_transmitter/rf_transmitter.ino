/**
 * @Author Tapadar S
 * @Date May 15, 2018
 * @Setup Aurdino Mega, 3.3 RF Transmitter
 * @Version Aurdino 1.8.4
 * @Purpose The RF transmitter transmits random text messages at interval
 * @Deploy This code to be deployed in Aurdino Mega that acts as transmitter.
 * 
 */
#include <RadioHead.h>
#include <radio_config_Si4460.h>
#include <RHCRC.h>
#include <RHDatagram.h>
#include <RHGenericDriver.h>
#include <RHGenericSPI.h>
#include <RHHardwareSPI.h>
#include <RHMesh.h>
#include <RHNRFSPIDriver.h>
#include <RHReliableDatagram.h>
#include <RHRouter.h>
#include <RHSoftwareSPI.h>
#include <RHSPIDriver.h>
#include <RHTcpProtocol.h>
#include <RH_ASK.h>
#include <RH_NRF24.h>
#include <RH_NRF905.h>
#include <RH_RF22.h>
#include <RH_RF24.h>
#include <RH_RF69.h>
#include <RH_RF95.h>
#include <RH_Serial.h>
#include <RH_TCP.h>

RH_ASK driver;
int i = 0;
const char *msg = "Hello World!";

void setup()
{
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{ 

    if(i==4) { i=0;}
    if(i==0){ msg = "Apple"; }
    else if(i==1){ msg = "Hello"; }
    else if(i==2){ msg = "Scot"; }
    else if(i==3){ msg = "Tiger"; }
    i++;
    
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println(msg);
    delay(1000);
}
