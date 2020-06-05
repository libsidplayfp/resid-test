# resid-test
A tool to perform comparison between reSID/reSIDfp and the transistor level emulation.



# Writing tests
-------------
The syntax for writing tests is fairly simple. Each line contains a command that is executed sequentially, some commands requires one ore more parameters separated by comma. Tha available commands are the following:

* check, \<register>: set the SID register to compare from now on, 0x1b for OSC3 and 0x1c for ENV3. The default is 0x1c.

* write, \<register>, \<value>: write value to SID register. Values and registers must be specified in c hex format.

* run, \<cycles>: run the emulation for specified number of cycles.

* end: end test

Lines starting with a pound (#) and empty lines are ignored.



#License

resid-test is distributed under GPLv2 license with the exception of perfect6581 which is distributed under MIT license.

-----------------------------------------------------------------------------

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

