/* -*- c++ -*- */
/*
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "cic_moving_average_cc_impl.h"

namespace gr {
  namespace dpd {

    cic_moving_average_cc::sptr
    cic_moving_average_cc::make(int window_len)
    {
      return gnuradio::get_initial_sptr
        (new cic_moving_average_cc_impl(window_len));
    }

    /*
     * The private constructor
     */
    cic_moving_average_cc_impl::cic_moving_average_cc_impl(int window_len)
      : gr::sync_block("cic_moving_average_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
      d_window_len(window_len)
    {
      // Set tap length
      set_history(window_len);
      // Set last output value
      d_last_output = gr_complex(0,0);
    }

    /*
     * Our virtual destructor.
     */
    cic_moving_average_cc_impl::~cic_moving_average_cc_impl()
    {
    }

    int
    cic_moving_average_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      for(int i=0; i<noutput_items; i++)
      {
        //output[n] = output[n-1] + input[n] - input[n-taps]
        if (i==0)
          out[i] = d_last_output + in[i+d_last_output] - in[i];
        else
          out[i] = out[i-1] + in[i+d_last_output] - in[i];
      }
      // Save stuff for next block call
      d_last_output = out[noutput_items-1];

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dpd */
} /* namespace gr */
