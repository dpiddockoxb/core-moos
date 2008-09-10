///////////////////////////////////////////////////////////////////////////
//
//   MOOS - Mission Oriented Operating Suite
//
//   A suit of Applications and Libraries for Mobile Robotics Research
//   Copyright (C) 2001-2005 Massachusetts Institute of Technology and
//   Oxford University.
//
//   This software was written by Paul Newman at MIT 2001-2002 and Oxford
//   University 2003-2005. email: pnewman@robots.ox.ac.uk.
//
//   This file is part of a  MOOS Core Component.
//
//   This program is free software; you can redistribute it and/or
//   modify it under the terms of the GNU General Public License as
//   published by the Free Software Foundation; either version 2 of the
//   License, or (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//   General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//   02111-1307, USA.
//
//////////////////////////    END_GPL    //////////////////////////////////
/*! \file MOOSSkewFilter.h */

#ifndef __MOOSSkewFilter_h
#define __MOOSSkewFilter_h

#include <MOOSGenLib/MOOSGenLib.h>
#include <deque>

namespace MOOS
{
	class CConvexEnvelope
	{
	public:
		struct tPt
		{
			tPt() : x(0), y(0) {}
			tPt(double _x, double _y) : x(_x), y(_y) {}
			double x,y;
		};

		struct tSeg
		{
			double dfPeriod;
			double dfM, dfC;     // Slope and intersect
			tPt    p1, p2; // Anchor points through which line passes

			void DumpState()
			{
				MOOSTrace("Period=%0.6f,dfM=%0.6f,dfC=%0.6f\n", dfPeriod, dfM, dfC);
			}
		};


	public:

		CConvexEnvelope();

		void Reset();
		bool AddPoint(double x, double y);

		unsigned int GetNumSegs() const { return m_segs.size(); }

		bool GetLongestSeg(tSeg &seg) const;

		/// Removes all segments from the front which have
		/// x vals less than x_min.  Will not remove the longest
		/// segment
		void CropFrontBefore(double x_min);

		void DumpState();

	private:
		bool DeleteLastSeg();
		bool MergeLastSeg();

		void AppendSeg(const tSeg &seg);
		bool MakeSeg(tSeg &seg, const tPt &p1, const tPt &p2) const;
		bool GetLineParams(const tPt &p1, const tPt &p2, double &M, double &C) const;

	private:
		CConvexEnvelope(const CConvexEnvelope &v); // Not implemented
		void operator=(const CConvexEnvelope &v); // Not implemented

	private:
		std::deque<tSeg> m_segs;

		// Temporarily store first point for each pending segment
		bool m_bHaveInitPt;
		tPt  m_InitPt;

		unsigned int m_uiLongestSegID;
		double m_dfLongestSegLen;
	};


	class CMOOSSkewFilter
	{
	public:
		struct tSkewInfo
		{
			tSkewInfo() : m(0),c(0),envpred(0) {}
			double m, c;
			double envpred;
		};

	public:
		CMOOSSkewFilter();

		void   Reset();

		double Update(double dfTXtime, double dfRXtime, double dfTransportDelay, tSkewInfo *skewinfo=NULL);
		double GetSkew();

		void DumpState();

	private:
		CMOOSSkewFilter(const CMOOSSkewFilter &v); // Not implemented
		void  operator=(const CMOOSSkewFilter &v); // Not implemented

	private:
		double SmoothingFilter(double dfDT, double dfOldFilterVal, double dfNewMeas, double dfGradient) const;

	private:
		CConvexEnvelope m_env;
		double m_dfLastVal;
		double m_dfLastTime;

		unsigned int m_nMeas;
	};

}

#endif // __MOOSSkewFilter_h


