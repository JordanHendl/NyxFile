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


#ifndef KARMA_GPU_WRITER_H
#define KARMA_GPU_WRITER_H

namespace kgl
{
  /** The Shader stage this shader 
   */
  enum ShaderStage : unsigned ;
  enum UniformType : unsigned ;
  
  /** Class to manage writing & reading KgFile's to disk.
   */
  class KgWriter
  {
    public:
      
      /** Default Constructor. 
       */
      KgWriter() ;

      /** Default Deconstructor.
       */
      ~KgWriter() ;

      /** Method to compile the shader with the specific stage and data.
       * @param stage The stage to use for the input shader data.
       * @param data The bytes of a valid GLSL file.
       */
      void compile( ShaderStage stage, const char* data ) ;

      /** Method to save the compiled shaders to disk.
       * @param path The path on the filesystem to save the .kg data to.
       */
      void save( const char* path ) ;

      /** Method to set the include directory for the GLSL files to use.
       * @param include_dir The string of the include directory on the filesystem
       */
      void setIncludeDirectory( const char* include_dir ) ;

      /** Method to retrieve the size of this object.
       * @return The number of shaders compiled into this object.
       */
      unsigned size() const ;

    private:

        /** Forward declared structure containing this object's data.
         */
      struct KgWriterData* compiler_data ;

        /** Method to retrieve a reference to this object's internal data structure.
         * @return Reference to this object's internal data structure.
         */
      KgWriterData& data() ;

        /** Method to retrieve a const-reference to this object's internal data structure.
         * @return Const-reference to this object's internal data structure.
         */
      const KgWriterData& data() const ;
  };
}
#endif

