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

#ifndef INCLUDED_DPD_READ_TAG_FROM_STREAM_CC_IMPL_H
#define INCLUDED_DPD_READ_TAG_FROM_STREAM_CC_IMPL_H

#include <dpd/read_tag_from_stream_cc.h>

namespace gr {
  namespace dpd {

    class read_tag_from_stream_cc_impl : public read_tag_from_stream_cc
    {
     private:
      // Nothing to declare in this block.

     public:
      read_tag_from_stream_cc_impl();
      ~read_tag_from_stream_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace dpd
} // namespace gr

#endif /* INCLUDED_DPD_READ_TAG_FROM_STREAM_CC_IMPL_H */

