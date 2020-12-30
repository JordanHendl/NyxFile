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

#ifndef KARMA_FILE_ARG_PARSER_H
#define KARMA_FILE_ARG_PARSER_H

namespace karma
{
  namespace file
  {
    /** TODO
     */
    class ArgumentParser
    {
      public:
      
        /**
         */
        ArgumentParser() ;

        /**
         */
        ~ArgumentParser() ;

        /**
         * @param argc 
         * @param argv 
         */
        void parse( int argc, const char** argv ) ;

        /**
         * @return unsigned 
         */
        unsigned getNumberOfInputs() const ;

        /**
         * @return true 
         * @return false 
         */
        bool recursive() const ;

        /**
         * @return const char* 
         */
        const char* recursionDirectory() const ;
        
        /**
         * @return 
         */
        bool verbose() const ;
        

        /**
         * @param index 
         * @return const char* 
         */
        const char* getFilePath( unsigned index ) const ;
        
        /**
         * @param index
         * @return 
         */
        const char* output() const ;

        /**
         * @return const char* 
         */
        const char* usage() const ;

        /**
         * @param index 
         * @return int 
         */
        int getShaderType( unsigned index ) const ;

        /**
         * @return true 
         * @return false 
         */
        bool valid() const ;
      private:

        /**
         */
        struct ArgParserData* arg_data ;

        /**
         * @return ArgParserData& 
         */
        ArgParserData& data() ;

        /**
         * @return const ArgParserData& 
         */
        const ArgParserData& data() const ;
    };
  }
}
#endif