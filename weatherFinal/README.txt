Project LWIP WeatherBase 

Het doel van het project is om de weerinformatie op te vragen aan een API via LWIP, het antwoord te verwerken en te displayen op het LCD.

Gebruikte bibliotheken & Compiler:

SW4Stm32 geïnstalleerd als plugin op eclipse
Lwip 1.5.0
Stm32 HAL (CubeMx)

Stappen:
1. stm32f7 discovery krijgt vanuit het programma een static IP 192.168.0.55, zorg dat poort 80 voor dit adres openstaat.
2. Verbind de stm32f7 met de netwerkkabel
3. Build en Run weatherFinal in Eclipse