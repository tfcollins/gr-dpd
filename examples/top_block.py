#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Sun Mar 20 16:23:25 2016
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from PyQt4 import Qt
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.ctrlport.monitor import *
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import dpd
import sys


class top_block(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Top Block")
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000

        ##################################################
        # Blocks
        ##################################################
        self.dpd_cic_moving_average_cc_0 = dpd.cic_moving_average_cc(4)
        self.blocks_vector_source_x_0 = blocks.vector_source_c((1,2,3,4,5,6,7,8,9,10), True, 1, [])
        self.blocks_null_sink_0_0 = blocks.null_sink(gr.sizeof_gr_complex*1)
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_gr_complex*1)
        self.blocks_moving_average_xx_0 = blocks.moving_average_cc(4, 1, 4000)
        self.blocks_head_0 = blocks.head(gr.sizeof_gr_complex*1, 2**30)
        self.blocks_ctrlport_probe2_c_0_0 = blocks.ctrlport_probe2_c("samples", "MA", 1024, gr.DISPTIME)
        self.blocks_ctrlport_probe2_c_0 = blocks.ctrlport_probe2_c("samples", "CIC", 1024, gr.DISPTIME)
        self.blocks_ctrlport_monitor_performance_0 = not True or monitor("gr-perf-monitorx")
        self.blocks_ctrlport_monitor_0 = not True or monitor()

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_head_0, 0), (self.blocks_null_sink_0_0, 0))    
        self.connect((self.blocks_moving_average_xx_0, 0), (self.blocks_ctrlport_probe2_c_0_0, 0))    
        self.connect((self.blocks_moving_average_xx_0, 0), (self.blocks_head_0, 0))    
        self.connect((self.blocks_vector_source_x_0, 0), (self.blocks_moving_average_xx_0, 0))    
        self.connect((self.blocks_vector_source_x_0, 0), (self.dpd_cic_moving_average_cc_0, 0))    
        self.connect((self.dpd_cic_moving_average_cc_0, 0), (self.blocks_ctrlport_probe2_c_0, 0))    
        self.connect((self.dpd_cic_moving_average_cc_0, 0), (self.blocks_null_sink_0, 0))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()


    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate


def main(top_block_cls=top_block, options=None):

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    if True:
        if True:
            (tb.blocks_ctrlport_monitor_0).start()
    else:
        sys.stderr.write("Monitor '{0}' does not have an enable ('en') parameter.".format("tb.blocks_ctrlport_monitor_0"))
    if True:
        if True:
            (tb.blocks_ctrlport_monitor_performance_0).start()
    else:
        sys.stderr.write("Monitor '{0}' does not have an enable ('en') parameter.".format("tb.blocks_ctrlport_monitor_performance_0"))
    qapp.exec_()


if __name__ == '__main__':
    main()
