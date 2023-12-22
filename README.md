# EH5IOT-01 PROJEKT
## Indhold
* [Introduktion](#Introduktion)
* [Hardware](#Hardware)
* [API/Webhook](#APIWebhook)

## Introduktion
Dette IOT projekts mål er at lave et indeklima info system der kan give et hurtigt overblik over et rums luftkvalitet via brug af sensorer, samt give information om luftkvaliteten udenfor via et api kald. Den opsamlede data fra sensorer og api-kald, bruges til at lave et simpelt overblik over indeklimaet.

Et dårligt indeklima kan have en negativ impakt på folks helbred, derfor er det ønskværdigt at man hurtigt kan få et overblik og forbedre indeklimaet hvis nødvendigt.

Ved at have data på luftkvaliteten udenfor er det hurtigt at se eksempelvis om det vil hjælpe at åbne eller lukke et vindue i rummet.

Mulig udvidelse af projektet inkluderer logging af indeklima og webbaseret dashboard med mere dybdegående data.

## Hardware
* Particle Argon: IoT hardware platform
* SEN-GP2Y1014AU: Et optisk støv-sensor modul
* SEN-BME680: Et temperatur, lufttryks og luftfugtigheds sensor modul
* SEN-CCS811V1: Et luftkvalitets sensor modul

## API/Webhook
waqi.info - api findes [her](https://aqicn.org/api/).
