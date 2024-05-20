// Import Library
#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Menginisialisasi variabel servo
Servo myservo;

// Inisialisasi pin LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
int SDA_pin = D1;
int SCL_pin = D2;

int myFunction(int, int);

void setup()
{
    // Setup pin servo dan set up cursor LCD
    myservo.attach(D4);
    Wire.begin(SDA_pin, SCL_pin);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    Wire.begin(SDA_pin, SCL_pin);
}

void loop()
{
    // Memulai progam dengan servo akan bergerak 180 derajat dan LCD melakukan print "TERBUKA"
    lcd.clear();          // Membersihkan LCD
    myservo.write(180);   // Menggerakan servo
    lcd.print("TERBUKA"); // Memunculkan teks di LCD
    // Lalu Delay selama 5 detik
    delay(5000);
    // Memulai progam dengan servo akan bergerak kembali 0 derajat dan LCD melakukan print "TERTUTUP"
    myservo.write(0);      // Menggerakan servo kembali
    lcd.print("TERTUTUP"); // Melakukan print teks "Tertutup"
    delay(5000);           // menunggu selama 5 detik untuk perintah selanjutnya

    // Scan alamat I2C
    byte error, address;
    int nDevices;
    Serial.println("Scanning...");
    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C terbaca pada alamat 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");

            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Ada error yang tidak diketahui pada alamat 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("Tidak ada satupun alamat I2C yang ditemukan\n");
    else
        Serial.println("selesai\n");
}

int myFunction(int x, int y)
{
    return x + y;
}