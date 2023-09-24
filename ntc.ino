#include <math.h>

#define NTC_input A1 //Bağlantılar tanımlandı.
#define led 8
 
float A = 1.009249522e-03, B = 2.378405444e-04, C = 2.019202697e-07; // Stein-Hart denkleminde bulunan sabit değerleri tanımladık.
 
int NTC_deger; //NTC değerini integer cinsinden tanımladık.
float Vout; // Vout değişkeni
float NTC_direnc, NTC_direnc_ln, Sicaklik; // Stein-Hart denkleminde kullanılacak olan değişkenler
 
 
void setup(){
 Serial.begin(9600);
 pinMode(led,OUTPUT);
 pinMode(A0,INPUT);
 //analogReference(EXTERNAL);
}
 
void loop() 
{
  
 NTC_deger = analogRead(NTC_input); //NTC değerini analog olarak okuyoruz.
 Serial.print(NTC_deger); 
 Vout = ( (NTC_deger * 5.0) / 1023.0 ); //Vout hesabı (Voltaj Bölücü Formülü)
 NTC_direnc = ( ( 5 * ( 10.0 / Vout ) ) - 10 ); //KiloOhm Cinsinden direnc değerinin hesabı
 NTC_direnc = NTC_direnc * 1000 ; // Ohm cinsinden direnç değeri
 NTC_direnc_ln = log(NTC_direnc); 
 /* Stein-Hart Denklemi: */
 Sicaklik = ( 1 / ( A + ( B * NTC_direnc_ln ) + ( C * NTC_direnc_ln * NTC_direnc_ln * NTC_direnc_ln ) ) ); //Sıcaklık değeri hesabı
 Sicaklik = Sicaklik - 273.15; //Sicaklik değerinin Celcius'a çevirimi 
 Serial.print("Sicaklik (Celcius) = "); //Bulunan değerlerin Seri Monitöre yazdırılması
 Serial.print(Sicaklik); 
 Serial.print("\t\t");
 Serial.print("NTC Direnc Degeri(Ohm) = ");
 Serial.print(NTC_direnc);
 Serial.print("\n\n");
 /*Sicaklik değeri 30 Derecenin üzerine çıkınca Arduino'ya bağlı olan LED yanacaktır.*/
 if(Sicaklik > 30){ 
 digitalWrite(led,HIGH);
 }
 else{
 digitalWrite(led,LOW);
 }
 delay(1000);
}
