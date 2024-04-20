This project aims to use an ESP32 with Home assistant and the LD2450 millimeter wave sensor. It is based on the work of Screek and has been improved in three areas:
- I doubled the number of detection zones. There are 6 of them.
- I added two more exclusion zones. There are 3 of them.
- I also reduced the amount of information that the ESP32 sends to Home Assistant by allowing the real-time display of targets to be deactivated, thus avoiding overloading the history.
- You can define an angle if you have not placed the sensor flat against a wall
- The maximum detection length has increased from 6 to 8 meters and can now start at - 0.5 meters
- The positioning of the zones no longer works with the same system. Before there was a minimum X and Y zone and a maximum X and Y zone. Now there is just an X and Y position with a length and width
- Each sensor entity now has the name of the room in which it is integrated. You must choose the name of this room manually. (entity_name: "Room")
- The chart is more interactive. Whether the target is displayed or not, when someone is in an area, it becomes more colorful.

<picture>
 <img alt="map 0°" src="https://forum.hacf.fr/uploads/default/original/3X/9/f/9f0e7d34a22281a5f8b7d2b3c38dd49ec131d3c6.gif">
</picture>  <br/><br/>
In the example above, <b>Zout1</b> is a fridge and triggering it could cause a false positive. <b>Zout2</b> and <b>3</b> are windows equipped with curtains. I added an automation in Home Assistant which only activates these two exclusion zones when the windows are open, thus preventing the curtains from being detected as a false positive due to the wind.
<br/><br/>
<b>Zone3</b>, straddling <b>Zone1</b> and <b>2</b>, is located on a door. It allows you to turn on the light in the room you arrive in before even entering, thus avoiding a delay of one second when switching on.
<br/><br/>
The light gray dotted area represents the approximate detection area of the sensor. Its pear-shaped pattern comes from the HLK datasheet. It allows us to understand that the optimal detection zone is 6 meters but that we can go a little further in practice.  <br/><br/>


<picture>
 <img alt="map 45°" src="https://forum.hacf.fr/uploads/default/original/3X/c/5/c5b53d535f0624cc30aa5af48a753b4861e7bcb1.gif">
</picture>
