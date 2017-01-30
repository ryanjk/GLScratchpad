:: Use this batch to add a new program to GL Scratch Pad

:: ex: generate-program MyNewProgram 512 512

@ECHO OFF

SET program_name=%1
SET x_res=%2
SET y_res=%3

SET replace=.\fart -C -q

:: create_header(program_name)
SET header_dir=..\
COPY .\header_template.txt "%header_dir%%program_name%.h" >NUL
%replace% "%header_dir%%program_name%.h" REPLACEME %program_name%

:: create_source(program_name)
SET source_dir=..\
COPY .\source_template.txt "%source_dir%%program_name%.cpp" >NUL
%replace% "%source_dir%%program_name%.cpp" REPLACEME %program_name%

:: create_json(program_name, x_resolution, y_resolution)
SET program_def_dir=..\data\
SET program_def_type=.json
SET def_file="%program_def_dir%%program_name%%program_def_type%"
COPY .\program_def_template.txt %def_file% >NUL
%replace% "%def_file%" REPLACEME %program_name%
%replace% "%def_file%" X_RESOLUTION %x_res%
%replace% "%def_file%" Y_RESOLUTION %y_res%

:: modify_application_load_program_source(program_name)
SET program_load_cpp_dir=..\
SET program_load_cpp_file=ApplicationProgramLoad.cpp
SET program_load_path=%program_load_cpp_dir%%program_load_cpp_file%

SET header_replace=\/\/INSERT_HEADER_HERE
SET header_include_line=#include \"%program_name%.h\"\n%header_replace%
%replace% %program_load_path% "%header_replace%" "%header_include_line%"

SET statement_replace=\/\/INSERT_STATEMENT_HERE
SET statement_line="else if (name == \"%program_name%\") {\n\t\tprogram_ = std::make_shared<glsp::%program_name%>(&camera_);\n	}\n\t%statement_replace%"
%replace% %program_load_path% "%statement_replace%" %statement_line%

:: generate_shader(program_name)
SET shader_program_dir=..\data\Shader\
SET new_dir=%shader_program_dir%%program_name%\
MKDIR %new_dir%
COPY .\vs_template.txt %new_dir%vs.glsl >NUL
COPY .\fs_template.txt %new_dir%fs.glsl >NUL

ECHO Successfully created new program %program_name%.