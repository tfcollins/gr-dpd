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
#include "read_tag_from_stream_cc_impl.h"

namespace gr {
  namespace dpd {

    read_tag_from_stream_cc::sptr
    read_tag_from_stream_cc::make()
    {
      return gnuradio::get_initial_sptr
        (new read_tag_from_stream_cc_impl());
    }

    /*
     * The private constructor
     */
    read_tag_from_stream_cc_impl::read_tag_from_stream_cc_impl()
      : gr::sync_block("read_tag_from_stream_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      // Optional but good to set
      set_tag_propagation_policy(TPP_ONE_TO_ONE);
    }

    /*
     * Our virtual destructor.
     */
    read_tag_from_stream_cc_impl::~read_tag_from_stream_cc_impl()
    {
    }

    int
    read_tag_from_stream_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {

      // Copy all stream data to output, since we only care about tags
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
	    // Copy data
	    memcpy(out, in, noutput_items * sizeof(gr_complex));

      // Get number of samples consumed since the beginnging of time by this block
      const uint64_t nread = this->nitems_read(0);

      // Setup something to hold tags
      std::vector<gr::tag_t> tags;
      std::vector<gr::tag_t> tags2;

      // Tags contain up to 3 things
      // 1. key: which can be used to identify a certain tag
      // 2. value: actual data in the tag of type pmt
      // 3. (Optional) source ID: identify the origin of this specific tag

      // Read stream tags
      for (int i=0; i<noutput_items; i++)
      {
        // Get tags in stream
        // "get_tags_in_range" requires values relative to all received data, not just this block call
        // Function Format: Tag container, port, start position, end position, Optional: Only find tags with certain key
        get_tags_in_range(tags, 0, nread + i, nread + i + 1);

        // Same call as above with window function
        get_tags_in_window(tags2, 0, i, i + 1);

        // If we get a tag print what is inside of it
        if (tags.size())
        {
          std::cout<<"Got A New TAGz!!!!\n";
          for (int k = 0; k<tags.size(); k++)
          {
            // Pull out tag info
            std::cout<<"SRCID: "<<pmt::symbol_to_string(tags[k].srcid)<<std::endl;
            std::cout<<"Key: "<<pmt::symbol_to_string(tags[k].key)<<std::endl;
            std::cout<<"Value: "<<pmt::symbol_to_string(tags[k].value)<<std::endl;
          }

        }

      }


      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dpd */
} /* namespace gr */
