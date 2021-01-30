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

#ifndef NYX_FILE_ARG_PARSER_H
#define NYX_FILE_ARG_PARSER_H

namespace nyx
{
  /** Class for parsing arguments to the Nyx file generator.
   */
  class ArgumentParser
  {
    public:

      /** Default constructor.
       */
      ArgumentParser() ;

      /** Default deconstructor.
       */
      ~ArgumentParser() ;

      /** Method to parge input arguments.
       * @param argc The amount of arguments to parse.
       * @param argv The string pointer of the arguments.
       */
      void parse( int argc, const char** argv ) ;

      /** Method to retrieve the number of inputs to Nyx generator.
       * @return unsigned The amount of inputs.
       */
      unsigned getNumberOfInputs() const ;

      /** Method to retrieve whether or not the shader generation is to recursively look into the input directory.
       * @return Whether or not the shader generation is to look recursively for shaders.
       */
      bool recursive() const ;

      /** Method to retrieve the directory to use for recursive loading.
       * @return const char* The string to the path on the filesystem to recursively look through.
       */
      const char* recursionDirectory() const ;

      /** Method to retrieve whether or not the NyxMaker program should produce verbose output.
       * @return Whether or not the NyxMaker program should produce verbose output.
       */
      bool verbose() const ;

      /** Method to get the include directory, if any, set by the passed in arguments.
       * @return The string representation of the include directory on the file systems.
       */
      const char* getIncludeDirectory() const ;

      /** Method to retrieve the file path for the specified index of input.
       * @param index The index of input to receive the file path of.
       * @return const char* The string representation to the shader on the filesystem.
       */
      const char* getFilePath( unsigned index ) const ;

      /** Method to retrieve the output file path to use.
       * @return The output file path to save shader information to.
       */
      const char* output() const ;

      /** Method to retrieve the usage of this program.
       * @return const char* The string message containing the usage of this program.
       */
      const char* usage() const ;

      /** Method to retrieve the shader type of the input at the specified index.
       * @param index The index of input to retrieve the shader type of.
       * @return int The shader type of the input, as directed by the extension.
       */
      int getShaderType( unsigned index ) const ;

      /** Method to retrieve whether or not the passed in arguments are valid.
       * @return Whether or not the passed in arguments are valid.
       */
      bool valid() const ;

    private:

      /** Forward-declared structure to contain this object's internal data.
       */
      struct ArgParserData* arg_data ;

      /** Method to retrieve a reference to this object's internal data.
       * @return Reference to this object's internal data.
       */
      ArgParserData& data() ;

      /** Method to retrieve a const-reference to this object's internal data.
       * @return Const-reference to this object's internal data.
       */
      const ArgParserData& data() const ;
  };
}
#endif