# Laporan Internet of Things-ThingSpeak

## Anggota Kelompok

| No | Nama                   | NRP         |
|----|------------------------|-------------|
| 1  | Hanif Mawla Faizi | 5027241064  |
| 2  | Mohammad Abyan Ranuaji     | 5027241106 |

## Alat yang dibutuhkan
- ESP32
- Kabel Female-to-Female
- HC-SR04
- Lampu LED

## Langkah-langkah
1. Sambungkan pin seperti berikut:

    - HC-SR04 VCC → VIN pada ESP32
    - HC-SR04 GND → GND pada ESP32
    - HC-SR04 Trig → GPIO 5 pada ESP32
    - HC-SR04 Echo → GPIO 18 pada ESP32
    - Anoda LED (kaki panjang) → Resistor 220Ω → GPIO 19, 23, 22, 1, 3 pada ESP32
    - Katoda LED (kaki pendek) → GND pada ESP32

Sehingga tampilan dari ESP32 kit seperti berikut:

<img width="1599" height="879" alt="Image" src="https://github.com/user-attachments/assets/a1f96f75-93e8-42f6-8d32-f35ed1526e44" />

2. Setup ThingSpeak
    - Buka situs web ThingSpeak.com dan buat akun atau masuk.
    - Buat Channel baru dengan mengklik "New Channel".
    - Beri nama channel (misal: "Sensor Jarak ESP32").
    - Aktifkan Field 1 dan beri nama "Jarak (cm)".
    - Simpan channel, lalu buka tab "API Keys" untuk menyalin Channel ID dan Write API Key.

3.  Run kode (.ino) yang berada di repository ini sehingga outputnya dapat menjadi seperti foto berikut:

<img width="699" height="470" alt="Image" src="https://github.com/user-attachments/assets/8602815f-a93e-4f3d-87b8-a3e085acc706" />
