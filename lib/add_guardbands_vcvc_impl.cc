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
#include "add_guardbands_vcvc_impl.h"

namespace gr {
  namespace dpd {

    add_guardbands_vcvc::sptr
    add_guardbands_vcvc::make(int in_vlen, int out_vlen)
    {
      return gnuradio::get_initial_sptr
        (new add_guardbands_vcvc_impl(in_vlen, out_vlen));
    }

    /*
     * The private constructor
     */
    add_guardbands_vcvc_impl::add_guardbands_vcvc_impl(int in_vlen, int out_vlen)
      : gr::sync_block("add_guardbands_vcvc",
              gr::io_signature::make(1, 1, in_vlen*sizeof(gr_complex)),
              gr::io_signature::make(1, 1, out_vlen*sizeof(gr_complex))),
            d_in_vlen(in_vlen),
            d_out_vlen(out_vlen)
    {}

    /*
     * Our virtual destructor.
     */
    add_guardbands_vcvc_impl::~add_guardbands_vcvc_impl()
    {
    }

    int
    add_guardbands_vcvc_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];//d_in_vlen*noutput_items == nsamples
        gr_complex *out = (gr_complex *) output_items[0];

        int guardbands = (d_out_vlen - d_in_vlen)/2; // May not be an int :(

        // Vector Indexes
        int items_out = 0;
        int items_in = 0;

        for(int item=0; item<noutput_items; item++)
        {

          // Add zeros to front of vector
          for (int z=0; z<guardbands; z++)
            out[z+items_out] = gr_complex(0,0);

          // Add data to vector
          for (int y=0; y<d_in_vlen; y++)
            out[y+guardbands+items_out] = in[items_in+guardbands+y];

          // Add zeros to front of vector
          for (int x=0; x<guardbands; x++)
            out[x+guardbands+d_in_vlen+items_out] = gr_complex(0,0);

          // Increment vector indexing
          items_out += d_out_vlen;
          items_in  += d_in_vlen;

        }
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace dpd */
} /* namespace gr */
