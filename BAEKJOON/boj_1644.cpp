#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> getPrimeNumUntilN(int n){
    vector<int> primes(n+1, 0);

    for (int i = 2; i <= n; i++){
        primes[i] = i;
    }

    for (int i = 2; i <= sqrt(n); i++){
        if (primes[i] == 0) continue;

        for (int j = i + i; j <= n; j += i)
            primes[j] = 0;
    }

    vector<int> prime_list;
    for(int i = 2 ; i <= n ; i++){
        if(primes[i] !=0){
            prime_list.push_back(i);
        }
    }

    return prime_list;
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int num;

    cin >> num;

    vector<int> primes = getPrimeNumUntilN(num);

    // for(auto a : primes)
    //     cout << a << " ";

    int left = 0;
    int right = 0;

    int answer = 0;
    int max_size = primes.size();
    int current_value = 0; 

    while(1){
        if(current_value < num){
            if(right + 1 > max_size)
                break;
            current_value += primes[right++];
        }else if (current_value > num){
            current_value -= primes[left++];
        }else {
            answer++;
            current_value -= primes[left++];
        }
    }

    cout << answer;
    return 0;
}