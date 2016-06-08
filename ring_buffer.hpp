/**
 *  @file ring_buffer.hpp
 *
 *  Template implementation of a generic ring buffer. 
 *
 *  This template requires c++11 or higher.
 *
 *  The naming convention attempts to follow the C++ STL format, 
 *  which means lower case, underscores, etc.
 *  
 *  MIT License
 *
 *  Copyright (c) 2016, Michael Becker
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a 
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 *  and/or sell copies of the Software, and to permit persons to whom the 
 *  Software is furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included 
 *  in all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 *  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT 
 *  OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
 *  THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef RING_BUFFER_HPP_
#define RING_BUFFER_HPP_


#include <exception>


/**
 *  Custom exception for the ring_buffer ctor.
 */
class ring_buffer_max_num_points_exception : public std::exception
{
    public:
        virtual const char *what() noexcept
        {
            return "Invalid size specified";
        }

        ring_buffer_max_num_points_exception(int invalidmax_num_points) noexcept
        : invalid_max_num_points(invalidmax_num_points)
        {
        }

        const int invalid_max_num_points;
};


/**
 *  Template class for a Ring Buffer implementation.
 *  This class contains reduce functions. So coupled with C++ lambdas 
 *  you can add your own functions such as addition, etc. across all 
 *  of the currently buffered elements of the ring buffer.
 */
template <typename TPoint>
class ring_buffer
{
    public:

        /**
         *  ctor, uses dymanic memory buffering.
         *  @param[in] num_points How many points you want in the buffer.
         *  @throws ring_buffer_max_num_points_exception, you need at least 
         *  2 points in this implementation.
         */
        ring_buffer(int num_points)
            : max_num_points(num_points),
              initial_num_points(0),
              index(0)
        {
            if (max_num_points < 2) {
                throw new ring_buffer_max_num_points_exception(max_num_points);
            }

            point_buffer = new TPoint[max_num_points];
        }


        /**
         *  dtor, frees memory.
         */ 
        ~moving_average()
        {
            delete[] point_buffer;
        }


        /**
         *  Adds a point to the ring buffer.
         */
        void insert(const TPoint point)
        {
            if (initial_num_points < max_num_points) {
                initial_num_points++;
            }

            point_buffer[index++] = point;

            if (index >= max_num_points) {
                index = 0;
            }
        }

        
        /**
         *  Resets the ring buffer to empty.
         */
        void reset()
        {
            initial_num_points = 0;
            index = 0;
        }


        /**
         *  @return The current number of points in the buffer.
         */
        int cur_buffer_size()
        {
            return initial_num_points;
        }


        /**
         *  Applies a function across all valid points in the buffer.
         *  @param reduce_fcn A function that takes two values, and returns a third.
         *  @param initial_value The desired first value passed to reduce_fcn.
         *  @returns The reduced value.
         */
        TPoint reduce( TPoint(*reduce_fcn)(TPoint data_point, TPoint reduced_value), TPoint initial_value)
        {
            TPoint reduced_value = initial_value;

            for (int i = 0; i < initial_num_points; i++) 
                reduced_value = reduce_fcn(point_buffer[i], reduced_value);

            return reduced_value;
        }


        /**
         *  Applies a function across all valid points in the buffer.
         *  @param reduce_fcn A function that takes two values, and returns a third.
         *  @returns The reduced value.
         */
        TPoint reduce( TPoint(*reduce_fcn)(TPoint data_pt, TPoint init_val))
        {
            TPoint reduced_value = point_buffer[0];

            for (int i = 1; i < initial_num_points; i++) 
                reduced_value = reduce_fcn(point_buffer[i], reduced_value);

            return reduced_value;
        }


    private:
        /**
         *  The size (in TPoint type) of point_buffer.
         */
        const int max_num_points;

        /**
         *  Where we buffer the points.
         */
        TPoint *point_buffer;

        /**
         *  Count of the points as we are initially filling the buffer.
         */
        int initial_num_points;

        /**
         *  The current insertion index into point_buffer.
         */
        int index;
};


#endif

