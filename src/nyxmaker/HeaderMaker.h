/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HeaderMaker.h
 * Author: jhendl
 *
 * Created on February 7, 2021, 3:14 PM
 */

#pragma once
namespace nyx
{
  class HeaderMaker
  {
    public:
      HeaderMaker() ;
      ~HeaderMaker() ;
      void make( const char* file_path ) ;
    private:
      HeaderMaker( const HeaderMaker& orig ) ;
      HeaderMaker& operator=( const HeaderMaker& orig ) ;
      struct HeaderMakerData *maker_data ;
      HeaderMakerData& data() ;
      const HeaderMakerData& data() const ;
  };
}

