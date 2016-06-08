#include <iostream>
#include <string>

#include "moving_average.hpp"


using namespace std;


bool verbose = false;


const string is_full_string(bool isFull)
{
    static const string full_str ("Full");
    static const string not_full_str ("Not Full");

    if (isFull)
        return full_str;
    else
        return not_full_str;
}


class unit_test 
{
public:
    virtual bool run_test() = 0;
};


class unit_test_1 : public unit_test 
{

public:
    bool run_test()
    {
        moving_average<double, double> *ravg = new moving_average<double, double>(10);
        bool is_full;
        double avg;

        if (verbose)
            cout << "Test 1\n" << "-----------------------" << endl;

        for (int i = 1; i <= 20; i++) {

            avg = ravg->insert_and_average(i, &is_full);

            if (verbose)
                cout << i << ": " << avg << " : " << is_full_string(is_full) << endl;
        }

        if (verbose)
            cout << "\n" << endl;

        delete ravg;

        return true;
    }
} test1;


class unit_test_2 : public unit_test 
{

public:
    bool run_test()
    {
        double Buffer[10];
        moving_average<double, double> *ravg = new moving_average<double, double>(10, Buffer);
        bool is_full;
        double avg;

        if (verbose)
            cout << "Test 2\n" << "-----------------------" << endl;

        for (int i = 1; i <= 20; i++) {

            avg = ravg->insert_and_average(i, &is_full);

            if (verbose)
                cout << i << ": " << avg << " : " << is_full_string(is_full) << endl;
        }

        if (verbose)
            cout << "\n" << endl;

        delete ravg;

        return true;
    }
} test2;


class unit_test_3 : public unit_test 
{

public:
    bool run_test()
    {
        moving_average<double, double> *ravg = new moving_average<double, double>(3);
        bool is_full;
        double avg;
        int data = 1;
        int cnt = 0;

        if (verbose)
            cout << "Test 3\n" << "-----------------------" << endl;

        for (int i = 0; i < 20; i++) {

            if ((cnt != 0) && (cnt % 3) == 0) {
                data++;
            }
            cnt++;

            avg = ravg->insert_and_average(data, &is_full);

            if (verbose)
                cout << data << ": " << avg << " : " << is_full_string(is_full) << endl;
        }

        if (verbose)
            cout << "\n" << endl;

        delete ravg;

        return true;
    }
} test3;


class unit_test_4 : public unit_test 
{

public:
    bool run_test()
    {
        moving_average<double, double> *ravg = new moving_average<double, double>(5);
        bool is_full;
        double avg;
        int data = 1;
        int cnt = 0;

        if (verbose)
            cout << "Test 4\n" << "-----------------------" << endl;

        for (int i = 0; i < 50; i++) {

            if ((cnt != 0) && (cnt % 5) == 0) {
                data++;
            }
            cnt++;

            avg = ravg->insert_and_average(data, &is_full);

            if (verbose)
                cout << data << ": " << avg << " : " << is_full_string(is_full) << endl;
        }

        if (verbose)
            cout << "\n" << endl;

        delete ravg;

        return true;
    }
} test4;


class unit_test_5 : public unit_test 
{

public:
    bool run_test()
    {
        moving_average<double, int> *ravg = new moving_average<double, int>(5);
        bool is_full;
        double avg;
        int data = 1;
        int cnt = 0;

        if (verbose)
            cout << "Test 5\n" << "-----------------------" << endl;

        for (int i = 0; i < 50; i++) {

            if ((cnt != 0) && (cnt % 5) == 0) {
                data++;
            }
            cnt++;

            avg = ravg->insert_and_average(data, &is_full);

            if (verbose)
                cout << data << ": " << avg << " : " << is_full_string(is_full) << endl;
        }

        if (verbose)
            cout << "\n" << endl;

        delete ravg;

        return true;
    }
} test5;


const int NUM_TESTS = 5;


//
//  g++ -std=c++11 -Wall -Wpedantic -g -O0 moving_average_unit_test.cpp -o moving_average_unit_test
//  valgrind --leak-check=full  ./moving_average_unit_test 
//
int main (int argc, char *argv[])
{
    const string verbose_str ("--verbose");
    const string test_str ("--test");
    int run_test = -1;
    bool run_specific_test = false;

    for (int i = 1; i < argc; i++) {

        if (verbose_str.compare(argv[i]) == 0) {
            verbose = true;
        }
        else if (test_str.compare(argv[i]) == 0) {

            if (++i >= argc)
                break;

            run_test = stoi(argv[i], nullptr);

            if ((run_test > 0) && (run_test <= NUM_TESTS)) {
                run_specific_test = true;
            }
        }
    }

    unit_test *tests[NUM_TESTS] = 
    {
        &test1,
        &test2,
        &test3,
        &test4,
        &test5
    };


    if (run_specific_test) {

        if ( !tests[run_test - 1]->run_test() ) {
            cout << "Unit test " << run_test << "failed." << endl;
            return run_test;
        }
    }
    else {

        for (int i = 0; i < NUM_TESTS; i++) {
            bool success = tests[i]->run_test();
            if (!success) {
                cout << "Unit test " << i + 1 << "failed." << endl;
                return (i + 1);
            }
        }
    }

    cout << "Unit tests passed." << endl;
    
    return 0;
}


