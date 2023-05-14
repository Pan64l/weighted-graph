#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include"graph.hpp"

int main(){

    std::string cmd = "";
    graph Mygraph;

    while(std::cin >> cmd)
    {
        if(cmd == "i")
        {
            int a;
            int b;
            double w;

            std::cin >> a >> b >> w;
            try
            {
                if (a > 23133 || a < 1 || b > 23133 || b < 1 || w > 1 || w < 0)
                {
                    throw illegal_exception();
                }

                bool is_find = Mygraph.find(a, b, w);
                // std::cout << is_find << std::endl;

                if(is_find == true)
                {
                    std::cout << "failure" << std::endl;
                }
                else{

                    Mygraph.insert(a, b, w);
                    std::cout << "success" << std::endl;

                }
            }
            catch (illegal_exception)
            {
                std::cout << "illegal argument" << std::endl;
            }

        }

        else if(cmd == "load")
        {
            std::ifstream fin("paperCollabWeighted.txt");
            // std::string e;
            int a;
            int b;
            double w;
            
            while(fin >> a >> b >> w)
            {
                Mygraph.insert(a, b, w);
                // std::cout << a << std::endl;
            }

            std::cout << "success" << std::endl;
        }

        else if(cmd == "size")
        {
            std::cout << "number of vertices is " << Mygraph.num_of_v() << std::endl;
        }

        else if(cmd == "p")
        {
            int a;
            std::cin >> a;
            try
            {
                if (a > 23133 || a < 1)
                {
                    throw illegal_exception();
                }

                Mygraph.print(a);
                std::cout << std::endl;
            }
            catch(illegal_exception)
            {
                std::cout << "illegal argument" << std::endl;
            }

        }

        else if(cmd == "d")
        {
            int a;
            std::cin >> a;
            try
            {
                if (a > 23133 || a < 1)
                {
                    throw illegal_exception();
                }

                Mygraph.del(a);
            }
            catch(illegal_exception)
            {
                std::cout << "illegal argument" << std::endl;
            }


        }

        else if(cmd == "mst")
        {
            int a;
            std::cin >> a;
            if(Mygraph.vertex_in(a) == true)
            {
                Mygraph.max_s(a);
                Mygraph.clear_mst();
            }
            else
            {
                std::cout << "failure" << std::endl;
            }


        }

        else if(cmd == "exit")
        {
            return 0;
        }


    }
    return 0;
}