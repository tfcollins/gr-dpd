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
#include "cyclic_prefixer_vcvc_impl.h"

namespace gr {
  namespace dpd {

    cyclic_prefixer_vcvc::sptr
    cyclic_prefixer_vcvc::make(int ofdm_sym_len, int cp_len)
    {
      return gnuradio::get_initial_sptr
        (new cyclic_prefixer_vcvc_impl(ofdm_sym_len, cp_len));
    }

    /*
     * The private constructor
     */
    cyclic_prefixer_vcvc_impl::cyclic_prefixer_vcvc_impl(int ofdm_sym_len, int cp_len)
      : gr::sync_block("cyclic_prefixer_vcvc",
              gr::io_signature::make(1, 1, ofdm_sym_len*sizeof(gr_complex)),
              gr::io_signature::make(1, 1, (cp_len+ofdm_sym_len)*sizeof(gr_complex))),
	d_cp_len(cp_len),
	d_ofdm_sym_len(ofdm_sym_len)
    {}

    /*
     * Our virtual destructor.
     */
    cyclic_prefixer_vcvc_impl::~cyclic_prefixer_vcvc_impl()
    {
    }

    int
    cyclic_prefixer_vcvc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

	// index helpers
	int items = 0;
	int cp_start_index = d_ofdm_sym_len - d_cp_len;

	// datatype sizes
	size_t cp_size = sizeof(gr_complex)*d_cp_len;
	size_t ofdm_data_size = sizeof(gr_complex)*d_ofdm_sym_len;

	for (int vec=0; vec<noutput_items; vec++)
	{
	  // add prefix
	  memcpy( out+d_ofdm_sym_len, in+d_ofdm_sym_len+cp_start_index, cp_size);

	  // add ofdm symbol
	  memcpy( out+d_ofdm_sym_len+cp_start_index, in+d_ofdm_sym_len, ofdm_data_size);

	  items =+ d_ofdm_sym_len;
	}

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dpd */
} /* namespace gr */

