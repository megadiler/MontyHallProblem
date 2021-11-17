// https://en.wikipedia.org/wiki/Monty_Hall_problem
// 
// This simple C++ code generates random sample of N experiments and calculate results for 2 strategies 
// (1)Change First selection or  (2)do not change init selection 
// 
// This code shows that
// strategy(1) provides probability of Win = 2/3 
// strategy(2) provides probability of Win = 1/3 
//
//
//               | F_irst C_hoice success    |  F_irst C_hoise is fail    |    
//---------------|---------------------------|----------------------------|
//   no change   | prob of f_c_success = 1/3 |  prob of F_C_fail = 2/3    |
//               | Result of game = WIN      |  REsult of game = FAIL     | 
// --------------|---------------------------|----------------------------|
//   change      | prob of F_C_success = 1/3 |  prob of F_C_fail = 2/3    |           
//               | Result of game = FAIL     |  Result of game =  WIN     |
//

#include <iostream>
#include <vector>
#include <random>

struct Count123
{
    int count1{ 0 };
    int count2{ 0 };
    int count3{ 0 };
};

int main()
{
    const int N = 10000000;//число экспериментов 

    std::vector<int> V = std::vector<int>(N);

    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    auto min = 1; auto max = 3;
    std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
    std::uniform_int_distribution<int> uni2(0, 1); // guaranteed unbiased
 
    Count123 CountAll;

    for (auto &iter : V)
    {

        iter = uni(rng);
        switch (iter)
        {
        case 1: CountAll.count1++; break;
        case 2: CountAll.count2++; break;
        case 3: CountAll.count3++; break;
        default: std::cout << "Generation Fail !" <<  "\n";
        }
    }

    std::cout << "Number of random experiments: " << N << "\n";
    std::cout << "Number of 1 in sample: " << CountAll.count1 << "\n";
    std::cout << "Number of 2 in sample: " << CountAll.count2 << "\n";
    std::cout << "Number of 3 in sample: " << CountAll.count3 << "\n";

    std::cout << "Experiments done " << "\n";

    int CountSuccess_NoChange{ 0 };
    int CountSuccess_YesChange{ 0 };

    for (auto& iter : V)
    {
        int FirstChoise = uni(rng);
        int NumToOpenRnd = uni2(rng); // guaranteed unbiased
        int NumToOpen{ 0 };
        if (FirstChoise == iter)
        {
            switch (FirstChoise)
            {
            case 1: NumToOpen = NumToOpenRnd == 0 ? 2 : 3; break;
            case 2: NumToOpen = NumToOpenRnd == 0 ? 1 : 3; break;
            case 3: NumToOpen = NumToOpenRnd == 0 ? 1 : 2; break;
            }
        }
        else
        {
            switch (FirstChoise)
            {
            case 1: NumToOpen = iter == 2 ? 3 : 2; break; 
            case 2: NumToOpen = iter == 1 ? 3 : 1; break;
            case 3: NumToOpen = iter == 1 ? 2 : 1; break;
            }
        }

        //не менять выбор
        int SecondChoise = FirstChoise;
        if (SecondChoise == iter)
            CountSuccess_NoChange++;

        //менять выбор
        switch (FirstChoise)
        {
        case 1: SecondChoise = NumToOpen == 2 ? 3 : 2; break;
        case 2: SecondChoise = NumToOpen == 1 ? 3 : 1; break;
        case 3: SecondChoise = NumToOpen == 2 ? 1 : 2; break;
        }
        if (SecondChoise == iter)
            CountSuccess_YesChange++;
    }

    std::cout << "Probability to win: " << "\n";
    std::cout << "No Change:  " << static_cast<double>(CountSuccess_NoChange) * 100.0 / N  <<"\n";
    std::cout << "Yes Change:  " << static_cast<double>(CountSuccess_YesChange) * 100.0 / N << "\n";
}
