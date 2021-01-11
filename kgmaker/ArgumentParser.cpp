/*
 * Copyright (C) 2020 Jordan Hendl
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ArgumentParser.h"
#include "../kgfile/KgFile.h"
#include <string>
#include <vector>
#include <map>
namespace kgl
{
  /**
   * @param name 
   * @return std::string 
   */
  static inline std::string getExtension( const std::string& name ) ;

  /**
   * @param extension 
   * @return ::tools::shader::ShaderStage 
   */
  static ::kgl::ShaderStage extensionToStage( std::string extension ) ;

  struct ArgParserData
  {
    std::string              include_directory   ;
    std::string              recursive_directory ;
    std::string              output_path         ;
    bool                     verbose             ;
    std::vector<std::string> shaders_paths       ;

    ArgParserData() ;
  };

  std::string getExtension( const std::string& name )
  {
    return ( name.rfind( '.' ) == std::string::npos ) ? "" : name.substr( name.rfind( '.' ) + 1 ) ;
  }

  static ::kgl::ShaderStage extensionToStage( std::string extension )
  {
         if( extension == "frag" ) return ::kgl::ShaderStage::FRAGMENT      ;
    else if( extension == "geom" ) return ::kgl::ShaderStage::GEOMETRY      ;
    else if( extension == "tesc" ) return ::kgl::ShaderStage::TESSALATION_C ;
    else if( extension == "tess" ) return ::kgl::ShaderStage::TESSELATION_E ;
    else if( extension == "comp" ) return ::kgl::ShaderStage::COMPUTE       ;
    else if( extension == "vert" ) return ::kgl::ShaderStage::VERTEX        ;

    return ::kgl::ShaderStage::VERTEX ;
  }

  ArgParserData::ArgParserData()
  {
    this->include_directory   = ""        ;
    this->recursive_directory = ""        ;
    this->output_path         = "out.uwu" ;
    this->shaders_paths       = {}        ;
    this->verbose             = false     ;
  }

  ArgumentParser::ArgumentParser()
  {
    this->arg_data = new ArgParserData() ;
  }

  ArgumentParser::~ArgumentParser()
  {
    delete this->arg_data ;
  }

  void ArgumentParser::parse( int num_inputs, const char** argv )
  {
    std::string buffer ;

    for( unsigned index = 1; index < static_cast<unsigned>( num_inputs ); index++ )
    {
      buffer = std::string( argv[ index ] ) ;

      if     ( buffer == "-i" && index + 1 < static_cast<unsigned>( num_inputs ) ) { data().include_directory   = std::string( argv[ index + 1 ] ) ; index++ ; }
      else if( buffer == "-o" && index + 1 < static_cast<unsigned>( num_inputs ) ) { data().output_path         = std::string( argv[ index + 1 ] ) ; index++ ; }
      else if( buffer == "-r" && index + 1 < static_cast<unsigned>( num_inputs ) ) { data().recursive_directory = std::string( argv[ index + 1 ] ) ; index++ ; }
      else if( buffer == "-v"                                 ) { data().verbose             = true                             ;           }
      else                                                      { data().shaders_paths.push_back( std::string( argv[ index ] ) )          ; }
    }
  }

  bool ArgumentParser::verbose() const
  {
    return data().verbose ;
  }

  bool ArgumentParser::recursive() const
  {
    return data().recursive_directory != "" ;
  }

  const char* ArgumentParser::output() const
  {
    std::string extention ;

    extention = ".kg" ;
    for( auto path : data().shaders_paths )
    {
      if( path.find( ".comp" ) != std::string::npos ) extention = ".kgc" ;
    }
    return ( data().output_path + extention ).c_str() ;
  }

  const char* ArgumentParser::recursionDirectory() const
  {
    return data().recursive_directory.c_str() ;
  }

  int ArgumentParser::getShaderType( unsigned index ) const
  {
    if( index < data().shaders_paths.size () ) 
    {
      return ::kgl::extensionToStage( ::kgl::getExtension( data().shaders_paths.at( index ) ) ) ;
    }

    return 0 ;
  }

  unsigned ArgumentParser::getNumberOfInputs() const
  {
    return data().shaders_paths.size() ;
  }

  const char* ArgumentParser::getFilePath( unsigned index ) const
  {
    return index < data().shaders_paths.size() ? data().shaders_paths[ index ].c_str() : "" ;
  }

  const char* ArgumentParser::usage() const
  {
    static const std::string program_usage = std::string( 
    "Usage:: kgmaker <shader.type1> <shader2.type2> ... <options>\n"  
    "  Options: -r <directory>\n"                                       
    "              -> Recursively parses all files in the directory.\n" 
    "           -i <directory>\n"                                 
    "              -> Sets the directory on the filesystem to use as the include directory for GLSL shader compilation.\n" 
    "           -v\n"                                                   
    "              -> Verbose output.\n"
    "           -o <name>\n"                                                   
    "              -> The output name, if not using recursive. File extension is automatically appended to input\n"
                                                        ) ;
    return program_usage.c_str() ;
  }

  bool ArgumentParser::valid() const
  {
    return !data().shaders_paths.empty() ;
  }

  ArgParserData& ArgumentParser::data()
  {
    return *this->arg_data ;
  }

  const ArgParserData& ArgumentParser::data() const
  {
    return *this->arg_data ;
  }
}