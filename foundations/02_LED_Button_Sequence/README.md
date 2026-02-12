# LED Button Sequence – ESP32

📘 **Languages**
- [English](#english)
- [Eesti](#eesti)
- [Italiano](#italiano)

---

## English

This project demonstrates how to control three LEDs using a single push button
on an ESP32 microcontroller.

Each button press turns on the next LED in the sequence.
After the last LED, the sequence restarts from the first one.

### Features
- ESP32 microcontroller
- Arduino framework
- PlatformIO build system
- 3 GPIO outputs driving LEDs
- 1 GPIO input with internal pull-up resistor
- Falling-edge detection on button press
- Simple debounce handling

### Hardware
- ESP32 development board
- Breadboard
- 3 × LEDs
- 3 × resistors (220–330 Ω)
- 1 × push button
- Jumper wires

### Wiring

| Component | GPIO | Notes |
|---------|------|------|
| LED 1 | GPIO21 | Series resistor |
| LED 2 | GPIO22 | Series resistor |
| LED 3 | GPIO23 | Series resistor |
| Button | GPIO19 | INPUT_PULLUP, connected to GND |

### Wiring overview

![Green LED](/02_exercises/ESP32/Arduino/02_LED_Button_Sequence/led_green_on.jpeg)

![LED red on](led_red_on.jpeg)

### Pin detail

![Wiring detail](wiring_detail.jpeg)

### Software

- IDE: Visual Studio Code
- Build system: PlatformIO
- Framework: Arduino (ESP32)

PlatformIO is used instead of the standard Arduino IDE to provide a more
professional and scalable development environment, including proper project
structure, dependency management, and build control.

### Design choices

#### Button input configuration

The push button is connected directly between the GPIO pin and GND,
without using an external pull-up or pull-down resistor.

The ESP32 internal pull-up resistor is enabled in software using:

```cpp
pinMode(BTN, INPUT_PULLUP);
```

With this configuration:

Button released → HIGH

Button pressed → LOW

A falling edge (HIGH → LOW) is detected to advance the LED sequence.

This approach:

Reduces external components

Simplifies wiring

Is suitable for most push-button input use cases

How it works

All LEDs start OFF

Each button press:

Turns OFF all LEDs

Turns ON the next LED in sequence

After the last LED, the sequence restarts from the first one

Eesti

See projekt näitab, kuidas juhtida kolme LED-i ühe nupu abil ESP32
mikrokontrolleril.

Iga nupuvajutus lülitab sisse järgmise LED-i.
Pärast viimast LED-i algab järjestus uuesti.

Omadused

ESP32 mikrokontroller

Arduino raamistik

PlatformIO ehitussüsteem

3 LED väljundit

1 nupu sisend sisemise pull-up takistiga

Nupu vajutuse tuvastamine (langev serv)

Lihtne debounce-loogika

Ühendused
Komponent	GPIO	Märkus
LED 1	GPIO21	Takisti jadamisi
LED 2	GPIO22	Takisti jadamisi
LED 3	GPIO23	Takisti jadamisi
Nupp	GPIO19	INPUT_PULLUP, ühendatud GND-ga
Tarkvara

IDE: Visual Studio Code

Ehitussüsteem: PlatformIO

Raamistik: Arduino (ESP32)

PlatformIO võimaldab professionaalset projektistruktuuri ning paremat
ehituse ja sõltuvuste haldamist võrreldes Arduino IDE-ga.

Disainivalikud
Nupu ühendamine

Nupp on ühendatud otse GPIO ja GND vahele, ilma välise takistita.

ESP32 sisemine pull-up takisti aktiveeritakse tarkvaras käsuga:

```cpp
pinMode(BTN, INPUT_PULLUP);
```
Nupp vabastatud → HIGH

Nupp vajutatud → LOW

Nupu vajutuse tuvastamiseks kasutatakse langevat serva (HIGH → LOW).

Italiano

Questo progetto mostra come controllare tre LED utilizzando un solo pulsante
su un microcontrollore ESP32.

Ogni pressione del pulsante accende il LED successivo in sequenza.
Dopo l’ultimo LED, la sequenza riparte dal primo.

Caratteristiche

Microcontrollore ESP32

Framework Arduino

Sistema di build PlatformIO

3 uscite GPIO per LED

1 ingresso GPIO con pull-up interno

Rilevamento del fronte di discesa

Debounce semplice

Collegamenti
Componente	GPIO	Note
LED 1	GPIO21	Resistenza in serie
LED 2	GPIO22	Resistenza in serie
LED 3	GPIO23	Resistenza in serie
Pulsante	GPIO19	INPUT_PULLUP, collegato a GND
Software

IDE: Visual Studio Code

Sistema di build: PlatformIO

Framework: Arduino (ESP32)

PlatformIO è stato scelto al posto dell’Arduino IDE per garantire
una struttura di progetto più professionale e scalabile.

Scelte progettuali
Gestione del pulsante

Il pulsante è collegato direttamente tra il pin GPIO e GND,
senza l’utilizzo di una resistenza esterna.

La resistenza di pull-up interna dell’ESP32 viene abilitata via software
tramite l’istruzione:

```cpp
pinMode(BTN, INPUT_PULLUP);
```

Con questa configurazione:

Pulsante rilasciato → HIGH

Pulsante premuto → LOW

Il fronte di discesa (HIGH → LOW) viene utilizzato per avanzare
nella sequenza dei LED.

Questa soluzione:

Riduce il numero di componenti esterni

Semplifica il cablaggio

È adatta alla maggior parte dei casi d’uso
