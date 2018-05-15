#include 
char *controller;


void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  vw_set_ptt_inverted(true); //
  vw_set_tx_pin(12);
  vw_setup(4000);// speed of data transfer Kbps

}

void loop() {
  // put your main code here, to run repeatedly:
  controller="1" ;
  vw_send((uint8_t *)controller, strlen(controller));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13,1);
  delay(2000);
  controller="0" ;
  vw_send((uint8_t *)controller, strlen(controller));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13,0);
  delay(2000);
}
