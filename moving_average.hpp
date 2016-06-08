/**
 *  @file moving_average.hpp
 *
 *  Template implementation of a generic moving average class.
 *  This is a simple moving average using the unweighted mean 
 *  of the previous N samples.
 *
 *  This template requires c++11 or higher.
 *
 *  The naming convention attempts to follow the C++ STL format, 
 *  which means lower case, underscores, etc.
 *  
 *  MIT License
 *
 *  Copyright (c) 2015, Michael Becker
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

#ifndef MOVING_AVERAGE_HPP_
#define MOVING_AVERAGE_HPP_


/**
 *  Template class for Moving Averages.
 *  Allows you to select type of data as well as calculation result.
 *  So you can specify that the data is int, while you want double 
 *  precision for your answers.
 */
template <typename TPoint, typename TCalculation>
class moving_average
{
    public:

        /**
         *  ctor, uses dynamic memory for buffering.
         *  @param[in] num_points The number of points you want in 
         *             the moving average.
         */
        moving_average(int num_points)
            : max_num_points(num_points),
              need_to_delete_point_buffer(true),
              initial_num_points(0),
              index(0),
              sum(0),
              fix_cumulative_error_sum(0)
        {
            point_buffer = new TPoint [max_num_points];
        }

        /**
         *  ctor, uses preallocated memory for buffering.
         *  Useful if you are trying to avoid malloc / new.
         *  @param[in] num_points The number of points you want in 
         *             the moving average.
         *  @param[in] buffer The point buffer we are supposed to use.
         */
        moving_average(int num_points, TPoint* buffer)
            : max_num_points(num_points),
              point_buffer(buffer),
              need_to_delete_point_buffer(false),
              initial_num_points(0),
              index(0),
              sum(0),
              fix_cumulative_error_sum(0)
        {
            point_buffer = buffer;
        }

        /**
         *  dtor, frees memory if needed.
         */ 
        ~moving_average()
        {
            if (need_to_delete_point_buffer)
                delete[] point_buffer;
        }

        /**
         *  Insert a new point and return the current average.
         *  @param[in]  point The new data point to insert and use.
         *  @param[out] buffer_full Has the buffer filled up yet?
         *  @return     Current average.
         */
        TCalculation insert_and_average(const TPoint point, bool *buffer_full)
        {
            TCalculation avg;

            if (initial_num_points < max_num_points) {

                initial_num_points++;
                sum += point;
                point_buffer[index++] = point;
                avg = sum / initial_num_points;

                if (index >= max_num_points)
                    index = 0;
            }
            else {

                TCalculation oldest_point = point_buffer[index];

                point_buffer[index++] = point;
                fix_cumulative_error_sum += point;

                if (index >= max_num_points) {
                    index = 0;
                    sum = fix_cumulative_error_sum;
                    fix_cumulative_error_sum = 0;
                }
                else {
                    sum = sum + point - oldest_point;
                }

                avg = sum / max_num_points;
            }

            if (buffer_full != nullptr)
                 *buffer_full = is_buffer_full();

            return avg;
        }

        /**
         *  Get the current average.
         *  @param[out] buffer_full Has the buffer filled up yet?
         *  @return     Current average.
         */
        TCalculation get_average(bool *buffer_full)
        {
            TCalculation avg;

            if (initial_num_points > 0)
                avg = sum / initial_num_points;
            else 
                avg = 0;

            if (buffer_full != nullptr)
                 *buffer_full = is_buffer_full();

            return avg;
        }

        /**
         *  Reset the average.
         */
        void reset()
        {
            initial_num_points = 0;
            index = 0;
            sum = 0;
            fix_cumulative_error_sum = 0;
        }


    private:

        /**
         *  Helper to determine if we've filled the buffer yet.
         */
        inline bool is_buffer_full()
        {
            if (initial_num_points == max_num_points)
                return true;
            else
                return false;
        }

        /**
         *  The size (in TPoint type) of point_buffer.
         */
        const int max_num_points;

        /**
         *  Where we buffer the points.
         */
        TPoint *point_buffer;

        /**
         *  If we dynamically allocated the buffer, remember to clean up.
         */
        bool need_to_delete_point_buffer;

        /**
         *  Count of the points as we are initially filling the buffer.
         */
        int initial_num_points;

        /**
         *  The current insertion index into point_buffer.
         */
        int index;

        /**
         *  The current sum of the points in point_buffer.
         */
        TCalculation sum;

        /**
         *  Attempt to prevent cumulative errors in sum. This replaces sum 
         *  after every max_num_points iterations.
         */
        TCalculation fix_cumulative_error_sum;
};

#endif

