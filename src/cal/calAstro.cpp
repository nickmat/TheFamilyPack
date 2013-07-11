/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name:        src/cal/calAstro.cpp
 * Project:     Cal: A general purpose calendar library.
 * Purpose:     General astronomy functions.
 * Author:      Nick Matthews
 * Website:     http://thefamilypack.org
 * Created:     8th December 2013
 * RCS-ID:      $Id$
 * Copyright:   Copyright (c) 2013, Nick Matthews.
 * Licence:     GNU GPLv3
 *
 *  The Family Pack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The Family Pack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Family Pack.  If not, see <http://www.gnu.org/licenses/>.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "calAstro.h"
#include "calMath.h"
#include "calGregorian.h"

// CC3 p187
const double calMeanTropicalYear = 365.242189; // days

// CC3 p191
const double calSpring = 0.0; // degrees
const double calSummer = 90.0; 
const double calAutumn = 180.0; 
const double calWinter = 270.0;

//
double const calJ2000 = 2451545.5; // 1 Jan 2000 (G) plus 12 hours

namespace {

inline long DateDifference( long jdn1, long jdn2 ) { return jdn2 - jdn1; } 

// NOTE: 
// 1 Jan 2000 (G) = 2451545 (JDN)
// 1 Jan 1900 (G) = 2415021 (JDN)
// 1 Jan 1810 (G) = 2382149 (JDN)

// CC3 p177
double EphemerisCorrection( double moment )
{
    const double daypersec = 1.0 / 86400.0;
    long jdn = (long) moment;
    long year = calGregorianYearFromJdn( jdn );

    if( year <= 2019 ) {
        if( year >= 1988 ) {
            return daypersec * (double) ( year - 1933 );
        }
        if( year >= 1800 ) {
            double c = 
                ( 1.0 / 36525.0 ) 
                * (double) DateDifference( 2415021L, calGregorianToJdn( year, 7, 1 ) )
            ;
            double c2 = c * c;
            double c3 = c2 * c;
            double c4 = c3 * c;
            double c5 = c4 * c;
            double c6 = c5 * c;
            double c7 = c6 * c;
            if( year >= 1900 ) {
                return 
                    - 0.00002 + 0.000297 * c + 0.025184 * c2
                    - 0.181133 * c3 + 0.553040 * c4 - 0.861938 * c5
                    + 0.677066 * c6 - 0.212591 * c7
                ;
            }
            double c8 = c7 * c;
            double c9 = c8 * c;
            double c10 = c9 * c;
            return
                - 0.000009 + 0.003844 * c + 0.083563 * c2 + 0.865736 * c3
                + 4.867575 * c4 + 15.845535 * c5 + 31.332267 * c6
                + 38.291999 * c7 + 28.316289 * c8 + 11.636204 * c9
                + 2.0437994 * c10
            ;
        }
        if( year >= 1700 ) {
            double ya = (double) ( year - 1700 );
            double ya2 = ya * ya;
            double ya3 = ya2 * ya;
            return 
                daypersec * ( 8.118780842 - 0.005092142 * ya
                + 0.003336121 * ya2 - 0.0000266484 * ya3 )
            ;
        }
        if( year >= 1620 ) {
            double yb = (double) ( year - 1600 );
            double yb2 = yb * yb;
            return daypersec * ( 196.58333 - 4.0675 * yb + 0.0219167 * yb2 );
        }
    }
    double x = 0.5 +
        (double) DateDifference( 2382149L, calGregorianToJdn( year, 1, 1 ) );
    return daypersec * ( ( x * x ) / 41048480.0 - 15.0 );
}

// CC3 p179
double JulianCentries( double moment )
{
    double dynamictime = moment + EphemerisCorrection( moment );
    return ( 1.0 / 36525.0 ) * ( dynamictime - calJ2000 );
}

// CC3 p186
double ObliquityFromJC( double c )
{
    double c2 = c * c;
    double c3 = c2 * c;
    return 23.4392911 - 0.01300417 * c - 0.000000164 * c2 + 0.00000050361 * c3;
}

// CC3 p189
double AberrationFromJC( double c )
{
    return 0.000974 * cos( ( 177.63 + 35999.01848 * c ) * calPi / 180 ) - 0.005575;
}

// CC3 p189
double NutationFromJC( double c )
{
    double c2 = c * c;
    double A = 124.9 - 1934.134 * c + 0.002063 * c2;
    double B = 201.11 + 72001.5377 * c + 0.00057 * c2;
    return - 0.004778 * sin( A * calPi / 180 ) - 0.0003667 * sin( B * calPi / 180 );
}

} // namespace

