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


#include "../nyxwriter/NyxWriter.h"
#include "../nyxfile/NyxFile.h"
#include "ArgumentParser.h"
#include "HeaderMaker.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#if defined ( __unix__ ) || defined( _WIN32 )
  constexpr const char* COLOR_END    = "\x1B[m"       ;
  constexpr const char* COLOR_RED    = "\u001b[31m"   ;
  constexpr const char* COLOR_GREEN  = "\u001b[32m"   ;
  constexpr const char* COLOR_YELLOW = "\u001b[33m"   ;
  constexpr const char* COLOR_GREY   = "\x1B[1;30m"   ;
  constexpr const char* COLOR_CYAN   = "\u001b[36m"   ;
  constexpr const char* COLOR_BCYAN  = "\u001b[36;1m" ;
  constexpr const char* COLOR_BOLD   = "\u001b[1m"    ;
  constexpr const char* UNDERLINE    = "\u001b[4m"    ;
#else
  constexpr const char* COLOR_END    = "" ;
  constexpr const char* COLOR_GREEN  = "" ;
  constexpr const char* COLOR_CYAN   = "" ;
  constexpr const char* COLOR_BCYAN  = "" ;
  constexpr const char* COLOR_YELLOW = "" ;
  constexpr const char* COLOR_GREY   = "" ;
  constexpr const char* COLOR_RED    = "" ;
  constexpr const char* COLOR_BOLD   = "" ;
  constexpr const char* COLOR_WHITE  = "" ;
#endif

static std::string loadStream( std::ifstream& stream ) ;
static ::nyx::ShaderStage extensionToStage( std::string extension ) ;
static std::string getExtension( const std::string& name ) ;

std::string loadStream( std::ifstream& stream )
{
  std::string buff ;
  buff = std::string( ( std::istreambuf_iterator<char>( stream ) ), std::istreambuf_iterator<char>() ) ;

  return buff ;
}

std::string getExtension( const std::string& name )
{
  return ( name.rfind( '.' ) == std::string::npos ) ? "" : name.substr( name.rfind( '.' ) + 1 ) ;
}

::nyx::ShaderStage extensionToStage( std::string extension )
{
       if( extension == "frag" ) return ::nyx::ShaderStage::Fragment ;
  else if( extension == "geom" ) return ::nyx::ShaderStage::Geometry ;
  else if( extension == "tesc" ) return ::nyx::ShaderStage::Tess_C   ;
  else if( extension == "tess" ) return ::nyx::ShaderStage::Tess_E   ;
  else if( extension == "comp" ) return ::nyx::ShaderStage::Compute  ;
  else if( extension == "vert" ) return ::nyx::ShaderStage::Vertex   ;
  
  return ::nyx::ShaderStage::Vertex ;
}

