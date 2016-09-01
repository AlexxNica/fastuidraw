/*!
 * \file ScaleTranslate.hpp
 * \brief file ScaleTranslate.hpp
 *
 * Adapted from: WRATHScaleTranslate.hpp of WRATH:
 *
 * Copyright 2013 by Nomovok Ltd.
 * Contact: info@nomovok.com
 * This Source Code Form is subject to the
 * terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with
 * this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * \author Kevin Rogovin <kevin.rogovin@nomovok.com>
 * \author Kevin Rogovin <kevin.rogovin@intel.com>
 *
 */


#pragma once

#include <cstdlib>
#include <math.h>
#include "vec2.hpp"


/*! \addtogroup Utility
 * @{
 */

/*!\class ScaleTranslate
  A ScaleTranslate represents the composition
  of a scaling and a translation, i.e.
  \f[ f(x,y) = (sx,sy) + (A,B) \f]
  where \f$ s \f$ =scale() and \f$ (A,B) \f$ =translation().
 */
class ScaleTranslate
{
public:
  /*!\fn ScaleTranslate(const vecN<T, 2>&, T)
    Ctor. Initialize a ScaleTranslate from a
    scaling factor and translation
    \param tr translation to use
    \param s scaling factor to apply to both x-axis and y-axis,
             _absolute_ value is stored, i.e. the sign of s
             is ignored
   */
  ScaleTranslate(const vec2 &tr, double s=double(1)):
    m_scale(fabs(s)),
    m_translation(tr)
  {}

  /*!\fn ScaleTranslate(T)
    Ctor. Initialize a ScaleTranslate from a
    scaling factor
    \param s scaling factor to apply to both x-axis and y-axis,
             _absolute_ value is stored, i.e. the sign of s
             is ignored
   */
  ScaleTranslate(double s = double(1)):
    m_scale(fabs(s))
  {
    m_translation.m_x = double(0);
    m_translation.m_y = double(0);
  }

  /*!\fn ScaleTranslate inverse(void) const
    Returns the inverse transformation to this.
   */
  ScaleTranslate
  inverse(void) const
  {
    ScaleTranslate r;

    r.m_scale = double(1) / m_scale;
    r.m_translation =  m_translation * (-r.m_scale);

    return r;
  }

  /*!\fn const vecN<T, 2>& translation(void) const
    Returns the translation of this
    ScaleTranslate.
   */
  const vec2&
  translation(void) const
  {
    return m_translation;
  }

  /*!\fn ScaleTranslate& translation(const vecN<T, 2>&)
    Sets the translation of this.
    \param tr value to set translation to.
   */
  ScaleTranslate&
  translation(const vec2 &tr)
  {
    m_translation=tr;
    return *this;
  }

  /*!\fn ScaleTranslate& translation_x(T)
    Sets the x-coordinate of the translation of this.
    \param x value to set translation to.
   */
  ScaleTranslate&
  translation_x(double x)
  {
    m_translation.m_x = x;
    return *this;
  }

  /*!\fn ScaleTranslate& translation_y(T)
    Sets the y-coordinate of the translation of this.
    \param y value to set translation to.
   */
  ScaleTranslate&
  translation_ry(double y)
  {
    m_translation.m_y = y;
    return *this;
  }

  /*!\fn T scale(void) const
    Returns the scale of this.
    Scaling factor is _NEVER_
    negative.
   */
  double
  scale(void) const
  {
    return m_scale;
  }

  /*!\fn ScaleTranslate& scale(T)
    Sets the scale of this.
    If a negative value is passed,
    it's absolute value is used.
    \param s value to set scale to.
   */
  ScaleTranslate&
  scale(double s)
  {
    m_scale=fabs(s);
    return *this;
  }

  /*!\fn vecN<T, 2> apply_to_point
    Returns the value of applying the transformation to a point.
    \param pt point to apply the transformation to.
   */
  vec2
  apply_to_point(const vec2 &pt) const
  {
    return pt * scale() + translation();
  }

  /*!\fn vecN<T, 2> apply_inverse_to_point
    Returns the value of applying the inverse of the
    transformation to a point.
    \param pt point to apply the transformation to.
   */
  vec2
  apply_inverse_to_point(const vec2 &pt) const
  {
    double inv_scale;
    inv_scale = double(1) / scale();
    return (pt - translation()) * inv_scale;
  }

private:
  double m_scale;
  vec2 m_translation;
};

/*!\fn operator*(const ScaleTranslate&, const ScaleTranslate&)
  Compose two ScaleTranslate so that:
  a*b.apply_to_point(p) "=" a.apply_to_point( b.apply_to_point(p)).
  \param a left hand side of composition
  \param b right hand side of composition
 */
inline
ScaleTranslate
operator*(const ScaleTranslate &a, const ScaleTranslate &b)
{
  ScaleTranslate c;

  //
  // c(p)= a( b(p) )
  //     = a.translation + a.scale*( b.scale*p + b.translation )
  //     = (a.translate + a.scale*b.translation) + (a.scale*b.scle)*p
  //
  //thus:
  //
  // c.scale=a.scale*b.scale
  // c.translation= a.apply_to_point(b.translation)
  c.scale( a.scale() * b.scale());
  c.translation( a.apply_to_point(b.translation()) );

  return c;
}