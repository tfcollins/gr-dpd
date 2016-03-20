#!/usr/bin/env python2
# -*- coding: utf-8 -*-
# 
# Copyright 2016 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import dpd_swig as dpd
import time
import numpy

samples_to_process = 2**30
one_million = 1000000

class qa_cic_moving_average_cc (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_numerics (self):
	taps = 16
	max_samples = 2**18
	cic = dpd.cic_moving_average_cc(taps)
	ma = blocks.moving_average_cc(taps,1,max_samples)
	samples = numpy.random.normal(0, 0.1, 1024)+1j*numpy.random.normal(0, 0.1, 1024)
	samples = samples.tolist()

	src = blocks.vector_source_c(samples, True, 1, [])
	head = blocks.head(gr.sizeof_gr_complex*1, max_samples)
	dst_cic = blocks.vector_sink_c ()
	dst_ma = blocks.vector_sink_c ()
	# Connect
        self.tb.connect (src, head)
        self.tb.connect (head, cic)
        self.tb.connect (head, ma)
        self.tb.connect (ma, dst_ma)
        self.tb.connect (cic, dst_cic)
        # set up fg
        self.tb.run()
	result_data_cic = dst_cic.data()
	result_data_ma = dst_ma.data()
	# evaluate
        self.assertFloatTuplesAlmostEqual(result_data_cic, result_data_ma, 3)

    def test_001_t (self):
	taps = 16
	cic = dpd.cic_moving_average_cc(taps)
	samples = range(16)
	src = blocks.vector_source_c(samples, True, 1, [])
	head = blocks.head(gr.sizeof_gr_complex*1, samples_to_process)
	dst = blocks.null_sink(gr.sizeof_gr_complex*1)
	# Connect
        self.tb.connect (src, cic)
        self.tb.connect (cic, head)
        self.tb.connect (head, dst)
        # set up fg
	times = []
	for k in range(5):
		s = time.time()
        	self.tb.start()
        	self.tb.wait()
		times.append(time.time() - s)
	print "CIC- Throughput: "+str( (samples_to_process/one_million)/numpy.mean(times) )+" MS/s"

    def test_002_t (self):
	taps = 16
	ma = blocks.moving_average_cc(taps,1,4000)
	samples = range(16)
	src = blocks.vector_source_c(samples, True, 1, [])
	head = blocks.head(gr.sizeof_gr_complex*1, samples_to_process)
	dst = blocks.null_sink(gr.sizeof_gr_complex*1)
	# Connect
        self.tb.connect (src, ma)
        self.tb.connect (ma, head)
        self.tb.connect (head, dst)
        # set up fg
	times = []
	for k in range(5):
		s = time.time()
        	self.tb.start()
        	self.tb.wait()
		times.append(time.time() - s)
	print "MA - Throughput: "+str( (samples_to_process/one_million)/numpy.mean(times) )+" MS/s"


if __name__ == '__main__':
    gr_unittest.run(qa_cic_moving_average_cc, "qa_cic_moving_average_cc.xml")
