/**
 *  @file
 *
 *  Experimenting with C++ Futures
 *
 *  To compile:
 *  g++ -g --std=c++11 futures_test.cpp -lpthread -o futures_test
 *  
 *  To test:
 *  valgrind -v --leak-check=full ./futures_test
 *
 *  MIT License
 *
 *  Copyright (c) 2016, Michael Becker (michael.f.becker@gmail.com)
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
#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>


using namespace std;


class WorkerThread {

    public:

        WorkerThread()
        {
            Thread = thread(RunWrapper, this);
        }

        void EndThread() 
        {
            RunThread = false;
            Thread.join();
        }

        future<string> ExecuteWork(string input) 
        {
            lock_guard<mutex> guard(Lock);

            prom = new promise<string>();
            future<string> fut = prom->get_future();
            Input = input;
            return fut;
        }

    private:
        thread Thread;
        volatile bool RunThread {true};
        string Input;
        promise<string> *prom;
        mutex Lock;

        static void RunWrapper (WorkerThread *w)
        {
            w->Run();
        }

        void Run() 
        {
            while(RunThread) {

                cout << "[THR ] I'm working in a coal mine..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                
                do {
                    lock_guard<mutex> guard(Lock);

                    if (Input.length() > 0) {
                        cout << "[THR ] Starting on " << Input << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                        cout << "[THR ] Working on " << Input << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                        cout << "[THR ] Working on " << Input << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                        cout << "[THR ] Completed " << Input 
                             << " Setting promise value." << endl;
                        Input = "";
                        prom->set_value("{Thread is all done!}");
                        delete prom;
                    }
                } while(false);
            }

            cout << "[THR ] Whew! I am so tired!" << endl;
        }
};


int main ()
{
    cout << "[MAIN] Experimenting with C++ futures as return values" << endl;

    WorkerThread worker;

    this_thread::sleep_for(chrono::seconds(2));
    cout << "[MAIN] Sending work1 off..." << endl;
    future<string> fut = worker.ExecuteWork("{Lot's o work 1!}");
    cout << "[MAIN] Work1 sent" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "[MAIN] waiting for future..." << endl;
    string s = fut.get();
    cout << "[MAIN] Future done! " << s << endl;


    this_thread::sleep_for(chrono::seconds(2));
    cout << "[MAIN] Sending work2 off..." << endl;
    fut = worker.ExecuteWork("{Lot's o work 2!}");
    cout << "[MAIN] Work2 sent" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    do { 
        cout << "[MAIN] polling for future..." << endl;
    } while ( fut.wait_for(chrono::seconds(1)) != future_status::ready);
    s = fut.get();


    cout << "[MAIN] Future done! " << s << endl;


    this_thread::sleep_for(chrono::seconds(2));
    worker.EndThread();


    return 0;
}


