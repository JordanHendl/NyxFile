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


#include "../kgwriter/KgWriter.h"
#include "../kgfile/KgFile.h"
#include "ArgumentParser.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

static std::string loadStream( std::ifstream& stream ) ;
static ::kgl::ShaderStage extensionToStage( std::string extension ) ;
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

::kgl::ShaderStage extensionToStage( std::string extension )
{
       if( extension == "frag" ) return ::kgl::ShaderStage::FRAGMENT      ;
  else if( extension == "geom" ) return ::kgl::ShaderStage::GEOMETRY      ;
  else if( extension == "tesc" ) return ::kgl::ShaderStage::TESSALATION_C ;
  else if( extension == "tess" ) return ::kgl::ShaderStage::TESSELATION_E ;
  else if( extension == "comp" ) return ::kgl::ShaderStage::COMPUTE       ;
  else if( extension == "vert" ) return ::kgl::ShaderStage::VERTEX        ;
  
  return ::kgl::ShaderStage::VERTEX ;
}

int main( int argc, const char** argv )
{
  std::ifstream         stream           ;
  ::kgl::ArgumentParser parser           ;
  ::kgl::KgWriter       shader           ;
  ::kgl::KgFile         shader_validator ;
  std::string           recursive_path   ;
  std::string           directory_name   ;

  parser.parse( argc, argv ) ;
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
      stream.open( parser.getFilePath( i ) ) ;
      if( stream )
      {
        shader.compile( static_cast<::kgl::ShaderStage>( parser.getShaderType( i ) ), loadStream( stream ).c_str() ) ;
        stream.close() ;
      }
    }
    
    shader.save( parser.output() ) ;
    
    if( parser.verbose() )
    {
      shader_validator.load( parser.output() ) ;
      
      for( auto sh = shader_validator.begin(); sh != shader_validator.end(); ++sh )
      {
        std::cout << "Shader Stage:   " << sh.stage()         << "\n" ;
        std::cout << "Num Uniforms:   " << sh.numUniforms()   << "\n" ;
        std::cout << "Num Attributes: " << sh.numAttributes() << "\n" ;
        
        for( unsigned i = 0; i < sh.numAttributes(); i++ )
        {
          std::cout << "  Attribute Name       : " << sh.attributeName    ( i ) << "\n" ;
          std::cout << "  Attribute Type       : " << sh.attributeType    ( i ) << "\n" ;
          std::cout << "  Attribute Size       : " << sh.attributeByteSize    ( i ) << "\n" ;
          std::cout << "  Attribute Location   : " << sh.attributeLocation( i ) << "\n" ;
          std::cout << "  Attribute is INPUT   : " << sh.attributeIsInput ( i ) << "\n" ;
          std::cout << "\n" ;
        }
        std::cout << "     -+-+ -+-+ -+-+ -+-+ -+-+ -+-+ -+-+\n\n" ;
        for( unsigned i = 0; i < sh.numUniforms(); i++ )
        {
          std::cout << "  Uniform Name   : " << sh.uniformName   ( i ) << "\n" ;
          std::cout << "  Uniform Binding: " << sh.uniformBinding( i ) << "\n" ;
          std::cout << "  Uniform Type   : " << sh.uniformType   ( i ) << "\n" ;
          std::cout << "  Uniform Size   : " << sh.uniformSize   ( i ) << "\n" ;
          std::cout << "\n" ;
        }
        std::cout << "\n" ;
        std::cout << "---------------------------------------------\n" ;
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