int main( int argc, const char** argv )
{
  std::ifstream         stream           ;
  ::nyx::ArgumentParser parser           ;
  ::nyx::NyxWriter      shader           ;
  ::nyx::NyxFile        shader_validator ;
  std::string           recursive_path   ;
  std::string           directory_name   ;
  unsigned              index            ;
  
  index = 0 ;
  parser.parse( argc, argv ) ;
  shader.setIncludeDirectory( parser.getIncludeDirectory() ) ;
  if( parser.valid() )
  {
    if( parser.recursive() )
    {
      recursive_path = std::string( parser.recursionDirectory() ) ;
      for( auto& file : std::filesystem::directory_iterator( recursive_path ) )
      {
        if( file.is_directory() ) 
        {
          if( !directory_name.empty() ) shader.save( directory_name.c_str() ) ;
          directory_name = file.path() ;
        }
        else
        {
          shader.compile( extensionToStage( getExtension( file.path().string() ) ), file.path().string().c_str() ) ;
        }
      }      
    }

    for( unsigned i = 0; i < parser.getNumberOfInputs(); i++ )
    {
      if( parser.verbose() )
      {
        std::cout << ::COLOR_BOLD <<  "Compiling: " << parser.getFilePath( i ) << ::COLOR_END << std::endl ;
      }

      stream.open( parser.getFilePath( i ) ) ;
      if( stream )
      {
        shader.compile( static_cast<::nyx::ShaderStage>( parser.getShaderType( i ) ), loadStream( stream ).c_str() ) ;
      }
      else
      {
        std::cout << ::COLOR_RED << "Cannot load file " << parser.getFilePath( i ) << ::COLOR_END << std::endl ;
        std::cout << ::COLOR_RED << "Exitting..."                                  << ::COLOR_END << std::endl ;
        exit( -1 ) ;
      }
      stream.close() ;
    }
    
    shader.save( parser.output() ) ;
    if( parser.outputHeader() )
    {
      nyx::HeaderMaker maker ;
      maker.make( parser.output() ) ;
    }

    if( parser.verbose() )
    {
      shader_validator.load( parser.output() ) ;
      std::cout << COLOR_BOLD << "Include Directory: " << parser.getIncludeDirectory() << "\n" << COLOR_END << std::endl ;
      
      if( shader_validator.numInputs() != 0 ) std::cout << COLOR_BOLD << "Pipeline Inputs: \n\n" << COLOR_END ;
      for( unsigned i = 0; i < shader_validator.numInputs(); i++ )
      {
        std::cout << COLOR_BOLD << "-- Name: " << shader_validator.inputName( i ) << "\n" ;
        std::cout << COLOR_BOLD << "--   ├─Input Type      : " << shader_validator.inputType    ( i ) << COLOR_END << "\n" ;
        std::cout << COLOR_BOLD << "--   ├─Input Byte Size : " << shader_validator.inputByteSize( i ) << COLOR_END << "\n" ;
        std::cout << COLOR_BOLD << "--   └─Input Location  : " << shader_validator.inputLocation( i ) << COLOR_END << "\n" ;
        std::cout << "\n" ;
      }
      
      if( shader_validator.numOutputs() != 0 ) std::cout << COLOR_BOLD << "Pipeline Outputs: \n\n" << COLOR_END ;
      for( unsigned i = 0; i < shader_validator.numOutputs(); i++ )
      {
        std::cout << COLOR_BOLD << "-- Name: " << shader_validator.outputName( i ) << "\n" ;
        std::cout << COLOR_BOLD << "--   ├─Output Type      : " << shader_validator.outputType    ( i ) << COLOR_END << "\n" ;
        std::cout << COLOR_BOLD << "--   ├─Output Byte Size : " << shader_validator.outputByteSize( i ) << COLOR_END << "\n" ;
        std::cout << COLOR_BOLD << "--   └─Output Location  : " << shader_validator.outputLocation( i ) << COLOR_END << "\n" ;
        std::cout << "\n" ;
      }
      
      for( auto sh = shader_validator.begin(); sh != shader_validator.end(); ++sh )
      {
        std::cout << COLOR_BOLD << "Shader: " << parser.getFilePath( index++ )  << COLOR_END << "\n"   ;
        std::cout << COLOR_BOLD << "  ├─Shader Stage:   " << sh.stage()         << COLOR_END << "\n"   ;
        std::cout << COLOR_BOLD << "  └─Num Uniforms:   " << sh.numUniforms()   << COLOR_END << "\n"   ;
        
        if( sh.numUniforms() != 0 ) std::cout << COLOR_BOLD << "Uniforms: \n\n" << COLOR_END ;
        for( unsigned i = 0; i < sh.numUniforms(); i++ )
        {
          std::cout << COLOR_BOLD << "-- Name: " << sh.uniformName( i ) << "\n" ;
          std::cout << COLOR_BOLD << "--   ├─Uniform Binding : " << sh.uniformBinding( i ) << COLOR_END << "\n" ;
          std::cout << COLOR_BOLD << "--   ├─Uniform Type    : " << sh.uniformType   ( i ) << COLOR_END << "\n" ;
          std::cout << COLOR_BOLD << "--   └─Uniform Size    : " << sh.uniformSize   ( i ) << COLOR_END << "\n" ;
          std::cout << "\n" ;
        }
        std::cout << std::string( 80, '-' ) << "\n\n" ;
      }
    }
  }
  else
  {
    std::cout << parser.usage() << std::endl ;
    return -1 ;
  }  
  return 0 ;
}