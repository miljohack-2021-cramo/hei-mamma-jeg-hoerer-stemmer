#include <UIPEthernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x2A, 0x8D };
byte server[] = {192, 168, 1, 165}; // Server IP
int data = 0;
const int microphonePin = A0;

void setup() {
  Serial.begin(9600);               // Used for serial debugging
  Serial.println("Starter");

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Ikke koblet til nett");
  } else {
    Serial.println("Koblet til nett");
  }

  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());

}
void loop() {
  //Serial.println("Program running...");

  data = 0;
  int antall = 70;
  for (int i = 0; i < antall; ++i) {
    int val = analogRead(microphonePin);
    data += val;
  }

  data = data / antall;

  senddata();
  //delay(500);
}
void senddata() {
  EthernetClient client;//(server, 80);
  delay(1000);                                    //Keeps the connection from freezing

  if (client.connect(server, 443)) {
    client.print("GET /api/iot/a/");
    client.print(data);
    client.println(" HTTP/1.1");
    client.println("Host: https://heimamma.com");
    client.println("Connection: close");
    client.println();

    Serial.print("Sendt dB: ");
    Serial.println(data);
  }

  else {
    Serial.println("Connection unsuccesful");
  }
  client.stop();
}
