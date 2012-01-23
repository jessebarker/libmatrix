#include <string>
#include "libmatrix_test.h"
#include "shader_source_test.h"
#include "../shader-source.h"

using std::string;

void
ShaderSourceBasic::run(const Options& options)
{
    static const string vtx_shader_filename("test/basic.vert");
    static const string frg_shader_filename("test/basic.frag");

    ShaderSource vtx_source(vtx_shader_filename);
    ShaderSource vtx_source2(vtx_shader_filename);
    ShaderSource frg_source(frg_shader_filename);
    ShaderSource frg_source2(frg_shader_filename);
    
    pass_ = ((vtx_source.str() == vtx_source2.str()) &&
             (frg_source.str() == frg_source2.str()));
    return;
}
