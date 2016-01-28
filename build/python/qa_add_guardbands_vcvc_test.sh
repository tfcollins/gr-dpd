#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/travis/Dropbox/PHD/WiFiUS/doa/gnuradio/gr-dpd/python
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/travis/Dropbox/PHD/WiFiUS/doa/gnuradio/gr-dpd/build/python:$PATH
export LD_LIBRARY_PATH=/home/travis/Dropbox/PHD/WiFiUS/doa/gnuradio/gr-dpd/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/travis/Dropbox/PHD/WiFiUS/doa/gnuradio/gr-dpd/build/swig:$PYTHONPATH
/usr/bin/python2 /home/travis/Dropbox/PHD/WiFiUS/doa/gnuradio/gr-dpd/python/qa_add_guardbands_vcvc.py 
