/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HeaderMaker.cpp
 * Author: jhendl
 * 
 * Created on February 7, 2021, 3:14 PM
 */

#include "HeaderMaker.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
#include <fstream>
#include <iomanip>

namespace nyx
{
  static std::string getFilename( const char* full_path ) ;
  static std::string getFilepath( const char* full_path ) ;
  
  struct HeaderMakerData
  {
    std::ifstream              input  ;
    std::ofstream              output ;
    std::vector<unsigned char> bytes  ;
    
    void load( const char* file_path ) ;
    void write( std::string output_dir, std::string file_name ) ;
  };

  std::string getFilename( const char* full_path )
  {
    std::string filename = full_path ;

    const size_t last_slash_idx = filename.find_last_of( "\\/" ) ;
    if ( std::string::npos != last_slash_idx )
    {
      filename.erase( 0, last_slash_idx + 1 ) ;
    }
    
    const size_t period_idx = filename.rfind( '.' ) ;
    if ( std::string::npos != period_idx )
    {
      filename.erase( period_idx ) ;
    }
    
    return filename + ".h" ;
  }
  
  std::string getFilepath( const char* full_path )
  {
    std::string path = full_path ;

    const size_t last_slash_idx = path.find_last_of( "\\/" ) ;
    if ( std::string::npos != last_slash_idx )
    {
      path.erase( last_slash_idx, path.size() ) ;
    }
    else
    {
      path.clear() ;
    }
    
    return path ;
  }
  
  void HeaderMakerData::load( const char* file_path )
  {
    this->input.open( file_path, std::ios::binary ) ;
    
    if( this->input )
    {
      // Copy stream's contents into string.
      this->input.seekg  ( 0, std::ios::end    ) ;
      this->bytes.reserve( this->input.tellg() ) ;
      this->input.seekg  ( 0, std::ios::beg    ) ;
      
      this->bytes.assign ( ( std::istreambuf_iterator<char>( this->input ) ), std::istreambuf_iterator<char>() ) ;
    }
    
    this->input.close() ;
  }

  void HeaderMakerData::write( std::string output_dir, std::string file_name )
  {
    if( !output_dir.empty() )
    {
      this->output.open( output_dir + std::string( "/" ) + file_name ) ;
    }
    else this->output.open( file_name ) ;
      
    
    file_name.pop_back() ;
    file_name.pop_back() ;

    unsigned line_count = 0 ;
    if( this->output )
    {
      this->output << ( "#pragma once\n"              ) ;
      this->output << ( "\n"                          ) ;
      this->output << ( "namespace nyx\n"             ) ;
      this->output << ( "{\n"                         ) ;
      this->output << ( "  namespace bytes\n"         ) ;
      this->output << ( "  {\n"                       ) ;
      this->output << ( "    const unsigned char "    ) ;
      this->output << file_name                         ;
      this->output << "[] = \n    {\n      "            ;
      
      for( unsigned index = 0; index < this->bytes.size(); index++ )
      {
        line_count++ ;
        this->output << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << static_cast<int>( this->bytes[ index ] ) ;
        
        if( index != this->bytes.size() - 1 ) this->output << ( ", " ) ;
        if( line_count > 20 )
        {
          this->output << ( "\n      " ) ;
          line_count = 0 ;
        }
      }

      this->output << ( "\n    } ; " ) ;
      this->output << ( "\n  }" ) ;
      this->output << ( "\n} \0"   ) ;
    }

    this->output.close() ;
  }

  HeaderMaker::HeaderMaker()
  {
    this->maker_data = new HeaderMakerData() ;
  }

  HeaderMaker::~HeaderMaker()
  {
    delete this->maker_data ;
  }

  void HeaderMaker::make( const char* file_path )
  {
    data().load( file_path ) ;
    data().write( getFilepath( file_path ), getFilename( file_path ) ) ;
  }

  HeaderMakerData& HeaderMaker::data()
  {
    return *this->maker_data ;
  }

  const HeaderMakerData& HeaderMaker::data() const
  {
    return *this->maker_data ;
  }
}

