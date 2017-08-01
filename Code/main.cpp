#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
#include <ctime>

int main()  //example of lambda and iterators usage
            //this program creates 10x10 matrix, fills it with random numbers and them sorts it by rows
            //shows maximum of each row and sorts it by columns
{
    int sizeOfMatrix = 10;
    srand(time(0));

    std::vector< std::vector<int> > Matrix(sizeOfMatrix);
    for_each(Matrix.begin(), Matrix.end(), [=] (std::vector<int> &row) { row.resize(sizeOfMatrix); } );

    for (int i=0;i<sizeOfMatrix;i++)
        for (int j=0;j<sizeOfMatrix;j++)
            Matrix[i][j]=rand()%9+1; //from 1 to 9

    auto showLambda = [=] (std::vector<int> &row)
        {copy(row.begin(), row.end(), std::ostream_iterator<int>(std::cout, " "));  std::cout << std::endl; };   //lambda for output

    std::cout << "Ranadom Matrix:\n";
    for_each(Matrix.begin(), Matrix.end(), showLambda);
    std::cout << std::endl;

    for_each(Matrix.begin(), Matrix.end(), [] (std::vector<int> &row)
        { std::sort(row.begin(), row.end()); } );   //sort by rows

    std::cout << "Sorted Matrix:\n";
    for_each(Matrix.begin(), Matrix.end(), showLambda);
    std::cout << std::endl;

    int maximums[sizeOfMatrix];
    int counter=0;
    for ( const auto &i : Matrix) { maximums[counter++]=i[sizeOfMatrix-1]; }

    std::cout << "Maximums of each row: \n";
    for ( const auto &i : maximums ) { std::cout << i << ' '; }
    std::cout << std::endl << std::endl;

    for ( int i=0;i<sizeOfMatrix;i++)                    //bubble sorted
        for (int k=0;k<sizeOfMatrix;k++)
            for ( int j=0;j<sizeOfMatrix-1;j++)
                if (Matrix[j][i]>Matrix[j+1][i])
                    std::swap(Matrix[j][i],Matrix[j+1][i]);

    std::cout << "Bubble sorted by columns: \n";
    for_each(Matrix.begin(), Matrix.end(), showLambda);
    std::cout << std::endl;


    return 0;
}
