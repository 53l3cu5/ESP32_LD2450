This project aims to use an ESP32 with Home assistant and the LD2450 millimeter wave sensor. It is based on the work of Screek and has been improved in three areas:
- I doubled the number of detection zones. There are 6 of them.
- I added two more exclusion zones. There are 3 of them.
- I also reduced the amount of information that the ESP32 sends to Home Assistant by allowing the real-time display of targets to be deactivated, thus avoiding overloading the history.

<picture>
 <img alt="map" src="https://forum.hacf.fr/uploads/default/original/3X/1/9/1907ece722a7cb17f05766ece8f75fd0125ae461.png">
</picture> </br>
In the example above, Zout1 is a fridge and triggering it could cause a false positive. Zout2 and 3 are windows equipped with curtains. I added an automation in Home Assistant which only activates these two exclusion zones when the windows are open, thus preventing the curtains from being detected as a false positive due to the wind.

Zone3, straddling Zone1 and 2, is located on a door. It allows you to turn on the light in the room you arrive in before even entering, thus avoiding a delay of one second when switching on.

The light gray dotted area represents the approximate detection area of the sensor. Its pear-shaped pattern comes from the HLK datasheet. It allows us to understand that the optimal detection zone is 6 meters but that we can go a little further in practice.