// CC3 p183  moment: Moment in Universal Time.  Returns fraction of day
double calEquationOfTime( double moment )
{
    double c = JulianCentries( moment );
    double c2 = c * c;
    double c3 = c2 * c;
    double lambda = 280.46645 + 36000.76983 * c + 0.0003032 * c2;
    double anomaly = 357.52910 + 35999.050303 * c - 0.0001559 * c2 - 0.00000048 * c3;
    double eccentricity = 0.016708617 - 0.000042037 * c - 0.0000001236 * c2;
    double epsilon = ObliquityFromJC( c );
    double y = tan( calDegToRad( epsilon / 2 ) );
    y *= y;

    double equation = 
        ( 1.0 / ( 2 * calPi ) ) * (
        y * sin( 2 * lambda * calPi / 180 ) 
        - 2 * eccentricity * sin( calDegToRad( anomaly ) )
        + 4 * eccentricity * y * sin( calDegToRad( anomaly ) ) * cos( 2 * calDegToRad( lambda ) )
        - 0.5 * y * y * sin( 4 * lambda * calPi / 180 )
        - 1.25 * eccentricity * eccentricity * sin( 2 * calDegToRad( anomaly ) ) )
    ;
    double t1 = y * sin( 2 * lambda * calPi / 180 );
    double t2 = - 2 * eccentricity * sin( anomaly * calPi / 180 );
    double t3 = 4 * eccentricity * y * sin( anomaly * calPi / 180 ) * cos( 2 * lambda * calPi / 180 );
    double t4 = - 0.5 * y * y * sin( 4 * lambda * calPi / 180 );
    double t5 = - 1.25 * eccentricity * eccentricity * sin( 2 * anomaly * calPi / 180 );
    double equation2 = ( 1.0 / ( 2 * calPi ) ) * ( t1 + t2 + t3 + t4 + t5 );
    return calSignum( equation ) * wxMin( abs( equation ), 0.5 );
}

// CC3 p189
double calSolarLongtitude( double moment )
{
    struct Args {
        double x; double y; double z;
    } a[] = {
        { 403406, 270.54861, 0.9287892 },
        { 195207, 340.19128, 35999.1376958 },
        { 119433, 63.91854, 35999.4089666 },
        { 112392, 331.26220, 35998.7287385 },
        { 3891, 317.843, 71998.20261 },
        { 2819, 86.631, 71998.4403 },
        { 1721, 240.052, 36000.35726 },
        { 660, 310.26, 71997.4812 },
        { 350, 247.23, 32964.4678 },
        { 334, 260.87, -19.441 },
        { 314, 297.82, 445267.1117 },
        { 268, 343.14, 45036.884 },
        { 242, 166.79, 3.1008 },
        { 234, 81.53, 22518.4434 },
        { 158, 3.5, -19.9739 },
        { 132, 132.75, 65928.9345 },
        { 129, 182.95, 9038.0293 },
        { 114, 162.03, 3034.7684 },
        { 99, 29.8, 33718.148 },
        { 93, 266.4, 3034.448 },
        { 86, 249.2, -2280.773 },
        { 78, 157.6, 29929.992 },
        { 72, 257.8, 31556.493 },
        { 68, 185.1, 149.588 },
        { 64, 69.9, 9037.75 },
        { 46, 8, 107997.405 },
        { 38, 197.1, -4444.176 },
        { 37, 250.4, 151.771 },
        { 32, 65.3, 67555.316 },
        { 29, 162.7, 31556.08 },
        { 28, 341.5, -4561.54 },
        { 27, 291.6, 107996.706 },
        { 27, 98.5, 1221.655 },
        { 25, 146.7, 62894.167 },
        { 24, 110, 31437.369 },
        { 21, 5.2, 14578.298 },
        { 21, 342.6, -31931.757 },
        { 20, 230.9, 34777.243 },
        { 18, 256.1, 1221.999 },
        { 17, 45.3, 62894.511 },
        { 14, 242.9, -4442.039 },
        { 13, 115.2, 107997.909 },
        { 13, 151.8, 119.066 },
        { 13, 285.3, 16859.071 },
        { 12, 53.3, -4.578 },
        { 10, 126.6, 26895.292 },
        { 10, 205.7, -39.127 },
        { 10, 85.9, 12297.536 },
        { 10, 146.1, 90073.778 }
    };
    size_t size = sizeof( a ) / sizeof( Args );
    double c = JulianCentries( moment );
    double sum = 0.0;
    for( size_t i = 0 ; i < size ; i++ ) {
        sum += a[i].x * sin( calDegToRad( a[i].y + a[i].z * c ) );
    }
    double lambda = 282.7771834 + 36000.76953744 * c + 0.000005729577951308232 * sum;

    return calMod( lambda + AberrationFromJC( c ) + NutationFromJC( c ), 360 );
}

// CC3 p193
double calEstimatePriorSolarLongitude( double lambda, double moment )
{
    double rate = calMeanTropicalYear / 360;
    double tau = 
        moment - rate * calMod( calSolarLongtitude( moment ) - lambda, 360 );
    double delta = calMod( calSolarLongtitude( tau ) - lambda + 180, 360 ) - 180;
    return wxMin( moment, tau - rate * delta );
}

// End of src/cal/calAstro.cpp
