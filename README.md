# EH5IOT-01 PROJEKT
## Indhold
* [Introduktion](#Introduktion)
* [Hardware](#Hardware)
* [API/Webhook](#API/Webhook)

## Introduktion
Dette IOT projekts mål er at lave et indeklima info system der kan give et hurtigt overblik over et rums luftkvalitet via brug af sensorer, samt give information om luftkvaliteten udenfor via et api kald. Den opsamlede data fra sensorer og api-kald, bruges til at lave et simpelt overblik over indeklimaet på hardwarens display.

Overbliket gives via et display der bruger både tekst/data samt en farve skala baseret på den der bruges på waqi.info. 
Et dårligt indeklima kan have en negativ impakt på folks helbred, derfor er det ønskværdigt at man hurtigt kan få et overblik og forbedre indeklimaet hvis nødvendigt. 

Ved at have data på luftkvaliteten udenfor er det hurtigt at se eksempelvis om det vil hjælpe at åbne eller lukke et vindue i rummet.

Mulig udvidelse af projektet inkluderer logging af indeklima og webbaseret dashboard med mere dybdegående data i stedet for det mere simpele overblik på selve iot hardwaren.

## Hardware
* En Particle Argon **minimum krav**
* En Honeywell HPMA115S0 Partikel Sensor **minimum krav**
* Et Display **minimum krav**
* En Adafruit CCS811 TVOC/C02 Sensor ***nice to have***
* En Adafruit Si7021 Fugtighed/Temperatur Sensor ***nice to have***

## API/Webhook
waqi.info - api findes [her](https://aqicn.org/api/).