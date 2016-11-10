#pragma once

#include <fastuidraw/text/glyph_selector.hpp>
#include <fastuidraw/text/glyph_cache.hpp>
#include <fastuidraw/text/font.hpp>
#include <fastuidraw/painter/painter.hpp>

#include "ostream_utility.hpp"
#include "PainterWidget.hpp"
#include "simple_time.hpp"

using namespace fastuidraw;

class CellSharedState:boost::noncopyable
{
public:
  CellSharedState(void):
    m_draw_text(true),
    m_draw_image(true),
    m_rotating(false),
    m_stroke_width(10.0f),
    m_pause(false),
    m_anti_alias_stroking(true),
    m_cells_drawn(0)
  {}

  bool m_draw_text;
  bool m_draw_image;
  bool m_rotating;
  Path m_path;
  float m_stroke_width;
  bool m_pause;
  bool m_anti_alias_stroking;

  int m_cells_drawn;
};

class CellParams
{
public:
  reference_counted_ptr<GlyphSelector> m_glyph_selector;
  reference_counted_ptr<const FontBase> m_font;
  PainterPackedValue<PainterBrush> m_background_brush;
  PainterPackedValue<PainterBrush> m_image_brush;
  PainterPackedValue<PainterBrush> m_text_brush;
  PainterPackedValue<PainterBrush> m_line_brush;
  std::string m_text;
  std::string m_image_name;
  vec2 m_pixels_per_ms;
  int m_degrees_per_s;
  GlyphRender m_text_render;
  float m_pixel_size;
  vec2 m_size;
  vec2 m_image_size;
  ivec2 m_table_pos;
  bool m_timer_based_animation;
  CellSharedState *m_state;
};

class Cell:public PainterWidget
{
public:
  Cell(PainterWidget *p, const CellParams &params);
  ~Cell() {}

protected:

  virtual
  void
  paint_pre_children(const reference_counted_ptr<Painter> &painter);

  virtual
  void
  pre_paint(void);

private:

  bool m_first_frame;
  simple_time m_time;
  int m_thousandths_degrees_rotation;
  int m_thousandths_degrees_cell_rotation;

  vec2 m_table_pos;
  vec2 m_image_size;

  vec2 m_pixels_per_ms;
  int m_degrees_per_s;

  PainterPackedValue<PainterBrush> m_background_brush;
  PainterPackedValue<PainterBrush> m_image_brush;
  PainterPackedValue<PainterBrush> m_text_brush;
  PainterPackedValue<PainterBrush> m_line_brush;

  vec2 m_item_location;
  float m_item_rotation;
  PainterAttributeData m_text;
  CellSharedState *m_shared_state;
  bool m_timer_based_animation;
};
