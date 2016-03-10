/* -*- c++ -*- */

#define DPD_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "dpd_swig_doc.i"

%{
#include "dpd/add_guardbands_vcvc.h"
#include "dpd/read_tag_from_stream_cc.h"
%}


%include "dpd/add_guardbands_vcvc.h"
GR_SWIG_BLOCK_MAGIC2(dpd, add_guardbands_vcvc);
%include "dpd/read_tag_from_stream_cc.h"
GR_SWIG_BLOCK_MAGIC2(dpd, read_tag_from_stream_cc);
