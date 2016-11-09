#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>

#include <fastuidraw/util/util.hpp>
#include <fastuidraw/painter/painter.hpp>
#include <fastuidraw/painter/packing/painter_header.hpp>

#include "sdl_painter_demo.hpp"

using namespace fastuidraw;

typedef std::bitset<32> bitset;

class painter_test:public sdl_painter_demo
{
public:
  painter_test(void):
    sdl_painter_demo("", true)
  {}

protected:
  void
  log_program(const reference_counted_ptr<gl::Program> &pr,
              const std::string &prefix)
  {
    {
      std::ostringstream name;
      name << prefix << "program.glsl";

      std::ofstream file(name.str().c_str());
      file << pr->log();

      std::cout << "Program Log and contents written to " << name.str() << "\n";
    }

    std::cout << "Vertex shaders written to:\n";
    for(unsigned int i = 0, endi = pr->num_shaders(GL_VERTEX_SHADER);
        i < endi; ++i)
      {
        std::ostringstream name;
        name << prefix << "vert." << i << ".glsl";

        std::ofstream file(name.str().c_str());
        file << pr->shader_src_code(GL_VERTEX_SHADER, i);

        std::cout << "\t" << name.str() << "\n";
      }

    std::cout << "Fragment shaders written to:\n";
    for(unsigned int i = 0, endi = pr->num_shaders(GL_FRAGMENT_SHADER);
        i < endi; ++i)
      {
        std::ostringstream name;
        name << prefix << "frag." << i << ".glsl";

        std::ofstream file(name.str().c_str());
        file << pr->shader_src_code(GL_FRAGMENT_SHADER, i);

        std::cout << "\t" << name.str() << "\n";
      }

    if(pr->link_success())
      {
        std::cout << "Link success\n";
        pr->use_program();
      }
    else
      {
        std::cout << "Link Failed\n";
      }
  }

  void
  derived_init(int, int)
  {
    log_program(m_backend->program(gl::PainterBackendGL::program_all), "painter.all.");
    log_program(m_backend->program(gl::PainterBackendGL::program_without_discard), "painter.without_discard.");
    log_program(m_backend->program(gl::PainterBackendGL::program_with_discard), "painter.with_discard.");

    std::cout << "\nUseful command to see shader after pre-processor:\n"
              << "\tsed 's/#version/@version/g' file.glsl | sed 's/#extension/@extension/g'"
              << " | cpp | grep -v \"#\" | sed '/^\\s*$/d'"
              << " | sed 's/@version/#version/g' | sed 's/@extension/#extension/g'\n";
  }

  void
  draw_frame(void)
  {
    end_demo(0);
  }

  void
  handle_event(const SDL_Event &ev)
  {
    switch(ev.type)
      {
      case SDL_QUIT:
        end_demo(0);
        break;

      case SDL_KEYUP:
        switch(ev.key.keysym.sym)
          {
          case SDLK_ESCAPE:
            end_demo(0);
            break;
          }
        break;
      };
  }

private:

};

int
main(int argc, char **argv)
{
  std::cout << std::setw(40) << "header_size = " << PainterHeader::header_size << "\n"
            << std::setw(40) << "clip_equations_data_size = " << PainterClipEquations::clip_data_size << "\n"
            << std::setw(40) << "item_matrix_data_size = " << PainterItemMatrix::matrix_data_size << "\n"
            << std::setw(40) << "image_data_size = " << ImageParams::data_size << "\n"
            << std::setw(40) << "linear_gradient_data_size = " << PainterBrush::linear_gradient_data_size << "\n"
            << std::setw(40) << "radial_gradient_data_size = " << PainterBrush::radial_gradient_data_size << "\n"
            << std::setw(40) << "repeat_window_data_size = " << RepeatWindowParams::data_size << "\n"
            << std::setw(40) << "transformation_matrix_data_size = " << PainterBrush::transformation_matrix_data_size << "\n"
            << std::setw(40) << "transformation_translation_data_size = " << PainterBrush::transformation_translation_data_size << "\n"
            << "\n"

            << std::setw(40) << "image_mask = " << bitset(PainterBrush::image_mask) << "\n"
            << std::setw(40) << "gradient_mask = " << bitset(PainterBrush::gradient_mask) << "\n"
            << std::setw(40) << "radial_gradient_mask = " << bitset(PainterBrush::radial_gradient_mask) << "\n"
            << std::setw(40) << "gradient_repeat_mask = " << bitset(PainterBrush::gradient_repeat_mask) << "\n"
            << std::setw(40) << "repeat_window_mask = " << bitset(PainterBrush::repeat_window_mask) << "\n"
            << std::setw(40) << "transformation_translation_mask = " << bitset(PainterBrush::transformation_translation_mask) << "\n"
            << std::setw(40) << "transformation_matrix_mask = " << bitset(PainterBrush::transformation_matrix_mask) << "\n"

            << std::setw(40) << "stroked_number_offset_types = " << StrokedPath::number_offset_types << "\n"
            << std::setw(40) << "stroked_number_point_set_types = " << StrokedPath::number_point_set_types << "\n"
            << std::setw(40) << "stroked_offset_type_bit0 = " << StrokedPath::offset_type_bit0 << "\n"
            << std::setw(40) << "stroked_offset_type_num_bits = " << StrokedPath::offset_type_num_bits << "\n"
            << std::setw(40) << "stroked_boundary_bit = " << StrokedPath::boundary_bit << "\n"
            << std::setw(40) << "stroked_depth_bit0 = " << StrokedPath::depth_bit0 << "\n"
            << std::setw(40) << "stroked_depth_num_bits = " << StrokedPath::depth_num_bits << "\n"
            << std::setw(40) << "stroked_join_bit = " << StrokedPath::join_bit << "\n"
            << std::setw(40) << "stroked_number_common_bits = " << StrokedPath::number_common_bits << "\n"
            << std::setw(40) << "stroked_normal0_y_sign_bit = " << StrokedPath::normal0_y_sign_bit << "\n"
            << std::setw(40) << "stroked_normal1_y_sign_bit = " << StrokedPath::normal1_y_sign_bit << "\n"
            << std::setw(40) << "stroked_sin_sign_bit = " << StrokedPath::sin_sign_bit << "\n"
            << std::setw(40) << "stroked_adjustable_cap_ending_bit = " << StrokedPath::adjustable_cap_ending_bit << "\n"
            << std::setw(40) << "stroked_bevel_edge_bit = " << StrokedPath::bevel_edge_bit << "\n";

  painter_test P;
  return P.main(argc, argv);

}
