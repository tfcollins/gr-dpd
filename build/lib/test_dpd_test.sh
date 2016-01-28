#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/travis/Dropbox/PHD/WiFiUS/doa/gnuradio/gr-dpd/lib
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/travis/Dropbox/PHD/WiFiUS/doa/gnuradio/gr-dpd/build/lib:$PATH
export LD_LIBRARY_PATH=/home/travis/Dropbox/PHD/WiFiUS/doa/gnuradio/gr-dpd/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-dpd 
