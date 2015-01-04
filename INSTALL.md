Prepare raspbian minimal install:
apt-get update
apt-get install xorg libfltk1.3 libxml++2.6-2

For remote testing:
apt-get install x11vnc

run OmmiKomm:
xinit /path/to/ommikomm

Compile:
apt-get install g++ make pkg-config libfltk1.3-dev libxml++2.6-dev
git clone https://github.com/Mik-/ommikomm.git
./configure
make
[sudo] make install
