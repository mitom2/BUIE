# BUIE
Simple SFML library containing <b>B</b>asic <b>U</b>ser <b>I</b>nterface <b>E</b>lements.
<br><br>
Currently implemented:
<ul>
  <li>Buttons</li>
  <li>Text fields</li>
</ul>
<br><br><br>
# SFML configuration
SFML is not included with this library. For proper functioning of this library, SFML is required. All files included in this library must have a direct access to SFML (#include <SFML/[moduleName].hpp> is used, an error will occur if proper module is not found this way). List of required SFML modules:<br>
<ul>
	<li>Graphics</li>
	<li>System</li>
	<li>Window</li>
</ul>